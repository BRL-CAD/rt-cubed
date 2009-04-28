/*                    C O M M A N D R E S U L T . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
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

/** @file CommandResult.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_COMMANDRESULT_H_)
#define _COMMANDRESULT_H_

#include "iBME/iBMECommon.h"

class CommandResult {

public:
	virtual ~CommandResult();

	CommandResult(unsigned int resVal);
	unsigned int getCommandResult();

private:
	CommandResult();
	unsigned int ResultValue;

};

#endif // !defined(_COMMANDRESULT_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
