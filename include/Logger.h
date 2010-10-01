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

#include <iostream>

#include <QtCore/QThread>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class Logger
{
public:
	static Logger* getInstance();
	virtual ~Logger(){};

	void enableVerbose()
	{
		this->verbose = true;
	}
	void disableVerbose()
	{
		this->verbose = false;
	}

	void enableLogToConsole()
	{
		this->printToConsole = true;
	}
	void disableLogToConsole()
	{
		this->printToConsole = false;
	}

	void enableLogToFile()
	{
		this->printToFile = true;
	}
	void disableLogToFile()
	{
		this->printToFile = false;
	}

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

private:
	static Logger* instance;
	static QMutex* lock;
	bool verbose;
	bool printToConsole;
	bool printToFile;

	Logger();
	Logger(const Logger& logger){};
	Logger& operator=(const Logger& log){};

	void log(quint32 logLevel, QString origin, QString string);
};

#endif /* __LOGGER_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
