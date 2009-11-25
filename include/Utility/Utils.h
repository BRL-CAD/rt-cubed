/*                       U T I L S . H
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file Utils.h
 *
 * Brief description
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include "iBME/iBMECommon.h"
#include <QString>
#include <QDataStream>
#include <QUuid>

class Utils
{
public:
static QString* getString(QDataStream* ds);
static void putString(QDataStream* ds, QString str);
static QUuid* getQUuid(QDataStream* ds);
static void putQUuid(QDataStream* ds, QUuid str);
static void printQByteArray(QByteArray* ba);


private:
Utils(){}

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
