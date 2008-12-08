///////////////////////////////////////////////////////////
//  AbstractResourceSource.cpp
//  Implementation of the Class AbstractDbObjectSource
//  Created on:      04-Dec-2008 8:26:34 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "AbstractResourceSource.h"


AbstractDbObjectSource::AbstractDbObjectSource(){

}



AbstractDbObjectSource::~AbstractDbObjectSource(){

}





DbObject& AbstractDbObjectSource::getDbObjectByURL(URL url){

	return  NULL;
}


bool AbstractDbObjectSource::putDbObject(DbObject& dbobj){

	return false;
}