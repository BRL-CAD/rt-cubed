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

#include "utility/Config.h"
#include <QFile>
#include <QStringList>

Config* Config::pInstance = NULL;

Config::Config()
{
	this->configMap = new QMap<QString, QString> ();
	this->log = Logger::getInstance();
}

Config::~Config()
{
	delete this->configMap;
}

Config* Config::getInstance()
{
	if (!Config::pInstance)
	{
		pInstance = new Config();
	}
	return Config::pInstance;
}

bool Config::loadFile(QString pathAndFileName)
{
	QString msg;
	msg = "Attemping to load config from: " + pathAndFileName + ".\n";
	this->log->logINFO("Config", msg);

	//init file object
	QFile f(pathAndFileName);

	//verify & open
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		msg = "Loading config from: " + pathAndFileName + " FAILED.\n";
		this->log->logFATAL("Config", msg);
		return false;
	}

	log->logINFO("Config", "File found.");

	while (!f.atEnd())
	{
		QByteArray lineBytes = f.readLine();

		QString line(lineBytes);

		//Check for comments
		if (line[0] == '#')
		{
			log->logINFO("Config", "Comment.");
		}
		else
		{
			this->processLine(line);
		}
	}
	log->logINFO("Config", "Done.");
}

void Config::processLine(QString line)
{
	//Process the string, clean it up.
	this->removeAllOccurances(&line, "\t", " ");
	this->removeAllOccurances(&line, "  ", " ");
	this->removeAllOccurances(&line, "\n ", "\n");
	this->removeAllOccurances(&line, " \n", "\n");

	//Check for blankline
	if (line == "\n") {
		//this->log->logDEBUG("Config", "Empty Line");
		return;
	}

	QStringList list = line.split(" ");
	if (list.length() <2) {
		this->log->logERROR("Config", "Invalid Config Line: " + line);
		return;
	}

	QString key = list[0];
	QString value = list[1];

	this->log->logINFO("Config", "Key: " + key);

	if (key == "\n")
	{
		//ignore
		return;
	}
}

void Config::removeAllOccurances(QString* data, QString search,
		QString replace)
{
	while (data->contains(search))
	{
		*data = (*data).replace(search, replace);
	}

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
