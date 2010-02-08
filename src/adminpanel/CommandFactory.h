/*             C O M M A N D F A C T O R Y . H
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
/** @file CommandFactory.h
 *
 *
 *
 */

#ifndef __COMMANDFACTORY_H__
#define __COMMANDFACTORY_H__

#include "Commands/AbstractCommand.h"
#include "ACPChatterBox.h"

#include <QString>
#include <QStringList>

class CommandFactory
{
public:
	CommandFactory(ACPChatterBox* box);
	AbstractCommand* parseCommand(QString cmdLine);
	AbstractCommand* parseCommand(QStringList cmdList);

private:
	virtual ~CommandFactory();
	ACPChatterBox* box;
};

#endif /* __COMMANDFACTORY_H__ */

// Local Variables:
// mode: C++
// tab-width: 8
// c-basic-offset: 2
// indent-tabs-mode: t
// End:
// ex: shiftwidth=2 tabstop=8
