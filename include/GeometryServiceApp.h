/*            G E O M E T R Y S E R V I C E A P P . H
 * BRLCAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file GeometryServiceApp.h
 *
 * Brief description
 *
 */


#ifndef __GEOMETRYSERVICEAPP_H__
#define __GEOMETRYSERVICEAPP_H__

#include "BaseApp.h"
#include "GeometryService.h"

class GeometryServiceApp :  public BaseApp
{

public:
    GeometryServiceApp(int& argc, char* argv[], GeometryService* gs);
    virtual ~GeometryServiceApp(){};
    GeometryService* getGeometryService();

protected:

private:
    GeometryService* gs;
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
