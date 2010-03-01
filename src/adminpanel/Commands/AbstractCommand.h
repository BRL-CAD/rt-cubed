/*                 A B S T R A C T C O M M A N D . H
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
/** @file AbstractCommand.h
 *
 * Brief description
 *
 */

#ifndef __ABSTRACTCOMMAND_H__
#define __ABSTRACTCOMMAND_H__

#include "GS/Jobs/AbstractJob.h"
#include "../ACPChatterBox.h"

#include <QString>

class AbstractCommand: public AbstractJob
{
public:
	AbstractCommand();
	virtual ~AbstractCommand();

	virtual JobResult _doJob(){};
protected:
	QString cmd;
	ACPChatterBox* box;
};

#endif /* __ABSTRACTCOMMAND_H__ */

// Local Variables:
// mode: C++
// tab-width: 8
// c-basic-offset: 2
// indent-tabs-mode: t
// End:
// ex: shiftwidth=2 tabstop=8
