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

#include <queue>
#include <vector>

#include <QtGui>

#include "Observer.h"

/** Maximum number lines of output displayed. */
#define CONSOLE_OUTPUT_LINES 8

class Console : public QWidget, public Observer
{
    Q_OBJECT

public:
    Console(QWidget *parent = NULL);
    ~Console();

    void update(const ObserverEvent &event);

public slots:
    void pushOutput(QString str);

signals:
    void commandRan(QString command);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

protected slots:
    void evalCmd();
    void updateCurrentHist();

private:
    QVBoxLayout *layout;
    
    QLineEdit *entry;
    QLabel *output;

    std::deque<QString> outputLines;
    std::deque<QString> history;
    unsigned historyIdx;
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
