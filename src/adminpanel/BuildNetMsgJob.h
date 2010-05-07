/*                B U I L D N E T M S G J O B . H
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
/** @file BuildNetMsgJob.h
 *
 * Brief description
 *
 */


#ifndef __BUILDNETMSGJOB_H__
#define __BUILDNETMSGJOB_H__

#include "libnetwork.h"
#include "libjob.h"

#include <QString>
#include <QStringList>

class BuildNetMsgJob : public AbstractJob
{
public:
	BuildNetMsgJob();
	virtual ~BuildNetMsgJob();

protected:
	virtual JobResult _doJob();
};

#endif

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
