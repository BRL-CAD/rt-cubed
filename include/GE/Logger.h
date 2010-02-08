/*                         L O G G E R . H
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
/** @file Logger.h
 *
 * Brief description
 *
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <QString>
#include <iostream>
#include <QMutex>
#include "GS/GSCommon.h"

class Logger
{

public:

	static Logger* getInstance();
	void writeStdOut(QString string);
	void writeStdErr(QString string);
	void log(quint32 logLevel, QString string);
	void enableVerbose(){this->verbose = true;}
	void disableVerbose(){this->verbose = false;}

	enum
	{
		INFO, WARNING, ERROR, FATAL
	};

private:
	bool verbose;
	QMutex lock;

	Logger();
	Logger(const Logger& logger){};
	Logger& operator=(const Logger& log){};
	~Logger(){};


};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
