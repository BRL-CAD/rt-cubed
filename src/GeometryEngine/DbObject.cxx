///////////////////////////////////////////////////////////
//  AbstractResource.cpp
//  Implementation of the Class DbObject
//  Created on:      04-Dec-2008 8:26:39 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#include "GeometryEngine/DbObject.h"

DbObject::DbObject() {

}

DbObject::~DbObject() {

}

DbObject::DbObject(long id, string name, unsigned int geoType, bool locked) {

}

string DbObject::getName() {

	return NULL;
}

void DbObject::setName(string name) {

}

unsigned int DbObject::getGeoType() {

	return 0;
}

void DbObject::setGeoType(unsigned int geoType) {

}

void DbObject::lock() {

}

void DbObject::unlock() {

}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
