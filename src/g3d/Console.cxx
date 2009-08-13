/*                  C O N S O L E . C X X
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

/** @file Console.cxx
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	Implementation for the Console widget
 */

#include "Console.h"

#include "Command.h"
#include "CommandInterpreter.h"

#include "Logger.h"

Console::Console(QWidget *parent) : QWidget(parent),
				    layout(new QVBoxLayout(this)),
				    entryContainer(new QWidget()), entryLayout(new QHBoxLayout(entryContainer)),
				    entry(new HistoryLineEdit()), output(new QLabel()),
				    prompt(new QLabel(">"))
{
    layout->setMargin(0);
    layout->setSpacing(0);
    entryLayout->setMargin(0);
    entryLayout->setSpacing(0);
    
    output->setStyleSheet("border-radius: 2px");
    output->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
    // Prevent lag first time the output is shown.
    output->ensurePolished();
    output->hide();
    output->installEventFilter(this);
    layout->addWidget(output);

    entry->installEventFilter(this);
    
    entryLayout->addWidget(prompt);
    entryLayout->addWidget(entry);
    layout->addWidget(entryContainer);
    
    QObject::connect(entry, SIGNAL(returnPressed(void)),
		     this, SLOT(evalCmd(void)));

    QObject::connect(&(Logger::instance()), SIGNAL(messageLogged(QString)),
		     this, SLOT(pushOutput(QString)));
}


bool Console::eventFilter(QObject *, QEvent *event) 
{
    switch(event->type())
    {
    case QEvent::Enter:
	output->show();
	return true;
	
    case QEvent::Leave:
	output->hide();
	return true;

    default:
	break;
    }

    return false;
}

void Console::evalCmd() 
{
    if(entry->text().isEmpty()) {
	return;
    }
    pushOutput("> " + entry->text());
    emit commandRan(entry->text());
    entry->entryComplete();
}


void Console::pushOutput(QString str) 
{
    if(str.length() == 0) {
	return;
    }

    QStringList lines = str.split("\n");
    for(int i = 0; i < lines.size(); i++) {
	outputLines.push_back(lines[i]);
    }

    while(outputLines.size() > CONSOLE_OUTPUT_LINES) {
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
