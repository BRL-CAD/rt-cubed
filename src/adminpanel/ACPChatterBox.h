/*             A C P C H A T T E R B O X . H
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
/** @file ACPChatterBox.h
 *
 *
 *
 */

#ifndef __ACPCHATTERBOX_H__
#define __ACPCHATTERBOX_H__

#include <QTableView>
#include <QString>
#include <QStandardItemModel>

class ACPChatterBox: public QTableView
{
public:
	ACPChatterBox();
	virtual ~ACPChatterBox();

	void addC2S(QString type, QString data);
	void addS2C(QString type, QString data);

private:
	void addCommon(QString type, QString dir, QString data);
	QStandardItemModel* internalModel;
};

#endif /* __ACPCHATTERBOX_H__ */
