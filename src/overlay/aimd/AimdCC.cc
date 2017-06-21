/*
 * AimdCC.cpp
 *
 * The Implementation of the Adaptive Increase Multiplicative Decrease Congestion Control Algorithm
 *
 *  Created on: 27.05.2010
 *      Author: Martin
 */

#include "AimdCC.h"
#include <GlobalStatistics.h>
#include "../../misc/stringtools.h"

Define_Module(AimdCC);

AimdCC::AimdCC() {
	// TODO Auto-generated constructor stub

}

AimdCC::~AimdCC() {
	// TODO Auto-generated destructor stub
}

/**
 * Initialize values
 */
void AimdCC::initializeOverlay( int stage )
{
	BasicCC::initializeOverlay(stage);

	if (stage != MIN_STAGE_OVERLAY) return;

	reset_rates=new cMessage("reset rates timer");
	scheduleAt(simTime()+1, reset_rates);
	send_ack=true;

	maxPeers=par("maxPeers");
	startRate=par("startRate");
	increase_factor=par("increase_factor");
	decrease_factor=par("decrease_factor");

	for(int i=0;i<maxPeers;++i)
	{
		addNewPeer();
	}
}

/**
 * Checks if this node is a peer
 */
bool AimdCC::hasRelayNode(int node)
{
	return peerinfo.find(node)!=peerinfo.end();
}

/**
 * Checks if there are peers available to route a message
 */
bool AimdCC::hasCapacity(size_t msglen)
{
	int c_suitable=0;
	for(std::map<int, SPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
	{
		if(it->second.rate+msglen<=it->second.target_rate)
		{
			++c_suitable;
			if(c_suitable>=numHops)
				return true;
		}
	}
	return false;
}

/**
 * Builds a path for a message and returns it
 */
std::vector<int> AimdCC::getPathNodes(int target, int hops, size_t msglen, void **userdata)
{
	std::vector<int> ret;
	std::vector<int> suitable;
	for(std::map<int, SPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
	{
		if(it->first!=target)
		{
			if(it->second.rate+msglen<=it->second.target_rate)
			{
				suitable.push_back(it->first);
			}
		}
	}
	if(suitable.size()<hops)
	{
		return std::vector<int>();
	}

	SAUserdata *ud=new SAUserdata;
	for(int i=0;i<hops;++i)
	{
		int nn=intuniform(0, suitable.size()-1);
		ret.push_back(suitable[nn]);
		ud->data.push_back(SSUserdata(peerinfo[suitable[nn]].target_rate, peerinfo[suitable[nn]].state));
		peerinfo[suitable[nn]].rate+=msglen;
		suitable.erase(suitable.begin()+nn);
	}
	ret.push_back(target);
	*userdata=ud;
	return ret;
}

void AimdCC::deleteUserdata(void *userdata)
{
	SAUserdata *ud=(SAUserdata*)userdata;
	delete ud;
}

/**
 * Handles a lost message ( target rate is decreased)
 */
void AimdCC::handleLossEvent(const std::vector<int> &route, void *userdata)
{
	SAUserdata *ud=(SAUserdata*)userdata;
	for(size_t i=0;i<route.size()-1;++i)
	{
		const int &target=route[i];
		std::map<int, SPeerInfo>::iterator it=peerinfo.find(target);
		if(it!=peerinfo.end())
		{
			if(ud->data[i].state==0 )
			{
				it->second.state=1;
				double target_rate=ud->data[i].rate/2.0;
				if(target_rate<it->second.target_rate)
				{
					it->second.sthresh=it->second.target_rate;
					it->second.target_rate=target_rate;
					it->second.laststhreshtime=simTime();
				}
				if(it->second.target_rate<startRate)
					it->second.target_rate=startRate;
			}
			else if(ud->data[i].state!=0)
			{
				double target_rate=it->second.target_rate;
				//double decrease=(decrease_factor*it->second.target_rate)/getLatency(myKey, target).mean.dbl();
				//double decrease=(1500.0/(decrease_factor*getLatency(myKey, target).mean.dbl()));
				it->second.target_rate/=decrease_factor;
				if(it->second.target_rate<startRate)
				{
					it->second.target_rate=startRate;
					/*it->second.state=0;
					it->second.laststhreshtime=simTime();*/
				}
			}
		}
	}
}

/**
 * Handles a received ack ( target rate is decreased )
 */
void AimdCC::handleAckEvent( const std::vector<int> &route, void *userdata)
{
	for(size_t i=0;i<route.size()-1;++i)
	{
		const int &target=route[i];
		std::map<int, SPeerInfo>::iterator it=peerinfo.find(target);
		if(it!=peerinfo.end())
		{
			if(it->second.state==0)
			{
				if(it->second.sthresh==-1 || it->second.target_rate<it->second.sthresh)
				{
					it->second.target_rate+=1500;
				}
				else
				{
					it->second.state=1;
				}
			}
			if(it->second.state==1)
			{
				double target_rate=it->second.target_rate;
				double increase=(increase_factor*1500.0)/(getLatency(myKey, target).mean.dbl()*target_rate);
				it->second.target_rate+=increase;
			}
		}
	}
}

/**
 * Handles timer events
 */
void AimdCC::handleTimerEvent(cMessage* msg)
{
	if(BasicCC::handleTimerEventInt(msg))
		return;

	IncreaseTimer *increase_timer=dynamic_cast<IncreaseTimer*>(msg);
	//Reset all current rates to zero
	if(msg==reset_rates)
	{
		//If the key is one collect stats
		if(myKey==1)
		{
			double crate=0;
			double total_crate=0;
			int c=0;
			for(std::map<int, SPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
			{
				if(c<10)
				{
					globalStatistics->recordOutVector("9rateOf1To"+nconvert(c), it->second.rate);
					globalStatistics->recordOutVector("max9RateOf1To"+nconvert(c), (it->second.target_rate));
					++c;
				}
				total_crate+=(it->second.target_rate);
				crate+=it->second.rate;
			}
			globalStatistics->recordOutVector("1rate", crate);
			globalStatistics->recordOutVector("max2Rate", total_crate);
		}
		//Reset rates every second
		scheduleAt(simTime()+1, reset_rates);
		for(std::map<int, SPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
		{
			it->second.rate=0;
		}
		//replaceWeakest();
	}
	else if(increase_timer!=NULL)
	{
		/*std::map<int, SPeerInfo>::iterator it=peerinfo.find(increase_timer->getTarget());
		if(it!=peerinfo.end())
		{
			if(myKey==1)
			{
				if(it->first==1)
					int asfsaf=5;
				globalStatistics->recordOutVector("rtt_"+nconvert(it->first), getEstimatedLatency(it->first).dbl());
			}
			it->second.target_rate+=1500;
			scheduleAt(simTime()+getEstimatedLatency(it->first), increase_timer);
		}
		else
		{
			delete increase_timer;
		}*/
	}
}

void AimdCC::replaceWeakest(void)
{
	std::map<int, SPeerInfo>::iterator weakest=peerinfo.end();
	for(std::map<int, SPeerInfo>::iterator it=peerinfo.begin();it!=peerinfo.end();++it)
	{
		if(weakest==peerinfo.end() || it->second.target_rate < weakest->second.target_rate)
		{
			weakest=it;
		}
	}

	if(weakest!=peerinfo.end() && simTime()-weakest->second.addtime>10)
	{
		int weakid=weakest->first;
		peerinfo.erase(weakest);
		addNewPeer(weakid);
	}
}

/**
 * Adds a new random peer
 */
void AimdCC::addNewPeer(int notadd)
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

	SPeerInfo new_peer=SPeerInfo(0,startRate, nn);
	//scheduleAt(simTime()+getEstimatedLatency(nn), new_peer.increase_timer);

	peerinfo.insert(std::pair<int, SPeerInfo>(nn,new_peer));
}
