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

#include <QThread>
#include <QString>
#include <QMutex>
#include <QMutexLocker>

#include <iostream>


class Logger
{

public:
	static Logger* getInstance();

	void enableVerbose(){this->_verbose = true;}
	void disableVerbose(){this->_verbose = false;}

	void enableLogToStdOut(){this->_toStdOut = true;}
	void disableLogToStdOut(){this->_toStdOut = false;}

	void enableLogToFile(){this->_toFile = true;}
	void disableLogToFile(){this->_toFile = false;}



	void logBANNER(QString origin, QString string);
	void logDEBUG(QString origin, QString string);
	void logINFO(QString origin, QString string);
	void logWARNING(QString origin, QString string);
	void logERROR(QString origin, QString string);
	void logFATAL(QString origin, QString string);

	enum
	{
		BANNER, INFO, WARNING, ERROR, FATAL, DEBUG
	};

protected:
	static Logger* instance;
	static QMutex* lock;
	bool _verbose;
	bool _toStdOut;
	bool _toFile;

	Logger();
	Logger(const Logger& logger){};
	Logger& operator=(const Logger& log){};
	~Logger(){};

	void log(quint32 logLevel, QString origin, QString string);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
