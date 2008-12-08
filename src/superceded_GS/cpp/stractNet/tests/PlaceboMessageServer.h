///////////////////////////////////////////////////////////
//  PlaceboMessageServer.h
//  Implementation of the Class PlaceboMessageServer
//  Created on:      06-Aug-2008 8:00:39 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_80A798B4_9ED6_48bb_8209_B431510B4810__INCLUDED_)
#define EA_80A798B4_9ED6_48bb_8209_B431510B4810__INCLUDED_

#include "MessageDispatcher.h"
#include "PlaceboMsgStoppableClass.h"
#include "PortalManager.h"
#include "STRunManager.java"
#include "SNRoot.h"

class PlaceboMessageServer : public SNRoot
{

public:
	PlaceboMessageServer();
	virtual ~PlaceboMessageServer();

	PlaceboMessageServer(String name, InetAddress host, int port, int[] ocsInUseA, int mtiA, long delayA, int[] ocsInUseB, int mtiB, long delayB) throw IOException;
	MessageDispatcher getMD();
	PlaceboMsgStoppableClass getMsgStopObj01();
	PlaceboMsgStoppableClass getMsgStopObj02();
	int getMTsInUseA();
	int getMTsInUseB();
	PortalManager getPortMan();
	STRunManager getRunMan();
	void printAllHosts();
	void start();

private:
	MessageDispatcher MD;
	PlaceboMsgStoppableClass MsgStopObj01;
	PlaceboMsgStoppableClass MsgStopObj02;
	int MTsInUseA[];
	int MTsInUseB[];
	PortalManager PortMan;
	STRunManager STRM;

};
#endif // !defined(EA_80A798B4_9ED6_48bb_8209_B431510B4810__INCLUDED_)
