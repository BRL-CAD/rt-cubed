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
#include "NetMsgTypes.h"
#include "libutility.h"
#include "GenericOneByteMsg.h"

#include <QtCore/QMutexLocker>

SessionManager* SessionManager::pInstance = NULL;

SessionManager::SessionManager()
{
    this->log = Logger::getInstance();
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


Session*
SessionManager::newSession(Account* a)
{
	Session* s = NULL;

	//check to see if its already cached.
    s = this->getSession(a);

    if (s != 0) {
    	s->stampLastAccess();
    } else {
    	//New
		s = new Session(a);

		//cache
		this->mapsLock.lock();
		this->sessionList.append(s);
		this->mapsLock.unlock();

    }
    return s;
}

Session*
SessionManager::getSession(Account* a) {
	QMutexLocker locker(&this->mapsLock);
	for (int i = 0; i < this->sessionList.size(); ++i) {
		Session* s = this->sessionList[i];
		if (s->getAccount() == a)
			return s;
	}
	return NULL;
}

//TODO need to verify the QUuid == QUuid works.
Session*
SessionManager::getSession(QUuid sessID) {
	QMutexLocker locker(&this->mapsLock);
	for (int i = 0; i < this->sessionList.size(); ++i) {
		Session* s = this->sessionList[i];
		if (s->getSessionID() == sessID)
			return s;
	}
	return NULL;
}

Session*
SessionManager::getSession(Portal* p) {
	QMutexLocker locker(&this->mapsLock);
	for (int i = 0; i < this->sessionList.size(); ++i) {
		Session* s = this->sessionList[i];
		if (s->getAccount()->getPortal() == p)
			return s;
	}
	return NULL;
}

bool
SessionManager::handleNetMsg(NetMsg* msg)
{
	quint16 type = msg->getMsgType();
	switch(type) {
	case NEWSESSIONREQ:
		this->handleNewSessionReqMsg((NewSessionReqMsg*)msg);
		break;
	case SESSIONINFO:
		//Dunno why someone would be sending the GS this message!
		break;
	case DISCONNECTREQ:
		this->handleDisconnectReqMsg((TypeOnlyMsg*)msg);
		break;

	}
}

/*
 * Msg Handlers
 */
void SessionManager::handleNewSessionReqMsg(NewSessionReqMsg* msg)
{
	Portal* origin = msg->getOrigin();
	QString uname = msg->getUName();
	QString passwd = msg->getPasswd();

	//validate incoming data
	if (origin == 0) {
		//TODO Figure out how to how to handle NULL Portal
		log->logERROR("SessionManager", "NULL Portal!");
		return;
	}

	if (uname.length() <=0 || passwd.length() <= 0) {
		log->logINFO("SessionManager", "Auth FAILED.  Zero len uname or passwd.");
		GenericOneByteMsg* fail = new GenericOneByteMsg(FAILURE, ACCOUNT_VALIDATION_FAIL);
		origin->send(fail);
		return;
	}

	//try to validate creds
	Account* a = AccountManager::getInstance()->login(msg->getUName(), msg->getPasswd(), msg->getOrigin());

	if (a == 0) {
		//Account validation failed
		GenericOneByteMsg* fail = new GenericOneByteMsg(FAILURE, ACCOUNT_VALIDATION_FAIL);
		origin->send(fail);
		return;
	}

	//Make new session
	Session* s = this->newSession(a);

	//tell client about it.
	SessionInfoMsg* info = s->generateSessionInfoMsg();
	origin->send(info);

}

void
SessionManager::handleDisconnectReqMsg(TypeOnlyMsg* msg)
{

}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
