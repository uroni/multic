/*
 * AimdCC.cpp
 *
 *  Created on: 27.05.2010
 *      Author: Martin
 */

#include "PerfectCC.h"
#include <GlobalStatistics.h>
#include "../../misc/stringtools.h"

PerfectCC *PerfectCC::manager=NULL;

Define_Module(PerfectCC);

PerfectCC::PerfectCC() {
	// TODO Auto-generated constructor stub

}

PerfectCC::~PerfectCC() {
	// TODO Auto-generated destructor stub
}

void PerfectCC::initializeOverlay( int stage )
{
	BasicCC::initializeOverlay(stage);

	if (stage != MIN_STAGE_OVERLAY) return;

	send_ack=true;

	manager_step_timer=NULL;

	//Node with the key one is the manager
	if(myKey==1)
	{
		manager=this;
		manager_step_timer=new cMessage("Manager step");
		rtts.setn(largestKey);
		nextstep_time=simTime()+1;
		curr_simtime_step=0;
		limits.resize(numHops+1);
		for(size_t i=0;i<limits.size();++i)
		{
			limits[i].resize(largestKey+1);
			for(size_t j=0;j<limits[i].size();++j)
			{
				SLimit &limit=limits[i][j];
				limit.upper=0;
				limit.lower=99999999;
			}
		}
		scheduleAt(nextstep_time, manager_step_timer);
	}
}


std::vector<int> PerfectCC::getPathNodes(int target, int hops, size_t msglen, void **userdata)
{
	if(manager==NULL)
		return std::vector<int>();
	//Get the route from the manager
	std::vector<int> route=manager->getRoute(myKey, target, msglen);
	if(!route.empty())
		route.erase(route.begin());
	return route;
}

void PerfectCC::handleLossEvent(const std::vector<int> &route, void *userdata)
{

}

void PerfectCC::handleAckEvent( const std::vector<int> &route, void *userdata)
{
	//update the latency information of the manager
	for(size_t i=1;i<route.size();++i)
	{
		manager->updateLatency(getLatency(route[i-1], route[i]), route[i-1], route[i]);
	}
}

void PerfectCC::handleTimerEvent(cMessage* msg)
{
	if(BasicCC::handleTimerEventInt(msg))
		return;

	if(msg==manager_step_timer)
	{
		std::cout << "--------------------------Manager step------------------------------" << std::endl;
		std::map<int, std::vector<unsigned int> >::iterator it=rates.find(curr_simtime_step);
		if(it!=rates.end())
		{
			unsigned int rate_sum=0;
			for(size_t i=0;i<it->second.size();++i )
			{
				rate_sum+=it->second[i];
			}
			unsigned int crate=rate_sum/it->second.size();
			globalStatistics->recordOutVector("rate", crate);
			rates.erase(it);
		}
		else
		{
			globalStatistics->recordOutVector("rate", 0);
		}
		//Reset the limits
		for(size_t i=0;i<limits.size();++i)
		{
			for(size_t j=0;j<limits[i].size();++j)
			{
				SLimit &limit=limits[i][j];
				limit.upper=0;
				limit.lower=99999999;
			}
		}
		++curr_simtime_step;
		nextstep_time+=1;
		scheduleAt(nextstep_time, manager_step_timer);
	}
}

/**
 * Update the manager latencies
 */
void PerfectCC::updateLatency(SRtt pRtt, int source, int target)
{
	SRtt &lat=rtts.get(source-1,target-1);
	if(lat.mean==0 && lat.var==0)
	{
		lat=pRtt;
	}
	else
	{
		lat.mean+=0.1*(pRtt.mean-lat.mean);
		lat.var+=0.1*(pRtt.var-lat.var);
	}
}

/**
 * Find the perfect route and increment the rates of the nodes at certain
 * timesteps
 */
std::vector<int> PerfectCC::getRoute(int source, int target, size_t msglen)
{
	std::vector<int> nodes;
	nodes.push_back(target);
	nodes.push_back(source);
	std::vector<SRoute> r=getRouteInt(1, source, target, simTime()-0.01,nodes, msglen);
	if(r.empty()){
		//std::cout << "Didn't find a route" << std::endl;
		nodes.clear(); return nodes;
	}
	size_t r_size=r.size();
	for(size_t i=1;i<r.size();++i)
	{
		incrementRateOfNode(r[i].timestep, r[i].id, (int)msglen);
	}
	nodes.clear();
	//reverse it
	for(int i=r.size()-1;i>=0;--i)
	{
		int id=r[i].id;
		nodes.push_back(id);
	}
	return nodes;
}

/**
 * Get the latency information the manager has
 */
SRtt PerfectCC::getManagerLatency(int source, int target)
{
	SRtt &lat=rtts.get(source-1,target-1);
	if(lat.mean==0 && lat.var==0)
	{
		return SRtt(0.5, 0);
	}
	else
	{
		return lat;
	}
}

/**
 * Get the current rate of a node in a certain timestep
 */
unsigned int PerfectCC::getRateOfNode(int timestep, int node)
{
	std::map<int, std::vector<unsigned int> >::iterator it1=rates.find(timestep);
	if(it1==rates.end())
		return 0;

	return it1->second[node];
}

/**
 * Increment the current rate of a node
 */
void PerfectCC::incrementRateOfNode(int timestep, int node, int rate)
{
	std::map<int, std::vector<unsigned int> >::iterator it1=rates.find(timestep);
	if(it1==rates.end())
	{
		std::vector<unsigned int> n;
		n.resize(largestKey+1);
		memset(&n[0],0, sizeof(unsigned int)*(largestKey+1));
		n[node]=rate;
		rates.insert(std::pair<int, std::vector<unsigned int> >(timestep, n));
		return;
	}

	it1->second[node]+=rate;
}

/**
 * Calculate the perfect route
 */
std::vector<SRoute> PerfectCC::getRouteInt(int hop, int source, int target, simtime_t curr_time, std::vector<int> nodes, size_t msglen)
{
	//If the current time is within the limit, we already know that there is no
	//route available anymore
	{
		SLimit &limit=limits[hop-1][source];
		double upper=limit.upper.dbl();
		double lower=limit.lower.dbl();
		double curr=curr_time.dbl();
		if(limit.lower<=curr_time && limit.upper>=curr_time)
		{
			return std::vector<SRoute>();
		}
	}
	//Recursion: On the tail add the target and return the route
	if(hop>numHops)
	{
		std::vector<SRoute> t;
		{
			t.push_back(SRoute(0,target));
		}
		{
			SRoute r;
			r.timestep=curr_simtime_step;
			if(curr_time>nextstep_time)
				r.timestep+=1+(int)((curr_time-nextstep_time).dbl());
			r.id=source;

			t.push_back(r);
		}
		return t;
	}
	//Search for an available node at the current timestep and test if that node has itself an available route. If yes return that route
	for(int i=1;i<=largestKey;++i)
	{
		if(i!=source)
		{
			bool found=false;
			for(size_t j=0;j<nodes.size();++j)
			{
				if(nodes[j]==i)
				{
					found=true;
					break;
				}
			}
			if(found)
				continue;

			std::vector<SRoute> t;
			nodes.push_back(i);
			int simtime_step=curr_simtime_step;
			simtime_t next_time=curr_time+getManagerLatency(source,i).mean.dbl()/2.0;
			if(next_time>nextstep_time)
				simtime_step+=1+(int)((next_time-nextstep_time).dbl());
			if(getRateOfNode(simtime_step, i)+msglen<=incoming_rate )
			{
				t=getRouteInt(hop+1, i, target, next_time, nodes, msglen);
				nodes.erase(nodes.begin()+nodes.size()-1);
				if(!t.empty())
				{
					SRoute r;
					r.timestep=curr_simtime_step;
					if(curr_time>nextstep_time)
						r.timestep+=1+(int)((curr_time-nextstep_time).dbl());
					r.id=source;
					t.push_back(r);
					return t;
				}
			}
		}
	}
	//We didn't find a route. Update the limit for this hop
	SLimit &limit=limits[hop-1][source];
	double upper=limit.upper.dbl();
	double lower=limit.lower.dbl();
	double curr=curr_time.dbl();
	if(limit.upper<curr_time)
		limit.upper=curr_time;
	if(limit.lower>curr_time)
		limit.lower=curr_time;
	return std::vector<SRoute>();
}

simtime_t PerfectCC::getNextResetIncomingTime(void)
{
	if(manager!=NULL)
		return manager->getNextTime();
	else
		return simTime()+1;
}

simtime_t PerfectCC::getNextTime(void)
{
	return nextstep_time+0.001;
}

/**
 * Has the congestion controler capacity?
 */
bool PerfectCC::hasCapacity(size_t msglen)
{
	if(manager!=NULL)
		return manager->hasCapacity(myKey, msglen);
	else
		return true;
}

/**
 * Function in the manager
 */
bool PerfectCC::hasCapacity(int source, size_t msglen)
{
	SLimit &limit=limits[0][source];
	double upper=limit.upper.dbl();
	double lower=limit.lower.dbl();
	simtime_t curr_time=simTime()-0.01;
	double curr=curr_time.dbl();
	if(limit.lower<=curr_time && limit.upper>=curr_time && upper-lower<1.0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

