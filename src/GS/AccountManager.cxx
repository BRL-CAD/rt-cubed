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
#include <cstdlib>

AccountManager* AccountManager::pInstance = NULL;

AccountManager::AccountManager()
{
}

AccountManager::~AccountManager()
{
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
    if (uname == "Kiaser" && passwd == "Sose") {
	return true;
    }
    return false;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8