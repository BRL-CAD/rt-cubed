/*                  M A I N W I N D O W . H
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

/** @file OgreGLWidget.h
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	Header for the Console widget
 */

#ifndef __G3D_CONSOLE_H__
#define __G3D_CONSOLE_H__

#include <QtGui>

class ConsoleLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ConsoleLineEdit(QLabel *output);
    
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    QLabel *_output;
};

class Console : public QWidget
{
    Q_OBJECT

public:
    Console(QWidget *parent = NULL);

private:
    QVBoxLayout *layout;
    
    ConsoleLineEdit *entry;
    QLabel *output;
};

#endif

/*
 * Local Variables:
 * mode: C++
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
