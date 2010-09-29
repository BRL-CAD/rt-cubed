/*                      D B O B J E C T . H
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
/** @file DbObject.h
 * DbObject.h
 *
 *  Created on: Sep 29, 2010
 *      Author: dloman
 */

#ifndef DBOBJECT_H_
#define DBOBJECT_H_

#include <QtCore/QString>
#include <QtCore/QUuid>
#include <QtCore/QByteArray>

class DbObject {
public:
	DbObject(QString path, QByteArray* data);
	DbObject(QUuid id, QByteArray* data);
	virtual ~DbObject();

	QString getPath();
	QUuid getID();
	QByteArray* getData();

private:
	QString path;
	QUuid id;
	QByteArray* data;
};

#endif /* DBOBJECT_H_ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
