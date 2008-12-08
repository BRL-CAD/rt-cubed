///////////////////////////////////////////////////////////
//  PlaceboMessageServer.cpp
//  Implementation of the Class PlaceboMessageServer
//  Created on:      06-Aug-2008 8:00:39 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "PlaceboMessageServer.h"


PlaceboMessageServer::PlaceboMessageServer(){

}



PlaceboMessageServer::~PlaceboMessageServer(){

}





PlaceboMessageServer::PlaceboMessageServer(String name, InetAddress host, int port, int[] ocsInUseA, int mtiA, long delayA, int[] ocsInUseB, int mtiB, long delayB) throw IOException{

}


MessageDispatcher PlaceboMessageServer::getMD(){

	return MD;
}


PlaceboMsgStoppableClass PlaceboMessageServer::getMsgStopObj01(){

	return MsgStopObj01;
}


PlaceboMsgStoppableClass PlaceboMessageServer::getMsgStopObj02(){

	return MsgStopObj02;
}


int PlaceboMessageServer::getMTsInUseA(){

	return MTsInUseA;
}


int PlaceboMessageServer::getMTsInUseB(){

	return MTsInUseB;
}


PortalManager PlaceboMessageServer::getPortMan(){

	return PortMan;
}


STRunManager PlaceboMessageServer::getRunMan(){

	return  NULL;
}


void PlaceboMessageServer::printAllHosts(){

}


void PlaceboMessageServer::start(){

}