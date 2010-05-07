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

#include "SessionManager.h"
#include "AccountManager.h"
#include "libnetwork.h"
#include "libutility.h"
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

void SessionManager::handleNetMsg(NetMsg* msg, NetPortal* origin)
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

	    if (accountID > 0) {
		Session* session = this->newSession(accountID);
		this->sessionIdMap->insert(accountID, session);

		// use reply cstr.
		SessionInfoMsg siMsg(msg, session->getSessionID() );

		//Send back reply
		origin->send(siMsg);
	    } else {
		FailureMsg fMsg(msg, AUTHENTICATION_FAILED);

		//Send back reply
		origin->send(fMsg);
	    }

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
