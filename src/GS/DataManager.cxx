/*             D A T A M A N A G E R . C X X
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
/** @file DataManager.cxx
 *
 * Single point of access for all Database
 * object IO from SVN, Cache and Disk
 *
 */

#include "DataManager.h"
#include "NetMsgTypes.h"

#include <QtCore/QMutexLocker>

DataManager* DataManager::pInstance = NULL;

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

QString DataManager::getDbObjectByURL(QString url)
{
}

QString DataManager::getDbObjectByUUID(QUuid& uuid)
{
}

void
DataManager::addDataSource(IDataSource* source)
{
	QMutexLocker lock (&this->sourceLock);
	this->datasources.append(source);
}

bool
DataManager::handleNetMsg(NetMsg* msg)
{
	quint16 type = msg->getMsgType();
	switch(type) {
	case GEOMETRYREQ:
		return true;
	case GEOMETRYMANIFEST:
		return true;
	case GEOMETRYCHUNK:
		return true;
	}
	return false;
}

DataManager* DataManager::getInstance()
{
	if (!DataManager::pInstance)
	{
		DataManager::pInstance = new DataManager();
	}
	return DataManager::pInstance;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
