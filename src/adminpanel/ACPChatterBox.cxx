/*             A C P C H A T T E R B O X . C X X
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
/** @file ACPChatterBox.cxx
 *
 *
 *
 */

#include "ACPChatterBox.h"

#include <QtGui/QApplication>
#include <QtGui/QStandardItem>
#include <QtGui/QHeaderView>
#include <QtCore/QDateTime>

ACPChatterBox::ACPChatterBox()
{
	QStandardItemModel* model = new QStandardItemModel(0, 4, this);
	model->setHorizontalHeaderLabels(QStringList() << QApplication::translate(
			"TimeStamp", "TimeStamp") << QApplication::translate("MsgType",
			"MsgType") << QApplication::translate("Dir", "Dir")
			<< QApplication::translate("Data", "Data"));

	this->internalModel = model;

	this->setModel(this->internalModel);
	this->verticalHeader()->hide();
	this->horizontalHeader()->setStretchLastSection(true);
	this->setColumnWidth(0, 175);
}

ACPChatterBox::~ACPChatterBox()
{}

void ACPChatterBox::addC2S(QString type, QString data)
{
	this->addCommon(type, "C->S", data);
}

void ACPChatterBox::addS2C(QString type, QString data)
{
	this->addCommon(type, "S->C", data);
}

void ACPChatterBox::addCommon(QString type, QString dir, QString data)
{
	QList<QStandardItem*> item;

	QDateTime qdt = QDateTime::currentDateTime();
	QString strDateTime = qdt.toString("dd MMM yy hh:mm:ss.zzz").toUpper();

	QStandardItem* qsi00 = new QStandardItem(strDateTime);
	qsi00->setTextAlignment(Qt::AlignCenter);

	item.append(qsi00);

	QStandardItem* qsi01 = new QStandardItem(type);
	qsi01->setTextAlignment(Qt::AlignCenter);
	item.append(qsi01);

	QStandardItem* qsi02 = new QStandardItem(dir);
	qsi02->setTextAlignment(Qt::AlignCenter);
	item.append(qsi02);

	QStandardItem* qsi03 = new QStandardItem(data);
	//qsi03->setTextAlignment(Qt::AlignCenter);
	item.append(qsi03);

	this->internalModel->insertRow(0, item);
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
