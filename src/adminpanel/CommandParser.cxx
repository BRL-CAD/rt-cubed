/*               C O M M A N D P A R S E R . C X X
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
/** @file CommandParser.cxx
 *
 * Brief description
 *
 */

#include "CommandParser.h"
#include <QString>
#include <iostream>

CommandParser::CommandParser(ICommandable* iCmd)
{
	this->objToCommand = iCmd;
	this->stopCmd = false;
}

void CommandParser::run()
{
	char* input = (char*) malloc(256);
	bool retVal;

	while (!this->stopCmd)
	{
		//print cmd prompt:
		this->printCmdPrompt();

		//get input
		std::cin.getline(input, 256);

		//build command stack:
		QString qinput(input);
		QStringList* cmdStack = new QStringList(qinput.split(" ",
				QString::SkipEmptyParts));

		if (cmdStack->size() == 0)
		{
			continue;
		}

		//Check for local command:
		if (this->checkLocalCommand(cmdStack))
		{
			//QString cmd = cmdStack->first();
			//std::cout << "\tRecognized Command: " << cmd.toStdString() << std::endl;
			continue;
		}

		//Route
		bool commandSuccess = this->objToCommand->handleCommand(cmdStack);
	}
	free(input);
}

void CommandParser::printCmdPrompt()
{
	std::cout << "\nACP> ";
}

bool CommandParser::checkLocalCommand(QStringList* cmdStack)
{
	QString cmd = cmdStack->first().toLower();

	if (cmd == "exit" || cmd == "quit")
	{
		this->stopCmd = true;
		return true;
	}

	return false;
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
