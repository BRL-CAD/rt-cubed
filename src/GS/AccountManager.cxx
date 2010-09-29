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

#include "AccountManager.h"
#include "SessionManager.h"

#include <cstdlib>

AccountManager* AccountManager::pInstance = NULL;

AccountManager::AccountManager()
{
	this->accounts = new QList<Account*>();
	this->log = Logger::getInstance();
}

AccountManager::~AccountManager()
{
	delete this->accounts;
}

AccountManager* AccountManager::getInstance()
{
    if (!AccountManager::pInstance) {
    	pInstance = new AccountManager();
    }
    return AccountManager::pInstance;
}

/**
 * returns 0 for bad login.  Positive number is the accountID
 */
quint32 AccountManager::validateLoginCreds(QString uname, QString passwd)
{
	//TODO put in REAL account validation here.
    if (uname == "Guest" && passwd == "Guest") {
    	return 0;
    }
    if (uname == "Keyser" && passwd == "Soze") {
    	return 1;
    }
    if (uname == "Dean" && passwd == "Keaton") {
    	return 2;
    }
    if (uname == "Michael" && passwd == "McManus") {
    	return 3;
    }
    if (uname == "Fred" && passwd == "Fenster") {
    	return 4;
    }
    if (uname == "Todd" && passwd == "Hockney") {
    	return 5;
    }
    if (uname == "Roger" && passwd == "Kint") {
    	return 6;    static quint32 nextID;
    }

    return -1;
}

Account* AccountManager::login(QString uname, QString passwd, Portal* p)
{
	quint32 id = this->validateLoginCreds(uname, passwd);

	if (id <= 0) {
		log->logINFO("AccountManager", "Authentication FAILED. User: '" + uname + "'");
		return NULL;
	}

	log->logINFO("AccountManager", "Authenticated user: '" + uname + "'");

	Account* acc = new Account(uname, p, id);

	//TODO cache account here.
	QMutexLocker locker(&this->accountListLock);
	this->accounts->append(acc);

	return acc;
}

bool
AccountManager::handleNetMsg(NetMsg* msg)
{

}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
