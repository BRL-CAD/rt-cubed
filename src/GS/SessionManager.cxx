/*              S E S S I O N M A N A G E R . C X X
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
/** @file SessionManager.cxx
 *
 * Provides management functions for active Sessions.
 *
 */

#include "GS/SessionManager.h"
#include "GS/AccountManager.h"
#include "libNetwork/NewSessionReqMsg.h"
#include "utility/GSException.h"
#include <QMutexLocker>

SessionManager* SessionManager::pInstance = NULL;

SessionManager::SessionManager()
{
    this->sessionIdMap = new QMap<quint32, Session*> ();
}

SessionManager::~SessionManager()
{
}

SessionManager* SessionManager::getInstance()
{
    if (!SessionManager::pInstance) {
	pInstance = new SessionManager();
    }
    return SessionManager::pInstance;
}

void SessionManager::handleNetMsg(NetMsg* msg)
{
    quint32 msgType = msg->getMsgType();

    switch (msgType) {

    case (NEWSESSIONREQ):
	{
	    NewSessionReqMsg* nstMsg = (NewSessionReqMsg*) msg;

	    QString uname = nstMsg->getUName();
	    QString passwd = nstMsg->getPasswd();

	    quint32 accountID =
		    AccountManager::getInstance()->validateLoginCreds(uname,
			    passwd);

	    Session* session = this->newSession(accountID);

	    break;
	}
    default:
	{
	    throw new GSException("Does not handle this MsgType");
	    break;
	}
    };

}
Session* SessionManager::newSession(quint32 accountID)
{
    Session* s = new Session(accountID);

    return s;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
