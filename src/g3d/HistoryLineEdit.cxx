/*                  M A I N W I N D O W . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2010 United States Government as represented by the
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

/** @file OgreGLWidget.h
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	Implementation for the Console widget
 */

#include "HistoryLineEdit.h"

#include <QKeyEvent>

HistoryLineEdit::HistoryLineEdit(QWidget *parent) : QLineEdit(parent),
						    history(1), historyIdx(0)
{
}

void HistoryLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Up:
	if(historyIdx < (history.size() - 1)) {
	    setText(history[++historyIdx]);
	}
	break;

    case Qt::Key_Down:
	if(historyIdx > 0) {
	    setText(history[--historyIdx]);
	}
	break;

    default:
	QLineEdit::keyPressEvent(event);
	history[0] = text();
	break;
    }
}

void HistoryLineEdit::entryComplete() 
{
    if(text().isEmpty()) {
	return;
    }
    history[0] = text();
    history.push_front("");
    historyIdx = 0;
    clear();
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
