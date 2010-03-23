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
/** @file Config.cxx
 *
 * Brief description
 *
 */

#include "GS/Config.h"
#include <QFile>
#include <QStringList>

Config::Config()
{
    this->configMap = new QMap<QString, QString> ();
    this->log = Logger::getInstance();
}

Config::~Config()
{
    delete this->configMap;
}

bool Config::loadFile(QString pathAndFileName)
{
    QString msg;
    msg = "Attemping to load config from: " + pathAndFileName + ".\n";
    this->log->logINFO(msg);

    //init file object
    QFile f(pathAndFileName);

    //verify & open
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
	msg = "Loading config from: " + pathAndFileName + " FAILED.\n";
	this->log->logFATAL(msg);
	return false;
    }

    while (!f.atEnd()) {
	QByteArray line = f.readLine();

	if (!line[0] == '#') {
	    this->processLine(line);
	}
    }

}

void Config::processLine(QByteArray inLine)
{
    //Process the string, clean it up.
    QString line(inLine);

    while (line.contains("\t")) {
	line = line.replace("\t", " ");
    }

    while (line.contains("  ")) {
	line = line.replace("  ", " ");
    }

    QStringList list = line.split(" ");

}

QString Config::getConfigValue(QString key)
{
    return this->configMap->value(key, "");
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
