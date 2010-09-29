/*               A C C O U N T M A N A G E R . C X X
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
/** @file AccountManager.cxx
 *
 * Interface to the SVN user system.
 *
 */

#ifndef __ACCOUNTMANAGER_H__
#define __ACCOUNTMANAGER_H__

#include "Session.h"
#include "INetMsgHandler.h"

#include <QtCore/QString>
#include <QtCore/QList>

class AccountManager : public INetMsgHandler
{

public:
    virtual ~AccountManager();
    static AccountManager* getInstance();
    Account* login(QString uname, QString passwd, Portal* p);
    bool handleNetMsg(NetMsg* msg);

private:
    static AccountManager* pInstance;
    AccountManager();


    QMutex accountListLock;
    QList<Account*>* accounts;
    quint32 validateLoginCreds(QString uname, QString passwd);

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
