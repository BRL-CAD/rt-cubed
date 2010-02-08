/*           A D M I N C O N T R O L P A N E L . C X X
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
/** @file AdminControlPanel.cxx
 *
 * All the functionality for the Admin Control Panel app.
 *
 */

#include "AdminControlPanel.h"

#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QStringList>
#include <QHeaderView>

AdminControlPanel::AdminControlPanel()
{
	this->acpMainWindow = new ACPMainWindow();

	QLabel *cmdLineLabel = new QLabel(QApplication::translate("cmdLineLayout",
			"cmd:"));
	this->cmdLineLineEdit = new QLineEdit();

	this->chatter = new ACPChatterBox();

	QHBoxLayout *cmdLineLayout = new QHBoxLayout();
	cmdLineLayout->addWidget(cmdLineLabel);
	cmdLineLayout->addWidget(this->cmdLineLineEdit);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(this->chatter);
	mainLayout->addLayout(cmdLineLayout);

	this->acpMainWindow->setLayout(mainLayout);

	this->acpMainWindow->setWindowTitle(QApplication::translate("windowlayout",
			"ACP v0.0.1"));

	this->acpMainWindow->resize(800, 600);

	/*
	 * Signals
	 */

	QObject::connect(cmdLineLineEdit, SIGNAL(returnPressed()), this, SLOT(
			addNew()));

	//finally show window.
	this->acpMainWindow->show();
}

AdminControlPanel::~AdminControlPanel()
{

}

void AdminControlPanel::addNew()
{
	QString str = this->cmdLineLineEdit->text();
	this->chatter->addC2S("Testing", str);
	this->cmdLineLineEdit->setText("");
}

// Local Variables:
// mode: C++
// tab-width: 8
// c-basic-offset: 2
// indent-tabs-mode: t
// End:
// ex: shiftwidth=2 tabstop=8
