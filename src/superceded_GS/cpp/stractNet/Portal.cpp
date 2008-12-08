///////////////////////////////////////////////////////////
//  Portal.cpp
//  Implementation of the Class Portal
//  Created on:      06-Aug-2008 7:50:30 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "Portal.h"


Portal::Portal(){

}



Portal::~Portal(){

}





Portal::Portal(String Name, PortalManager pm, SocketChannel sockChan){

}


Portal::Portal(String Name, PortalManager pm, SocketChannel sockChan, MessagingSystem ms){

}


void Portal::finishDisconnect(){

}


String Portal::getRemoteHostName(){

	return RemoteHostName;
}


SocketChannel Portal::getSockChan(){

	return  NULL;
}


void Portal::PortalSetRemoteHostName(StdMsg sm){

}


void Portal::Send(StdMsg sm){

}


void Portal::SendHostInfo(){

}


void Portal::SendToMS(StdMsg sm){

}


void Portal::SendToRemHost(StdMsg sm){

}