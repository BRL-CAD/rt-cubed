///////////////////////////////////////////////////////////
//  PortalManager.cpp
//  Implementation of the Class PortalManager
//  Created on:      06-Aug-2008 7:38:20 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "PortalManager.h"


PortalManager::PortalManager(){

}



PortalManager::~PortalManager(){

}





PortalManager::PortalManager(String Name, InetAddress hostAddress, int port) throw IOException{

}


PortalManager::PortalManager(String Name, InetAddress hostAddress, int port, MessagingSystem ms) throw IOException{

}


void PortalManager::accept(SelectionKey key) throw IOException{

}


SocketChannel PortalManager::ConnectTo(InetAddress host, int port){

	return  NULL;
}


Portal PortalManager::CreateNewPortal(SocketChannel sockChan){

	return  NULL;
}


boolean PortalManager::disconnect(SelectionKey key) throw IOException{

	return  NULL;
}


boolean PortalManager::disconnect(SocketChannel sockChan) throw IOException{

	return  NULL;
}


boolean PortalManager::disconnectFrom(String host) throw IOException{

	return  NULL;
}


boolean PortalManager::disconnectFrom(Portal p) throw IOException{

	return  NULL;
}


boolean PortalManager::disconnectFrom(InetAddress ip, int Port) throw IOException{

	return  NULL;
}


void PortalManager::finishConnection(SelectionKey key) throw IOException{

}


int PortalManager::getNewPortalNumber(){

	return 0;
}


boolean PortalManager::getRunCmd(){

	return  NULL;
}


boolean PortalManager::getRunStatus(){

	return  NULL;
}


Thread PortalManager::getThread(){

	return  NULL;
}


SocketChannel PortalManager::initiateConnection(InetAddress host, int port) throw IOException{

	return  NULL;
}


Selector PortalManager::initSelector() throw IOException{

	return  NULL;
}


void PortalManager::read(SelectionKey key) throw IOException{

}


void PortalManager::run(){

}


void PortalManager::send(SocketChannel sockChan, byte[] data){

}


void PortalManager::start(){

}


void PortalManager::stop(){

}


void PortalManager::write(SelectionKey key) throw IOException{

}