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
#include <QMutexLocker>

SessionManager* SessionManager::pInstance = NULL;

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
}

SessionManager* SessionManager::getInstance()
{
	if (!SessionManager::pInstance)
	{
		pInstance = new SessionManager();
	}
	return SessionManager::pInstance;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
