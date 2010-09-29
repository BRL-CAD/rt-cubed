/*              F I L E D A T A S O U R C E . C X X
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
/** @file FileDataSource.cxx
 *
 * Brief description
 *
 */

#include "FileDataSource.h"

FileDataSource::FileDataSource(QString repoPath):repoPath(repoPath)
{
}

FileDataSource::~FileDataSource() {
}

bool
FileDataSource::lock(DbObject* obj, Account* a)
{
}
bool
FileDataSource::hasLock(DbObject* obj, Account* a)
{
}
bool
FileDataSource::unlock(DbObject* obj)
{
}

DbObject*
FileDataSource::getByPath(QString path)
{
}
DbObject*
FileDataSource::getByID(QUuid id)
{
}
bool
FileDataSource::putObject(DbObject* obj)
{
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
