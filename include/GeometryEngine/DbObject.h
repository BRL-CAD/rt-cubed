///////////////////////////////////////////////////////////
//  AbstractResource.h
//  Implementation of the Class DbObject
//  Created on:      04-Dec-2008 8:26:39 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__DBOBJECT_H__)
#define __DBOBJECT_H__

#include <iostream>
#include <list>
#include "iBMECommon.h"

using namespace std;


class DbObject {

public:
  DbObject();
  virtual ~DbObject();

  DbObject(long id, string name, unsigned int geoType, bool locked =
			false);
	string getName();
	void setName(string name);
	unsigned int getGeoType();
	void setGeoType(unsigned int geoType);
	void lock();
	void unlock();

private:
	string name;
	UUID uuid;
	list<DbObject> parents;
	list<DbObject> children;
	int geoType;

};
#endif // !defined(__DBOBJECT_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
