/*                 C O M M A N D P A R S E R . H
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
/** @file CommandParser.h
 *
 * Brief description
 *
 */

#ifndef __COMMANDPARSER_H__
#define __COMMANDPARSER_H__

#include <QThread>
#include <QStringList>
#include <QCoreApplication>

#include "ICommandable.h"

class CommandParser : public QThread
{
    Q_OBJECT

public:
    CommandParser(ICommandable* iCmd);
    
    void run();
    void printCmdPrompt();

    bool stopCmd;
    
private:
    ICommandable* objToCommand;
    CommandParser(const CommandParser& cp){} //disable copy constructor.
    bool checkLocalCommand(QStringList* cmdStack);

};

#endif

/*
 * Local Variables:
 * tab-width: 8
 * mode: C++
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
