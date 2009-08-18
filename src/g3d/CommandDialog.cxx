/*                  C O M M A N D D I A L O G . C X X 
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by the
 * U.S. Army Research Laboratory.
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

/** @file CommandDialog.cxx
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	Implementation for the command popup
 */

#include "CommandDialog.h"

CommandDialog::CommandDialog() 
{
    setWindowFlags(Qt::FramelessWindowHint);

    setupUi(this);
    QObject::connect(runButton, SIGNAL(clicked()),
		     entry, SLOT(entryComplete()));

    QObject::connect(runButton, SIGNAL(clicked()),
		     this, SLOT(hide()));
}

void CommandDialog::focusInEvent(QFocusEvent *) 
{
    entry->setFocus();
}

/*
 * Local Variables:
 * mode: C++
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
