/*                   C O N F I G . H
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
/** @file Config.h
 *
 * Brief description
 *
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Logger.h"
#include <QMap>
#include <QString>

class Config
{

public:
	~Config();
	static Config* getInstance();

	bool loadFile(QString pathAndFileName);
	QString getConfigValue(QString key);
	QList<QString> getAllKeys();

private:
	Config(); //Turn off Default cstr
	Config(const Config& c){}; //Turn off Copy cstr
	Config& operator=(const Config& c){}; //Turn off equal oper
	void processLine(QString line);
	void removeAllOccurances(QString* data, QString search,
			QString replace);

	QMutex lock;
	Logger* log;
	QMap<QString, QString>* configMap;

	static Config* pInstance;

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
