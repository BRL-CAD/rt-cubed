/*                         L O G G E R . C X X
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
/** @file Logger.cxx
 *
 * Brief description
 *
 */

#include "GE/Logger.h"
#include <QTime>

//Statics instantiation
Logger* Logger::instance;
QMutex* Logger::lock = new QMutex();

Logger::Logger()
{
    this->verbose = true; //Default to true
}
Logger* Logger::getInstance()
{
    QMutexLocker locker(Logger::lock);

    if (Logger::instance == NULL) {
	Logger::instance = new Logger();
    }

    return Logger::instance;
}

void Logger::log(quint32 logLevel, QString string)
{
    QMutexLocker locker(Logger::lock);

    QString out("");

    out += QTime::currentTime().toString();
    out += ": ";

    switch (logLevel) {
    case (Logger::FATAL):
	out += "(FATAL) ";
	break;
    case (Logger::ERROR):
	out += "(ERROR) ";
	break;
    case (Logger::WARNING):
	out += "(WARNING) ";
	break;
    case (Logger::INFO):
    default:
	out += "(INFO) ";
	break;
    }

    out += string;

    //TODO add file logging

    if (this->verbose) {
	std::cout << out.toStdString();
    }

}

void Logger::writeStdOut(QString string)
{
    QMutexLocker locker(Logger::lock);
    std::cout << string.toStdString();

}

void Logger::writeStdErr(QString string)
{
    QMutexLocker locker(Logger::lock);
    std::cerr << string.toStdString();

}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
