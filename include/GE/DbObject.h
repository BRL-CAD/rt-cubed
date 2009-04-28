/*                 D B O B J E C T . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/** @file DbObject.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_DBOBJECT_H_)
#define _DBOBJECT_H_

#include <iostream>
#include <list>
#include "iBME/iBMECommon.h"

class DbObject {

public:
  DbObject();
  virtual ~DbObject();

  DbObject(unsigned long id, std::string name, unsigned int geoType, bool locked = false);
  std::string getName();
  void setName(std::string name);
  unsigned int getGeoType();
  void setGeoType(unsigned int geoType);
  void lock();
  void unlock();

private:
  std::string name;
  UUID uuid;
  std::list<DbObject> parents;
  std::list<DbObject> children;
  unsigned int geoType;

};

#endif // !defined(_DBOBJECT_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
