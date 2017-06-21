/*
 * QLearnCC.h
 *
 * Congestion controler which learns the rates by reinforcement learning
 *
 *  Created on: 15.06.2010
 *      Author: Martin
 */

#ifndef QLEARNCC_H_
#define QLEARNCC_H_

#include "../basic/BasicCC.h"

struct SActionReward
{
	SActionReward(){ value=0; action=0; }
	SActionReward(int pAction, double pValue){ action=pAction; value=pValue; }
	double value;
	int action;
};

/**
 * the action values
 */
struct SQValues
{
	SQValues(){up=0; stay=0; down=0;}
	SQValues(double pUp, double pDown, double pStay) : up(pUp), down(pDown), stay(pStay) {}
	SQValues(int action, double value){ if(action==-1) down=value; if(action==0) stay=value; if(action==1) up=value; }
	double up;
	double down;
	double stay;
	std::vector<SActionReward> rewards;
};

struct SQSubuserdata
{
	int state;
	int action;
};

/**
 * Userdata for messages. Save the current state and last action
 */
struct SQUserdata
{
	std::vector<SQSubuserdata> data;
	int msgsize;
};

/**
 * Reinforcement learning information about each peer
 */
struct SQPeerInfo
{
	SQPeerInfo(){ curr_state=0; target=0; rate=0;last_action=0;}
	SQPeerInfo(int pCurr_state, unsigned int pMax_states, int pTarget, const SQValues &def, bool q_rnd) : curr_state(pCurr_state), target(pTarget), last_cong_state(-1)
	{
		qtable.resize(pMax_states);
		for(size_t i=0;i<qtable.size();++i)
		{
			if(!q_rnd)
				qtable[i]=def;
			else
				qtable[i]=SQValues(uniform(-1,1), uniform(-1,1), uniform(-1,1));
		}
		rate=0;
		last_action=0;
	}
	int curr_state;
	int last_state;
	std::vector<SQValues> qtable;
	int target;
	int rate;
	int last_action;
	int last_cong_state;
	int ack_bytes;
};

/**
 * Q-Learning Congestion Controler
 */
class QLearnCC : public BasicCC
{
public:
	QLearnCC();
	virtual ~QLearnCC();

	virtual void initializeOverlay( int stage );


	virtual void handleTimerEvent(cMessage* msg);

	/**
	 * Returns if there's capacity to route a message of len 'msglen'
	 */
	virtual bool hasCapacity(size_t msglen);


protected:
	/**
	 * Looks for a suitable path and returns it if there is still capacity free in the peers
	 */
	virtual std::vector<int> getPathNodes(int target, int hops,size_t msglen, void **userdata);
	/**
	 * Loss Event
	 */
	virtual void handleLossEvent(const std::vector<int> &route, void *userdata);
	/**
	 * An ACK was received for a message
	 */
	virtual void handleAckEvent(const std::vector<int> &route, void *userdata);
	virtual void deleteUserdata(void *userdata);

	/**
	 * Add a new random peer
	 */
	void addNewPeer(int notadd=-1);

	/**
	 * Update the state of peer 'pi'
	 */
	void updateQValue(SQPeerInfo *pi);
	/**
	 * Learn the Q-Values of peer 'pi'
	 */
	void reinforceQValue(SQPeerInfo *pi, int state, int action, double ret);

	/**
	 * Returns if there is information about this node present
	 */
	bool hasRelayNode(int node);

	void addAckBytes(SQPeerInfo *pi, int msgsize);

	std::map<int, SQPeerInfo> peerinfo;

	int maxPeers;
	unsigned int packetsize;
	int maxRate;

	cMessage *reset_rates;

	double alpha;
	double lambda;
	double reinf_up;
	double reinf_down;
	double reinf_down_cong;
	double epsilon;
};

#endif /* QLEARNCC_H_ */
