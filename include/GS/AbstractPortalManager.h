/*         A B S T R A C T P O R T A L M A N A G E R . H
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file AbstractPortalManager.h
 *
 * Brief description
 *
 */

#ifndef _ABSTRACTPORTALMANAGER_H_
#define _ABSTRACTPORTALMANAGER_H_

#include <iostream>
#include <list>
#include <map>

#include "GS/AbstractPortal.h"
#include "GS/netMsg/NetMsg.h"

class AbstractPortalManager
{

public:
  AbstractPortalManager();
  virtual ~AbstractPortalManager();

  void startListening(unsigned int port);

private:
  std::map<std::string, AbstractPortal> portals;
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
