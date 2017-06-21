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

#include "DataTest.h"
#include "DataMsg_m.h"
#include "../../overlay/basic/BasicCC.h"
#include <UnderlayConfigurator.h>
#include <iostream>

Define_Module(DataTest);

double g_nextAct=0;
int nextActId=1;


DataTest::DataTest() {
	// TODO Auto-generated constructor stub


}

DataTest::~DataTest() {
	// TODO Auto-generated destructor stub
}

/**
 * Initialize the module
 */
void DataTest::initializeApp(int stage)
{
	if (stage != MIN_STAGE_APP) return;

	bindToPort(2000);

	outgoing_intervall=par("outgoing_intervall");
	outgoing_size=par("outgoing_size");
	largestKey=par("largestKey");
	sendonlyfrom=par("sendonlyfrom");
	outgoing_count=par("outgoing_count");
	actIntervall=par("actIntervall");

	if(actIntervall!=0)
	{
		g_nextAct=simTime().dbl();
		activated=false;
	}
	else
	{
		activated=true;
	}

	outgoing_timer = new cMessage("outgoing timer");
	cong_test_timer=new cMessage("cong test timer");
	last_cong=simTime();
	scheduleAt(simTime() + outgoing_intervall, outgoing_timer);
	scheduleAt(simTime()+1, cong_test_timer);
}

void DataTest::finishApp()
{
	//delete outgoing_timer;
}

/**
 * handle timers
 */
void DataTest::handleTimerEvent(cMessage *msg)
{
	//send a message
	if(msg==outgoing_timer)
	{
		//don't send in init phase
		if (underlayConfigurator->isInInitPhase())
		{
			scheduleAt(simTime() + 0.1, msg);
			return;
		}


		//get the own address
		BasicCC *basiccc=check_and_cast<BasicCC*>(overlay);
		size_t h=basiccc->getKey();
		if(sendonlyfrom>=0 && h!=(size_t)sendonlyfrom)
			return;

		if(activated==false && nextActId==(int)h && simTime().dbl()>g_nextAct)
		{
			activated=true;
			++nextActId;
			g_nextAct=simTime().dbl()+actIntervall;
		}

		if(!activated)
		{
			scheduleAt(simTime() + outgoing_intervall, msg);
			return;
		}

		//check if there's still capacity free
		if(!basiccc->hasCapacity(outgoing_size+58))
		{
			if(basiccc->getNextResetTime()>simTime())
				scheduleAt(basiccc->getNextResetTime(), msg);
			else
				scheduleAt(simTime() + outgoing_intervall, msg);
			last_cong=simTime();
			return;
		}
		else
		{
			scheduleAt(simTime() + outgoing_intervall, msg);
		}
		//send outgoing_count messages
		for(int i=0;i<outgoing_count;++i)
		{
			//Send the message to a random node (no self messages)
			OverlayKey randomKey(intuniform(1, largestKey));

			EV << "Sending message...";
			while(randomKey.hash()==h)
				randomKey=OverlayKey(intuniform(1,largestKey));

			DataMsg *nmsg=new DataMsg();
			nmsg->setType(DATATEST_DATA);
			nmsg->setByteLength(outgoing_size);

			callRoute(randomKey, nmsg, TransportAddress::UNSPECIFIED_NODE, FULL_RECURSIVE_ROUTING);
		}
	}
	else if(msg==cong_test_timer)
	{
		//Check if the connection was saturated
		scheduleAt(simTime()+1, cong_test_timer);

		if(simTime()-last_cong>1)
		{
			BasicCC *basiccc=check_and_cast<BasicCC*>(overlay);
			size_t h=basiccc->getKey();
			//std::cout << "Warning: Node " <<h << " not congested" << std::endl;
		}
	}
	else
	{
		delete msg;
	}
}

void DataTest::deliver(OverlayKey & key, cMessage *msg)
{
	DataMsg *dmsg=dynamic_cast<DataMsg*>(msg);
	if(dmsg==NULL)
	{
		delete dmsg;
		return;
	}

	delete msg;
}

void DataTest::handleUDPMessage(cMessage *msg)
{
	delete msg;
}










