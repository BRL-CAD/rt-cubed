/*                   C O N F I G . H
 * BRL-CAD
 *
 * Copyright (c) 2011 United States Government as represented by
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
 * Configuration class that provides loading and storing of configuration Key/Value pairs.
 *
 */

#include "Config.h"
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QStringList>
#include <QtCore/QMutexLocker>

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
    if (!Config::pInstance) {
    	pInstance = new Config();
    }
    return Config::pInstance;
}

bool Config::loadFile(QString pathAndFileName, bool verbose)
{
    QString msg;
    msg = "Attemping to load config from: '" + pathAndFileName + "'.";
    this->log->logINFO("Config", msg);

    //init file object
    QFile f(pathAndFileName);

    if (f.exists() == false) {
		msg = "Could not find file: '" + pathAndFileName + "'.";
		this->log->logFATAL("Config", msg);
		return false;
    }


    //verify & open
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		msg = "Loading config from: '" + pathAndFileName + "' FAILED.";
		this->log->logFATAL("Config", msg);
		return false;
    }

    while (!f.atEnd()) {
		QByteArray lineBytes = f.readLine();

		QString line(lineBytes);

		//Rem newline:
		this->removeAllOccurances(&line, "\n", "");

		//Check for comments
		if (line[0] == '#') {
			//log->logINFO("Config", "Ignoring Comment. (" + line + ")");
		} else {
			QString key = this->processLine(line);

			if (verbose && key != NULL && key.length() > 0) {
				QString value = this->configMap->value(key);
				log->logINFO("Config", "Read key/value: '" + key + "'->'" + value + "'");
			}

		}
    }
    QFileInfo info(f);

    log->logINFO("Config", "Done loading config from: " + info.absoluteFilePath());
    return true;
}

QString
Config::processLine(QString line)
{
    //Process the string, clean it up.

    this->removeAllOccurances(&line, "\t", " ");
    this->removeAllOccurances(&line, "  ", " ");

    //Check for blankline
    if (line == "" || line == " ") {
	//this->log->logDEBUG("Config", "Empty Line");
	return "";
    }

    QStringList list = line.split(" ");
    if (list.length() < 2) {
	this->log->logERROR("Config",
		"Not enough elements for Key/Value pair on Config Line: "
			+ line);
	return "";
    }

    QString key = list[0];
    QString value = list[1];

    this->updateValue(key, value);
    return key;
}

void Config::removeAllOccurances(QString* data, QString search, QString replace)
{
    while (data->contains(search)) {
	*data = (*data).replace(search, replace);
    }
}

QString Config::getConfigValue(QString key)
{
	QMutexLocker(&this->mapLock);
    return this->configMap->value(key, "") + "";
}

void
Config::updateValue(QString key, QString value)
{
	QMutexLocker(&this->mapLock);
	this->configMap->insert(key, value);
}

QList<QString> Config::getAllKeys()
{
	QMutexLocker(&this->mapLock);
	return this->configMap->uniqueKeys();
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
