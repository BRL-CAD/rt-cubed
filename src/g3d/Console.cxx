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
 *	Implementation for the Console widget
 */

#include "Console.h"

#include "Command.h"
#include "CommandInterpreter.h"
#include "History.h"

#include "Logger.h"

Console::Console(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    
    output = new QLabel();
    output->setText("Console output goes here.");
    output->setAutoFillBackground(true);
    output->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
    // Prevent lag first time the output is shown.
    output->ensurePolished();
    output->hide();
    installEventFilter(output);
    layout->addWidget(output);

    entry = new QLineEdit();
    installEventFilter(entry);
    layout->addWidget(entry);
    
    installEventFilter(this);

    QObject::connect(entry, SIGNAL(returnPressed(void)),
		     this, SLOT(evalCmd(void)));

    // TODO: Replace this with signal/slot
    Logger::instance().attach(this);
}

Console::~Console() 
{
    Logger::instance().detach(this);
}


void Console::update(const ObserverEvent &event) 
{
    // logger events
    {
	const LoggerObserverEvent* e = dynamic_cast<const LoggerObserverEvent*>(&event);
	if (e) {
	    switch (e->_actionId) {
	    case LoggerObserverEvent::ADDED_ENTRY:
		pushOutput(QString(e->_content.c_str()));
		break;
	    default:
		break;
	    }
	    return;
	}
    }
}


// TODO: Should we be returning true for handled events?
bool Console::eventFilter(QObject *obj, QEvent *event) 
{
    switch(event->type())
    {
    case QEvent::Enter:
	output->show();
	break;
	
    case QEvent::Leave:
	output->hide();
	break;

    case QEvent::KeyPress:
    {
	if(obj != entry) {
	    break;
	}
	
	switch(static_cast<QKeyEvent*>(event)->key()) {
	case Qt::Key_Up:
	    entry->setText(QString(History::instance().getPrev().c_str()));
	    break;

	case Qt::Key_Down:
	    entry->setText(QString(History::instance().getNext().c_str()));
	    break;
	}
	
	break;
    }

    default:
	break;
    }

    return false;
}

// TODO: Doesn't appear to get signaled.
void Console::evalCmd() 
{
    emit commandRan(entry->text());
    // TODO: Replace History with a simple STL container
    History::instance().insert(entry->text().toStdString().c_str());
    entry->clear();
}


void Console::pushOutput(QString str) 
{
    if(str.length() == 0) {
	return;
    }
    
    outputLines.push_back(str);

    if(outputLines.size() > CONSOLE_OUTPUT_LINES) {
	outputLines.pop_front();
    }

    // Update widget
    QString combined;
    for(std::deque<QString>::const_iterator i = outputLines.begin(); i != outputLines.end(); ++i) {
	if(i != outputLines.begin()) {
	    combined.append("\n");
	}
	combined.append(*i);
    }
    output->setText(combined);
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
