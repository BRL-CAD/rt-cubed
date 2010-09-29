/*                       S E S S I O N . H
 * BRL-CAD
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
/** @file Session.h
 *
 * Brief description
 *
 */

#ifndef __SESSION_H__
#define __SESSION_H__

#include "Account.h"
#include <cstdlib>
#include <iostream>
#include <ios>
#include <fstream>

#include <QtCore/QUuid>

class Session
{
friend class SessionManager;
public:
    virtual ~Session();

    QUuid getSessionID();
    Account*  getAccount();

private:
    Session(Account* a);

    QUuid sessionID;
    Account* a;
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
