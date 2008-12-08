///////////////////////////////////////////////////////////
//  AbstractResourceSource.cxx
//  Implementation of the Class AbstractDbObjectSource
//  Created on:      04-Dec-2008 8:26:34 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#include "AbstractResourceSource.h"

AbstractDbObjectSource::AbstractDbObjectSource() {

}

AbstractDbObjectSource::~AbstractDbObjectSource() {

}

DbObject& AbstractDbObjectSource::getDbObjectByURL(URL url) {

	return NULL;
}

bool AbstractDbObjectSource::putDbObject(DbObject& dbobj) {

	return false;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
