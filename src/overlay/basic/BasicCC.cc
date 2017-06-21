//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "BasicCC.h"
#include "AckMsg_m.h"
#include "TimeoutMessage_m.h"
#include <GlobalStatistics.h>

#define BIGBIT (1 << 24)


Define_Module(BasicCC);

const double ttlconv_tol=0.00001;

unsigned int BasicCC::incoming_bytes_m=0;
int BasicCC::num_all_dropped=0;
int BasicCC::delayed_all_acks=0;
double BasicCC::timetotimeouts_all=0.0;
double BasicCC::last_timetotimeouts_all=99999.0;
unsigned int BasicCC::timetotimeouts_all_c;
double BasicCC::ttl_convtime=0.0;
double BasicCC::last_timetotimeouts_all_smoothed=0;
double BasicCC::timetotimeouts_all_smoothed=0;

void test_uppermatrix(void);

BasicCC::BasicCC()
{
	test_uppermatrix();
}

BasicCC::~BasicCC()
{

}

/**
 * Initialize the base class
 */
void BasicCC::initializeOverlay(int stage)
{
	if (stage != MIN_STAGE_OVERLAY) return;

	ev << "Setting key...";
	myKey = thisNode.getAddress().get4().getInt() & ~BIGBIT;

	creationTime=simTime();
	num_dropped=0;
	send_ack=true;
	curr_ack_sequence_id=0;
	delayed_acks=0;
	timetotimeouts=0;
	timetotimeouts_c=0;
	switched_rate=false;

	incoming_rate=par("incoming_rate");
	incoming_rate2=par("incoming_rate2");
	rate_switch_border=par("rate_switch_border");
	rate_switch_time=par("rate_switch_time");
	incoming_received=0;
	incoming_total_bytes=0;
	largestKey=par("largestKey");
	numHops=par("numHops");
	rttalpha=par("rttalpha");
	rttgamma=par("rttgamma");

	if(rate_switch_border>0 && myKey>=rate_switch_border)
	{
		int tmp=incoming_rate;
		incoming_rate=incoming_rate2;
		incoming_rate2=tmp;
	}

	incoming_timer=new cMessage("incoming timer");
	scheduleAt(getNextResetIncomingTime(), incoming_timer);
	reset_measurement_timer=new cMessage("reset_measurement_timer");
	/*scheduleAt(simTime()+10, reset_measurement_timer);*/

	latencies.setn(largestKey);

	if(myKey==1)
	{
		incoming_measurement_timer=new cMessage("incoming measurement timer");
		scheduleAt(simTime()+1,incoming_measurement_timer);
	}
}

/**
 * Set the key of this node
 */
void BasicCC::setOwnNodeID()
{
	thisNode.setKey(OverlayKey(myKey));
}

/**
 * Should return true if the node is itself else false
 */
bool BasicCC::isSiblingFor(const NodeHandle & node, const OverlayKey & key, int numSiblings, bool *err)
{
	if (node == thisNode && key == thisNode.getKey())
	{
		return true;
	}
	else
	{
	    return false;
	}
}

/**
 * Drop packets if too much was already received
 */
bool BasicCC::dropPacket(BaseOverlayMessage *msg)
{
	if(rate_switch_time!=0 && switched_rate==false && simTime().dbl()>=rate_switch_time)
	{
		incoming_rate=incoming_rate2;
		switched_rate=true;
	}

	incoming_received+=(int)msg->getByteLength();
	RECORD_STATS(incoming_total_bytes+=(int)msg->getByteLength(); );
	if(incoming_received>incoming_rate)
	{
		RECORD_STATS(++num_dropped;++num_all_dropped);
		return true;
	}
	return false;
}

/**
 * Returns a path from this node to target with 'hops' hops and adds the userdata to the packet
 */
std::vector<int> BasicCC::getPathNodes(int target, int hops, size_t msglen, void **userdata)
{
	//Route randomly
	std::vector<int> ret;
	for(int i=0;i<hops;++i)
	{
		int nn;
		bool found;
		do
		{
			nn=intuniform(1, largestKey);
			found=false;
			for(size_t j=0;j<ret.size();++j)
			{
				if(ret[j]==nn)
				{
					found=true;
					break;
				}
			}
		}
		while(found || nn==target || nn==myKey );
		ret.push_back(nn);
	}
	ret.push_back(target);
	return ret;
}

/**
 * Implements the find node call.
 *
 * This method simply returns the closest nodes known in the
 * corresponding routing topology. If the node is a sibling for
 * this key (isSiblingFor(key) = true), this method returns all
 * numSiblings siblings, with the closest neighbor to the key
 * first.
 *
 * @param key The lookup key.
 * @param numRedundantNodes Maximum number of next hop nodes to return.
 * @param numSiblings number of siblings to return
 * @param msg A pointer to the BaseRouteMessage or FindNodeCall
 *                   message of this lookup.
 * @return NodeVector with closest nodes.
 */
NodeVector *BasicCC::findNode(const OverlayKey & key, int numRedundantNodes, int numSiblings, BaseOverlayMessage *msg)
{
	NodeVector * nextHop=new NodeVector(1);
	LookupExt *findNodeExt=NULL;
	if (msg && msg->hasObject("findNodeExt"))
	{
		findNodeExt = check_and_cast<LookupExt*>(msg->getObject("findNodeExt"));
	}

	//Drop only packets if they're not from the application layer
	if(findNodeExt!=NULL && dropPacket(msg))
	{
		delete nextHop;
		return new NodeVector(0);
	}

	std::vector<int> route;
	bool first=false;
	void *userdata=NULL;
	//Extend the message with routing data
	if(findNodeExt==NULL)
	{
		first=true;
		//find the route
		route=getPathNodes((int)key.hash(), numHops, msg->getByteLength(), &userdata);
		if(route.empty())
		{
			deleteUserdata(userdata);
			//RECORD_STATS(++num_dropped); don't record
			delete nextHop;
			return new NodeVector(0);
		}
		//Set the data and save the path the message is supposed to take
		findNodeExt=new LookupExt("findNodeExt");
		findNodeExt->setHops(0);
		findNodeExt->setPathNodesArraySize(route.size()+1);
		findNodeExt->setPathNodes(0, myKey);
		findNodeExt->setSequence_id(curr_ack_sequence_id++);
		findNodeExt->setSenttime(simTime());
		//std::cout << "route: " << myKey ;
		for(size_t i=0;i<route.size();++i)
		{
			//std::cout << " - " << route[i];
			findNodeExt->setPathNodes(i+1, route[i]);
		}
		//std::cout << endl;
		msg->addObject(findNodeExt);
	}
	lookup_ext=findNodeExt;

	//save the number of hops the message did
	findNodeExt->setHops(findNodeExt->getHops()+1);

	//find the next node
	int nextKey=findNodeExt->getPathNodes(findNodeExt->getHops());
	if(nextKey==-1)
	{
		deleteUserdata(userdata);
		delete nextHop;
		return new NodeVector(0);
	}

	//Set the next hop address
	NodeHandle targetNode;
	targetNode.setAddress(IPAddress(BIGBIT | nextKey));
	targetNode.setPort(thisNode.getPort());
	targetNode.setKey(OverlayKey(nextKey));
	nextHop->add(targetNode);

	//If the message came from the application save data about the message and set an ack timeout
	if(send_ack && first==true)
	{
		//Estimate rtt
		double rtt=0;
		for(int i=0;i<=numHops;++i)
		{
			rtt+=getEstimatedLatency(findNodeExt->getPathNodes(i), findNodeExt->getPathNodes(i+1)).dbl();
		}
		simtime_t timeouttime=simTime()+rtt;
		sent_msgs.insert(std::pair<unsigned int, SSentMsg>(findNodeExt->getSequence_id(), SSentMsg(route,simTime(),userdata,timeouttime)));
		TimeoutMessage *timeout=new TimeoutMessage("Ack timeout");
		timeout->setSeq_id(findNodeExt->getSequence_id());
		scheduleAt(timeouttime, timeout);

	}

	return nextHop;
}

void BasicCC::joinOverlay()
{
	setOverlayReady(true);
}

int BasicCC::getMaxNumSiblings()
{
	return 1;
}

void BasicCC::handleTimerEvent(cMessage *msg)
{
	handleTimerEventInt(msg);
}

simtime_t BasicCC::getNextResetIncomingTime(void)
{
	next_resettime=simTime()+1;
	return next_resettime;
}

simtime_t BasicCC::getNextResetTime(void)
{
	return next_resettime;
}

bool BasicCC::handleTimerEventInt(cMessage *msg)
{
	TimeoutMessage *timeout=dynamic_cast<TimeoutMessage*>(msg);
	if(msg==incoming_timer)
	{
		//reset the incoming time
		scheduleAt(getNextResetIncomingTime(), incoming_timer);

		//std::cout << myKey << ": Packets on the fly: " << sent_msgs.size() << std::endl;

		incoming_received=0;
		return true;
	}
	else if(msg==reset_measurement_timer)
	{
		/*starttime=simTime();
		num_dropped=0;*/
		return true;
	}
	else if(msg==incoming_measurement_timer)
	{
		scheduleAt(simTime()+1, incoming_measurement_timer);

		double new_timetotimeouts=timetotimeouts_all_c==0?0.0:(timetotimeouts_all/(double)timetotimeouts_all_c);
		if(last_timetotimeouts_all!=0 && new_timetotimeouts!=0 && ttl_convtime==0)
		{
			timetotimeouts_all_smoothed=0.9*last_timetotimeouts_all_smoothed+0.1*new_timetotimeouts;
			if(last_timetotimeouts_all_smoothed!=0 )
			{
				double diff=last_timetotimeouts_all_smoothed-timetotimeouts_all_smoothed;
				if(diff<0)diff*=-1;
				if(diff<ttlconv_tol)
				{
					ttl_convtime=simTime().dbl();
				}
			}
			last_timetotimeouts_all_smoothed=timetotimeouts_all_smoothed;
		}

		globalStatistics->recordOutVector("incoming_bytes", incoming_bytes_m);
		globalStatistics->recordOutVector("drops", num_all_dropped);
		globalStatistics->recordOutVector("delayed_acks", delayed_all_acks);
		if(last_timetotimeouts_all!=0 && new_timetotimeouts!=0)
		{
			globalStatistics->recordOutVector("timetotimeouts", new_timetotimeouts);
		}
		last_timetotimeouts_all=new_timetotimeouts;
		num_all_dropped=0;
		delayed_all_acks=0;
		incoming_bytes_m=0;

		//std::cout << "sent_msgs.size(): " << sent_msgs.size() << std::endl;
	}
	else if(timeout!=NULL)
	{
		//Ack timeout. Find the message. If we don't find it an ack has already been received and the data deleted,
		//else we have a loss event
		std::map<unsigned int, SSentMsg>::iterator it=sent_msgs.find(timeout->getSeq_id());
		if(it!=sent_msgs.end())
		{
			handleLossEvent(it->second.route, it->second.userdata);
			deleteUserdata(it->second.userdata);
			sent_msgs.erase(it);
		}
		delete timeout;
		return true;
	}

	return false;
}

AbstractLookup* BasicCC::createLookup(RoutingType routingType, const BaseOverlayMessage* msg, const cPacket* findNodeExt, bool appLookup)
{
	//Add extended data to iterative lookups (not in use atm)
	LookupExt *nfindNodeExt=new LookupExt("findNodeExt");

	nfindNodeExt->setHops(0);
	AbstractLookup* newLookup =  BaseOverlay::createLookup(routingType,
            msg, nfindNodeExt,
            appLookup);
	delete nfindNodeExt;
	return newLookup;
}

int BasicCC::getKey(void)
{
	return myKey;
}

/**
 * Hook for forwarded message in recursive lookup mode
 *
 * This hook is called just before a message is forwarded to a next hop or
 * if the message is at its destination just before it is sent to the app.
 * Default implementation just returns true. This hook
 * can for example be used to detect failed nodes and call
 * handleFailedNode() before the actual forwarding takes place.
 *
 * @param dest destination node
 * @param msg message to send
 * @returns true, if message should be forwarded;
 *  false, if message will be forwarded later by an other function
 *  or message has been discarded
 */
bool BasicCC::recursiveRoutingHook(const TransportAddress& dest,
									  BaseRouteMessage* msg)
{
	//Find data. Check if this is the last node in the path. If yes send an ack else just
	//forward the message
	LookupExt *findNodeExt=NULL;
	if (msg && msg->hasObject("findNodeExt"))
	{
		findNodeExt = check_and_cast<LookupExt*>(msg->getObject("findNodeExt"));
	}
	if(findNodeExt!=NULL)
	{
		int target_id=findNodeExt->getPathNodes(findNodeExt->getPathNodesArraySize()-1);
		if(target_id==myKey)
		{
			if(findNodeExt->getHops()!=numHops+1)
			{
				std::cout << "error: wrong number of hops (real:"<<findNodeExt->getHops() <<" expected:"<<numHops+1 << ")" << std::endl;
				delete msg;
				return false;
			}

			incoming_bytes_m+=(unsigned int)msg->getByteLength();
			/**
			 * No dropping of application data
			 *if(dropPacket(msg))
			{
				delete msg;
				return false;
			}**/
			if(send_ack)
			{
				AckMsg *ack=new AckMsg();
				ack->setSeq_id(findNodeExt->getSequence_id());
				ack->setDatasenttime(findNodeExt->getSenttime());
				ack->setHops(1);
				ack->setPathNodesArraySize(findNodeExt->getPathNodesArraySize());
				for(int i=0,as=findNodeExt->getPathNodesArraySize();i<as;++i)
				{
					ack->setPathNodes(as-i-1, findNodeExt->getPathNodes(i));
				}
				sendMessageToUDP(TransportAddress(IPAddress(BIGBIT | ack->getPathNodes(1)),localPort), ack);
			}
		}
	}
	else
	{
		EV << "Err: findNodeExt not found";
	}
	return true;
}

void BasicCC::finishOverlay()
{
	//Save some statistics

	setOverlayReady(false);

	simtime_t time = globalStatistics->calcMeasuredLifetime(creationTime);

	globalStatistics->addStdDev("BasicCC: Drop rate", (double)(num_dropped*1500.0)/time.dbl());
	globalStatistics->addStdDev("BasicCC: Incoming rate", (double)(incoming_total_bytes)/time.dbl());
	globalStatistics->addStdDev("BasicCC: Delayed acks/s", (double)(delayed_acks)/time.dbl());
	globalStatistics->addStdDev("BasicCC: Mean Timetotimeouts", (double)(timetotimeouts.dbl())/(double)timetotimeouts_c);
	globalStatistics->addStdDev("BasicCC: TTL Convergencetime", ttl_convtime);
}

/**
 * Handles UDP message to the overlay - in this case only acks are sent
 */
void BasicCC::handleUDPMessage(BaseOverlayMessage* msg)
{
	AckMsg *ack=dynamic_cast<AckMsg*>(msg);
	if(ack!=NULL)
	{
		//If we are the source of the message update the latencies. Throw an ACK event and delete the
		//message data
		if(ack->getHops()==ack->getPathNodesArraySize()-1 && ack->getPathNodes(ack->getHops())==myKey)
		{
			int seq_id=ack->getSeq_id();

			simtime_t ut=(simTime()-ack->getDatasenttime())/(double)(ack->getPathNodesArraySize()-1);
			for(size_t i=1;i<ack->getPathNodesArraySize();++i)
			{
				const int &source=ack->getPathNodes(i-1);
				const int &target=ack->getPathNodes(i);
				SRtt &lat=latencies.get(source-1,target-1);
				if(lat.mean<0.001 && lat.var<0.001)
				{
					lat.mean=ut;
					lat.var=ut;
				}
				else
				{
					//Jacobson/Karel
					simtime_t err=ut-lat.mean;
					lat.mean+=rttalpha*err;
					if(err<0)err*=-1;
					lat.var+=rttalpha*(err-lat.var);
				}
			}

			std::map<unsigned int, SSentMsg>::iterator it=sent_msgs.find(seq_id);
			if(it!=sent_msgs.end())
			{
				RECORD_STATS(timetotimeouts+=abs(simTime().dbl()-it->second.timeouttime.dbl());++timetotimeouts_c);
				timetotimeouts_all+=abs(simTime().dbl()-it->second.timeouttime.dbl());
				++timetotimeouts_all_c;

				handleAckEvent(it->second.route, it->second.userdata);
				deleteUserdata(it->second.userdata);
				sent_msgs.erase(it);
			}
			else
			{
				RECORD_STATS(++delayed_acks; ++delayed_all_acks);
			}

			delete ack;
		}
		else
		{
			ack->setHops(ack->getHops()+1);
			sendMessageToUDP(TransportAddress(IPAddress(BIGBIT | ack->getPathNodes(ack->getHops())),localPort), ack);
		}
	}
	else
	{
		delete msg;
	}
}

/**
 * Estimate the latencies by MEAN+rttgamma*VAR
 */
simtime_t BasicCC::getEstimatedLatency(int source, int target)
{
	SRtt &lat=latencies.get(source-1,target-1);
	if(lat.mean<0.001 && lat.var<0.001)
	{
		return 0.5;
	}
	else
	{
		double mean=lat.mean.dbl();
		double var=lat.var.dbl();
		return lat.mean+rttgamma*lat.var;
	}
}

/**
 * Return the latency information
 */
SRtt BasicCC::getLatency(int source, int target)
{
	SRtt &lat=latencies.get(source-1,target-1);
	if(lat.mean<0.001 && lat.var<0.001)
	{
		return SRtt(0.5,0);
	}
	else
	{
		return lat;
	}
}

void BasicCC::handleLossEvent(const std::vector<int> &route, void *userdata)
{

}

void BasicCC::handleAckEvent(const std::vector<int> &route, void *userdata)
{

}

void BasicCC::deleteUserdata(void *userdata)
{

}

bool BasicCC::hasCapacity(size_t msglen)
{
	return true;
}






