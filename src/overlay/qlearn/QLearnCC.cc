/*
 * QLearnCC.cpp
 *
 *  Created on: 15.06.2010
 *      Author: Martin
 */

#include "QLearnCC.h"
#include <GlobalStatistics.h>
#include "../../misc/stringtools.h"

Define_Module(QLearnCC);

QLearnCC::QLearnCC() {
	// TODO Auto-generated constructor stub

}

QLearnCC::~QLearnCC() {
	// TODO Auto-generated destructor stub
}

/**
 * Initialize the values from configuration
 */
void QLearnCC::initializeOverlay( int stage )
{
	BasicCC::initializeOverlay(stage);

	if (stage != MIN_STAGE_OVERLAY) return;

	reset_rates=new cMessage("reset rates timer");
	scheduleAt(simTime()+1, reset_rates);
	send_ack=true;

	maxPeers=par("maxPeers");
	packetsize=par("packetsize");
	maxRate=par("maxRate");
	alpha=par("alpha");
	lambda=par("lambda");
	reinf_up=par("reinf_up");
	reinf_down=par("reinf_down");
	reinf_down_cong=par("reinf_down_cong");
	epsilon=par("epsilon");

	for(int i=0;i<maxPeers;++i)
	{
		addNewPeer();
	}
}

/**
 * Returns if there is information about this node present
 */
bool QLearnCC::hasRelayNode(int node)
{
	return peerinfo.find(node)!=peerinfo.end();
}

/**
 * Returns if there's capacity to route a message of len 'msglen'
 */
bool QLearnCC::hasCapacity(size_t msglen)
{
	unsigned int c_suitable=0;
	for(std::map<int, SQPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
	{
		if(it->second.rate+msglen<=(it->second.curr_state+1)*packetsize)
		{
			++c_suitable;
			if(c_suitable>=numHops)
				return true;
		}
	}
	return false;
}

/**
 * Looks for a suitable path and returns it if there is still capacity free in the peers
 */
std::vector<int> QLearnCC::getPathNodes(int target, int hops, size_t msglen, void **userdata)
{
	std::vector<int> ret;
	std::vector<int> suitable;
	//Collect suitable peers
	for(std::map<int, SQPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
	{
		if(it->first!=target)
		{
			if(it->second.rate+msglen<=(it->second.curr_state+1)*packetsize)
			{
				suitable.push_back(it->first);
			}
		}
	}
	//not enough capacity
	if(suitable.size()<hops)
	{
		return std::vector<int>();
	}

	//collect userdata for each path node and update the rates
	SQUserdata *quserdata=new SQUserdata;
	quserdata->data.resize(hops);
	for(int i=0;i<hops;++i)
	{
		int nn=intuniform(0, suitable.size()-1);
		ret.push_back(suitable[nn]);
		SQPeerInfo & pi = peerinfo[suitable[nn]];
		pi.rate+=msglen;
		quserdata->data[i].state=pi.curr_state;
		quserdata->data[i].action=pi.last_action;
		suitable.erase(suitable.begin()+nn);
	}
	ret.push_back(target);
	quserdata->msgsize=(int)msglen;

	*userdata=quserdata;

	return ret;
}

/**
 * An ACK didn't come in time. Update the Q-Values of the peers on the route
 */
void QLearnCC::handleLossEvent(const std::vector<int> &route, void *userdata)
{
	SQUserdata *quserdata=(SQUserdata*)userdata;
	for(size_t i=0;i<route.size()-1;++i)
	{
		const int &target=route[i];
		std::map<int, SQPeerInfo>::iterator it=peerinfo.find(target);
		if(it!=peerinfo.end())
		{
			if(it->second.last_cong_state==-1)
			{
				for(int j=quserdata->data[i].state/2,s=(int)it->second.qtable.size();j<s && j<quserdata->data[i].state;++j)
				{
					it->second.qtable[j].up=0;
					it->second.qtable[j].stay=0;
					it->second.qtable[j].down=0;
				}
				for(int j=quserdata->data[i].state,s=(int)it->second.qtable.size();j<s;++j)
				{
					it->second.qtable[j].up=0;
					it->second.qtable[j].stay=0;
					it->second.qtable[j].down=-1*reinf_down*j;
				}
				it->second.curr_state=quserdata->data[i].state/2;
				it->second.last_cong_state=quserdata->data[i].state;
				continue;
			}
			it->second.last_cong_state=quserdata->data[i].state;
			int state=it->second.curr_state+1;
			if(it->second.last_cong_state!=-1)
			{
				int r_state=quserdata->data[i].state-quserdata->data[i].action;
				it->second.qtable[r_state].rewards.push_back(SActionReward(quserdata->data[i].action, reinf_down*state));
			}
			addAckBytes(&it->second, quserdata->msgsize);
		}
	}
}

/**
 * An ACK was received in time. Update the Q-Values of the peers on the route
 */
void QLearnCC::handleAckEvent( const std::vector<int> &route, void *userdata)
{
	SQUserdata *quserdata=(SQUserdata*)userdata;
	for(size_t i=0;i<route.size()-1;++i)
	{
		const int &target=route[i];
		std::map<int, SQPeerInfo>::iterator it=peerinfo.find(target);
		if(it!=peerinfo.end())
		{
			int state=it->second.curr_state+1;
			if(it->second.last_cong_state!=-1)
			{
				int r_state=quserdata->data[i].state-quserdata->data[i].action;
				it->second.qtable[r_state].rewards.push_back(SActionReward(quserdata->data[i].action, reinf_up*state));
			}
			addAckBytes(&it->second, quserdata->msgsize);
		}
	}
}

void QLearnCC::addAckBytes(SQPeerInfo *pi, int msgsize)
{
	pi->ack_bytes+=msgsize;
	if(pi->last_cong_state==-1) // fast start
	{
		pi->qtable[pi->curr_state].up=reinf_up*(pi->curr_state+1);
		pi->qtable[pi->curr_state].down=0;
		pi->qtable[pi->curr_state].stay=0;
		if(pi->curr_state+1<pi->qtable.size())
		{
			++pi->curr_state;
		}
		else
		{
			pi->last_cong_state=pi->curr_state;
			pi->curr_state=pi->qtable.size()-1;
		}
		pi->ack_bytes=0;
	}
	else
	{
		if(pi->ack_bytes>=(pi->curr_state+1)*packetsize)
		{
			pi->ack_bytes=0;
			updateQValue(pi);
		}
	}
}

void QLearnCC::deleteUserdata(void *userdata)
{
	SQUserdata *quserdata=(SQUserdata*)userdata;
	delete quserdata;
}

void QLearnCC::handleTimerEvent(cMessage* msg)
{
	if(BasicCC::handleTimerEventInt(msg))
		return;

	if(msg==reset_rates)
	{
		//collect statistics and set all rates to zero
		if(myKey==1)
		{
			double crate=0;
			double total_crate=0;
			int c=0;
			for(std::map<int, SQPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
			{
				if(c<10)
				{
					globalStatistics->recordOutVector("9rateOf1To"+nconvert(c), it->second.rate);
					globalStatistics->recordOutVector("max9RateOf1To"+nconvert(c), (it->second.curr_state+1)*packetsize);
					++c;
				}
				crate+=it->second.rate;
				total_crate+=(it->second.curr_state+1)*packetsize;
			}
			globalStatistics->recordOutVector("1rate", crate);
			globalStatistics->recordOutVector("max2Rate", total_crate);
		}
		scheduleAt(simTime()+1, reset_rates);
		for(std::map<int, SQPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
		{
			it->second.rate=0;
			/*if(it->second.curr_state<it->second.last_cong_state+1)
			{
				reinforceQValue(&it->second, it->second.curr_state, it->second.last_action, reinf_down_cong*it->second.curr_state);
			}*/
		}
	}
}

/**
 * Add a new random peer
 */
void QLearnCC::addNewPeer(int notadd)
{
	int tries=50;
	int nn;
	do
	{
		nn=intuniform(1, largestKey);
		--tries;
		if(tries<0)
			return;
	}
	while( nn==myKey || hasRelayNode(nn) || nn==notadd );

	SQPeerInfo new_peer=SQPeerInfo(0,maxRate/packetsize,nn, SQValues(0, 0, 0), false);
	//scheduleAt(simTime()+getEstimatedLatency(nn), new_peer.increase_timer);

	peerinfo.insert(std::pair<int, SQPeerInfo>(nn,new_peer));
}

/**
 * Select the next state epsilon-greedy on policy (state with maximum q-value
 */
void QLearnCC::updateQValue(SQPeerInfo *pi)
{
	//Apply rewards
	size_t reward_size=pi->qtable[pi->curr_state].rewards.size();
	if(reward_size>0)
	{
		SQValues reward;
		size_t rewards_up=0;
		size_t rewards_down=0;
		size_t rewards_stay=0;
		for(size_t i=0;i<reward_size;++i)
		{
			SActionReward &r=pi->qtable[pi->curr_state].rewards[i];
			if(r.action==-1)
			{
				reward.down+=r.value;
				++rewards_down;
			}
			else if(r.action==0)
			{
				reward.stay+=r.value;
				++rewards_stay;
			}
			else if(r.action==1)
			{
				reward.up+=r.value;
				++rewards_up;
			}
		}

		if(rewards_up>0)
		{
			reinforceQValue(pi, pi->curr_state+1, 1, reward.up/(double)rewards_up);
		}
		if(rewards_stay>0)
		{
			reinforceQValue(pi, pi->curr_state, 0, reward.stay/(double)rewards_stay);
		}
		if(rewards_down>0)
		{
			reinforceQValue(pi, pi->curr_state-1, -1, reward.down/(double)rewards_down);
		}

		pi->qtable[pi->curr_state].rewards.clear();
	}

	int alpha=bernoulli(epsilon);
	if(alpha==1)
	{
		pi->last_action=intuniform(-1,1);
	}
	else
	{
		double qmax=pi->qtable[pi->curr_state].down;
		pi->last_action=-1;
		if(pi->qtable[pi->curr_state].up==qmax)
		{
			pi->last_action=intuniform(0,1);
			if(pi->last_action==0)
				pi->last_action=-1;
		}
		if(pi->qtable[pi->curr_state].up>qmax)
		{
			pi->last_action=1;
			qmax=pi->qtable[pi->curr_state].up;
		}
		if(pi->qtable[pi->curr_state].stay>qmax)
		{
			pi->last_action=0;
			qmax=pi->qtable[pi->curr_state].up;
		}
	}

	if(pi->last_action==-1)
	{
		if(pi->curr_state>0)
		{
			--pi->curr_state;
		}
		else
		{
			//pi->curr_state; do nothing
			pi->last_action=0;
		}
	}
	else if(pi->last_action==1)
	{
		if(pi->curr_state<pi->qtable.size()-1)
		{
			++pi->curr_state;
		}
		else
		{
			//--pi->curr_state; do nothing
			pi->last_action=0;
		}
	}
}

/**
 * Learn the Q-Value of state 'state' and action 'action' as 'ret'
 */
void QLearnCC::reinforceQValue(SQPeerInfo *pi, int state, int action, double ret)
{
	int last_state=state-action;

	double qmax=pi->qtable[state].down;
	if(pi->qtable[state].up>qmax)
		qmax=pi->qtable[state].up;
	if(pi->qtable[state].stay>qmax)
		qmax=pi->qtable[state].stay;

	if(action==-1)
		pi->qtable[last_state].down+=alpha*(ret+lambda*qmax-pi->qtable[last_state].down);
	else if(action==1)
		pi->qtable[last_state].up+=alpha*(ret+lambda*qmax-pi->qtable[last_state].up);
	else if(action==0)
		pi->qtable[last_state].stay+=alpha*(ret+lambda*qmax-pi->qtable[last_state].stay);
}
