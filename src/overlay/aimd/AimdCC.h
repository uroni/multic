/*
 * AimdCC.h
 *
 * The Adaptive Increase Multiplicative Decrease Congestion Controler
 *
 *  Created on: 27.05.2010
 *      Author: Martin
 */

#ifndef AIMDCC_H_
#define AIMDCC_H_

#include "../basic/BasicCC.h"
#include "IncreaseTimer_m.h"

/**
 * Struct to save information about peers
 */
struct SPeerInfo
{
	SPeerInfo(){ rate=0; target_rate=0;}
	SPeerInfo(double pRate, double pTarget_rate, int target) : rate(pRate), target_rate(pTarget_rate) { addtime=simTime();sthresh=-1;state=0;laststhreshtime=0;}
	double rate;
	double target_rate;
	double sthresh;
	int state;
	simtime_t addtime;
	simtime_t laststhreshtime;
};

struct SSUserdata
{
	SSUserdata(double pRate, int pState) : rate(pRate), state(pState) {}
	double rate;
	int state;
};

struct SAUserdata
{
	std::vector<SSUserdata> data;
};

class AimdCC : public BasicCC
{
public:
	AimdCC();
	virtual ~AimdCC();

	virtual void initializeOverlay( int stage );


	virtual void handleTimerEvent(cMessage* msg);

	virtual bool hasCapacity(size_t msglen);


protected:

	//Returns a path where there is bandwidth available
	virtual std::vector<int> getPathNodes(int target, int hops,size_t msglen, void **userdata);
	//Called on a lost message
	virtual void handleLossEvent(const std::vector<int> &route, void *userdata);
	//Called on a received ack
	virtual void handleAckEvent(const std::vector<int> &route, void *userdata);

	//Not in use currently
	void replaceWeakest(void);

	//Adds a new peer
	void addNewPeer(int notadd=-1);

	//Test if this node is a peer
	bool hasRelayNode(int node);

	virtual void deleteUserdata(void *userdata);

	std::map<int, SPeerInfo> peerinfo;

	//Maximum number of peers
	int maxPeers;
	//Rate to start at (and minimum rate)
	unsigned int startRate;
	//the rate is increased with the help of that factor on an ACK
	double increase_factor;
	//the rate is decreased with the help of this factor on a packet loss
	double decrease_factor;

	//Timer to reset the rates
	cMessage *reset_rates;
};

#endif /* AIMDCC_H_ */
