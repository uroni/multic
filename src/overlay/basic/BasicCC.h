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

#ifndef SIMPLECC_H_
#define SIMPLECC_H_

#include <BaseOverlay.h>
#include "LookupExt_m.h"
#include <map>
#include "../../misc/uppermatrix.h"

/**
 * Saved data about sent messages
 */
struct SSentMsg
{
	SSentMsg(const std::vector<int> &pRoute, simtime_t pSendtime, void *pUserdata, simtime_t pTimeouttime)
	: route(pRoute), sendtime(pSendtime), userdata(pUserdata),timeouttime(pTimeouttime) {}
	std::vector<int> route;
	simtime_t sendtime;
	simtime_t timeouttime;
	void * userdata;
};

/**
 * RTT info about peers
 */
struct SRtt
{
	SRtt(void){ mean=0; var=0; }
	SRtt(simtime_t pMean, simtime_t pVar) : mean(pMean), var(pVar) {}
	simtime_t mean;
	simtime_t var;
};

/**
 * Basic functions for all congestion control algorithms
 */
class BasicCC : public BaseOverlay
{
public:
	BasicCC();
	virtual ~BasicCC();

	virtual void initializeOverlay( int stage );

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
	virtual NodeVector* findNode( const OverlayKey& key,
	                                  int numRedundantNodes,
	                                  int numSiblings,
	                                  BaseOverlayMessage* msg = NULL);

	/**
	 * Query if a node is among the siblings for a given key.
	 *
	 * Query if a node is among the siblings for a given key.
	 * This means, that the nodeId of this node is among the closest
	 * numSiblings nodes to the key and that by a local findNode() call
	 * all other siblings to this key can be retrieved.
	 *
	 * @param node the NodeHandle
	 * @param key destination key
	 * @param numSiblings The nodes knows all numSiblings nodes close
	 *                    to this key
	 * @param err return false if the range could not be determined
	 * @return bool true, if the node is responsible for the key.
	 */
	virtual bool isSiblingFor(const NodeHandle& node,
							  const OverlayKey& key, int numSiblings, bool* err);

	/**
	 * Query the maximum number of siblings (nodes close to a key)
	 * that are maintained by this overlay protocol.
	 *
	 * @return int number of siblings.
	 */
	virtual int getMaxNumSiblings();

	virtual void setOwnNodeID();
	virtual void joinOverlay();

	virtual void handleTimerEvent(cMessage* msg);

	 /**
	 * Creates an abstract iterative lookup instance.
	 *
	 * @param routingType The routing type for this
	 *                    lookup (e.g. recursive/iterative)
	 * @param msg pointer to the message for which the lookup is created.
	 *            Derived classes can use it to construct an object with
	 *            additional info for the lookup class.
	 * @param findNodeExt object that will be sent with the findNodeCalls
	 * @param appLookup Set to true, if lookup is triggered by application (for statistics)
	 * @return AbstractLookup* The new lookup instance.
	 */
	virtual AbstractLookup* createLookup(RoutingType routingType = DEFAULT_ROUTING,
										 const BaseOverlayMessage* msg = NULL,
										 const cPacket* findNodeExt = NULL,
										 bool appLookup = false);

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
	virtual bool recursiveRoutingHook(const TransportAddress& dest,
									  BaseRouteMessage* msg);


	/**
	 * Returns the key (address of the node)
	 */
	int getKey(void);

	/**
	 * collects statistical data in derived class
	 */
	virtual void finishOverlay();

	/**
	 * Processes messages from underlay
	 *
	 * @param msg Message from UDP
	 */
	virtual void handleUDPMessage(BaseOverlayMessage* msg);

	virtual simtime_t getNextResetIncomingTime(void);

	/**
	 * Returns if the overlay has the capacity to route a message of size msglen
	 */
	virtual bool hasCapacity(size_t msglen);

	virtual simtime_t getNextResetTime(void);

protected:

	bool handleTimerEventInt(cMessage* msg);

	/**
	 * Drops packets if too much were already received
	 */
	bool dropPacket(BaseOverlayMessage *msg);

	/**
	 * Returns the estimated latency from source to target
	 */
	simtime_t getEstimatedLatency(int source, int target);
	/**
	 * Returns all latency data about the route from source to target
	 */
	SRtt getLatency(int source, int target);


	/**
	 * Returns a path from this node to target with 'hops' hops and adds the userdata to the packet
	 */
	virtual std::vector<int> getPathNodes(int target, int hops,size_t msglen, void **userdata);
	/**
	 * Called when a loss event occured, which means an ack wasn't received in time
	 */
	virtual void handleLossEvent(const std::vector<int> &route, void *userdata);
	/**
	 * Called when an ack was received in time
	 */
	virtual void handleAckEvent(const std::vector<int> &route, void *userdata);
	/**
	 * Callback to delete userdata
	 */
	virtual void deleteUserdata(void *userdata);


	//If acks should be sent, set this to true (saves performance otherwise)
	bool send_ack;
	//The key of this node
	int myKey;
	//statistics
	int incoming_rate;
	int incoming_rate2;
	int rate_switch_border;
	double rate_switch_time;
	int incoming_received;
	int num_dropped;
	static int num_all_dropped;
	//number of nodes
	int largestKey;
	//number of nodes for each route
	int numHops;
	simtime_t creationTime;
	LookupExt *lookup_ext;
	//number of delayed acks (acks that didn't come in time)
	int delayed_acks;
	static int delayed_all_acks;
	double rttalpha;
	double rttgamma;
	simtime_t timetotimeouts;
	unsigned int timetotimeouts_c;
	static double timetotimeouts_all;
	static double ttl_convtime;
	static double last_timetotimeouts_all;
	static double last_timetotimeouts_all_smoothed;
	static double timetotimeouts_all_smoothed;
	static unsigned int timetotimeouts_all_c;
	bool switched_rate;

	cMessage *incoming_timer;
	int incoming_total_bytes;
	cMessage *reset_measurement_timer;
	unsigned int curr_ack_sequence_id;
	cMessage *incoming_measurement_timer;

	//incromation about sent messages (for which the ack wasn't received yet)
	std::map<unsigned int, SSentMsg> sent_msgs;
	//the latencies between the nodes
	uppermatrix<SRtt> latencies;

	simtime_t next_resettime;
	static unsigned int incoming_bytes_m;
};

#endif /* SIMPLECC_H_ */
