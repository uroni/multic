/*
 * AimdCC.h
 *
 *  Created on: 27.05.2010
 *      Author: Martin
 */

#ifndef PERFECTCC_H
#define PERFECTCC_H

#include "../basic/BasicCC.h"

class PerfectCC;

struct SRoute
{
	SRoute(int pTimestep, int pId) : timestep(pTimestep), id(pId){}
	SRoute(void){ timestep=0; id=0; }
	int timestep;
	int id;
};

struct SLimit
{
	simtime_t upper;
	simtime_t lower;
};

/**
 * Perfect congestion control for testing purposes
 */
class PerfectCC : public BasicCC
{
public:
	PerfectCC();
	virtual ~PerfectCC();

	virtual void initializeOverlay( int stage );


	virtual void handleTimerEvent(cMessage* msg);

	std::vector<int> getRoute(int source, int target, size_t msglen);
	/**
	 * Update the manager latencies
	 */
	void updateLatency(SRtt pRtt, int source, int target);
	simtime_t getNextTime(void);

	virtual simtime_t getNextResetIncomingTime(void);

	virtual bool hasCapacity(size_t msglen);

	/**
	 * Function in the manager
	 */
	virtual bool hasCapacity(int source, size_t msglen);

protected:
	virtual std::vector<int> getPathNodes(int target, int hops,size_t msglen, void **userdata);
	virtual void handleLossEvent(const std::vector<int> &route, void *userdata);
	virtual void handleAckEvent(const std::vector<int> &route, void *userdata);

	/**
	 * Get the latency information the manager has
	 */
	SRtt getManagerLatency(int source, int target);

	/**
	 * Calculate the perfect route
	 */
	std::vector<SRoute> getRouteInt(int hop, int source, int target, simtime_t curr_time, std::vector<int> nodes, size_t msglen);

	/**
	 * Get the current rate of a node in a certain timestep
	 */
	unsigned int getRateOfNode(int timestep, int node);
	/**
	 * Increment the current rate of a node
	 */
	void incrementRateOfNode(int timestep, int node, int rate);

	static PerfectCC *manager;

	//manager
	cMessage *manager_step_timer;
	simtime_t nextstep_time;
	uppermatrix<SRtt> rtts;
	std::map<int, std::vector<unsigned int> > rates;
	std::vector< std::vector<SLimit> > limits;
	int curr_simtime_step;

};

#endif /* PERFECTCC_H */
