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

#ifndef DATATEST_H_
#define DATATEST_H_

#include <BaseApp.h>

/**
 * Class for sending as much data as possible from node to node
 */
class DataTest : public BaseApp
{
public:
	DataTest();
	virtual ~DataTest();

	void initializeApp(int stage);                 // called when the module is being created
	void finishApp();                              // called when the module is about to be destroyed
	void handleTimerEvent(cMessage* msg);          // called when we received a timer message
	void deliver(OverlayKey& key, cMessage* msg);  // called when we receive a message from the overlay
	void handleUDPMessage(cMessage* msg);          // called when we receive a UDP message

private:
	//timer for sending messages
	cMessage *outgoing_timer;
	//timer for checking if enough messages are send
	cMessage *cong_test_timer;

	//last time the connection was saturated
	simtime_t last_cong;
	//intervall between messages sent
	double outgoing_intervall;
	//number of messages sent at once
	int outgoing_count;
	//size of the message to be sent
	int outgoing_size;
	//number of used nodes
	int largestKey;
	//send only frm this node (usefull for testing)
	int sendonlyfrom;

	double actIntervall;
	bool activated;
};

#endif /* DATATEST_H_ */
