/*             A B S T R A C T C L I E N T C M D . H
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
/** @file AbstractClientCmd.h
 * AbstractClientCmd.h
 *
 */

#ifndef __ABSTRACTCLIENTCMD_H__
#define __ABSTRACTCLIENTCMD_H__

#include "Logger.h"
#include "GSClient.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

class AbstractClientCmd {
public:
	virtual ~AbstractClientCmd();
	bool exec(GSClient* client, QStringList args);

	QString getCmd();
	virtual QString getUsage() = 0;
	virtual QString getHelp() = 0;

	void printUsage();
	void printHelp();

protected:
	AbstractClientCmd(QString cmd);
	AbstractClientCmd(AbstractClientCmd* acCmd);

	virtual bool _exec(GSClient* client, QStringList args) = 0;

	Logger* log;

private:
	QString cmd;
};

#endif /* __ABSTRACTCLIENTCMD_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
