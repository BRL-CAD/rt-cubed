/*                   S H U T D O W N C M D . H
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
/** @file ShutdownCmd.h
 * ShutdownCmd.h
 *
 */

#ifndef __SHUTDOWNCMD_H__
#define __SHUTDOWNCMD_H__

#include "AbstractClientCmd.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

class ShutdownCmd : public AbstractClientCmd {
public:
	ShutdownCmd();
	virtual ~ShutdownCmd();

	QString getUsage();
	QString getHelp();

protected:
	bool _exec(QStringList args);

};

#endif /* __SHUTDOWNCMD_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
