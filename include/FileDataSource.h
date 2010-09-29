/*                F I L E D A T A S O U R C E . H
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
/** @file FileDataSource.h
 *
 * Brief description
 *
 */

#ifndef __FILEDATASOURCE_H__
#define __FILEDATASOURCE_H__

#include "IDataSource.h"

#include <QtCore/QMutex>

class FileDataSource: public IDataSource {
public:
	FileDataSource(QString repoPath);
	virtual ~FileDataSource();

	bool lock(DbObject* obj, Account* a);
	bool hasLock(DbObject* obj, Account* a);
	bool unlock(DbObject* obj);

	DbObject* getByPath(QString path);
	DbObject* getByID(QUuid id);
	bool putObject(DbObject* obj);

private:
	QString repoPath;

	QMutex lockLock;
	QList<QString> pathLocks;
	bool hasPathLock(QString path);
	void setPathLock(QString path);
	void remPathLock(QString path);

};

#endif /* __FILEDATASOURCE_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
