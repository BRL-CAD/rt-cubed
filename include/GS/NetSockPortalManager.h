/*          N E T S O C K P O R T A L M A N A G E R . H
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
/** @file NetSockPortalManager.h
 *
 * Brief description
 *
 */
#ifndef _NETSOCKPORTALMANAGER_H_
#define _NETSOCKPORTALMANAGER_H_

#include "GS/AbstractPortalManager.h"

class NetSockPortalManager : public AbstractPortalManager
{

public:
    NetSockPortalManager();
    ~NetSockPortalManager();

protected:


private:


};

#endif


/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
