/*           C L I E N T C M D R E G I S T R Y . C X X
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
/** @file ClientCmdRegistry.cxx
 *
 * Brief description
 *
 */


#include "ClientCmdRegistry.h"
#include <QtCore/QMutexLocker>

ClientCmdRegistry* ClientCmdRegistry::pInstance = NULL;

ClientCmdRegistry*
ClientCmdRegistry::getInstance() {
	if (ClientCmdRegistry::pInstance == NULL) {
		ClientCmdRegistry::pInstance = new ClientCmdRegistry();
		ClientCmdRegistry::pInstance->registerInternalCmds();
	}
	return ClientCmdRegistry::pInstance;
}

ClientCmdRegistry::ClientCmdRegistry() {
	this->cmdMap = new QMap<QString,AbstractClientCmd*> ();
	this->log = Logger::getInstance();
}

ClientCmdRegistry::~ClientCmdRegistry() {
	/* TODO loop thru and del all the CMDs?? */
	delete cmdMap;
}

bool ClientCmdRegistry::registerCmd(AbstractClientCmd* cmd) {
	QString cmdString = cmd->getCmd();

	QMutexLocker(&this->mapLock);
	if (this->cmdMap->contains(cmdString) == false) {
		this->cmdMap->insert(cmdString, cmd);
		return true;
	}

	this->log->logWARNING("ClientCmdRegistry","An AbstractClientCmd '" + cmdString + "' already exists in Registry.");
	return false;
}

AbstractClientCmd*
ClientCmdRegistry::getCmd(QString cmd)
{

}

QList<QString>*
ClientCmdRegistry::getListOfCmds() {
	QMutexLocker(&this->mapLock);

	QList<QString>* keys = new QList<QString>(this->cmdMap->keys());

	return keys;
}

void
ClientCmdRegistry::registerInternalCmds()
{
	/* TODO add in any cmds that should be automatically mapped here. */
}

/*
 * Local Variables:
 * mode: C
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */

