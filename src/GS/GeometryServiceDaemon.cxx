/*       G E O M E T R Y S E R V I C E D A E M O N . C X X
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
/** @file GeometryServiceDaemon.cxx
 *
 * Brief description
 *
 */

#include "GeometryServiceDaemon.h"

GeometryServiceDaemon::GeometryServiceDaemon(GeometryServiceApp* gsa) : gsa(gsa)
{
}

void GeometryServiceDaemon::run()
{
    int retVal = this->gsa->exec();
}

void GeometryServiceDaemon::stop()
{
    this->gsa->getGeometryService()->stopListening();
    this->terminate();
}

GeometryServiceApp* GeometryServiceDaemon::getGeometryServiceApp()
{
    return this->gsa;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
