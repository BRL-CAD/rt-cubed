/*             A D M I N C O N T R O L P A N E L . H
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
/** @file AdminControlPanel.h
 *
 * All the functionality for the Admin Control Panel app.
 *
 */

#ifndef __ADMINCONTROLPANEL_H__
#define __ADMINCONTROLPANEL_H__

#include "ACPChatterBox.h"

#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

class AdminControlPanel : public QObject
{
Q_OBJECT

public:
	AdminControlPanel();
	virtual ~AdminControlPanel();

protected slots:
	void addNew();

private:
	QWidget* mainWidget;
	QLineEdit *cmdLineLineEdit;
	ACPChatterBox *chatter;
};

#endif /* __ADMINCONTROLPANEL_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
