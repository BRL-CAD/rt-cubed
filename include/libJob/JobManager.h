/*                    J O B M A N A G E R . H
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
/** @file JobManager.h
 *
 * Brief description
 *
 */

#ifndef __JOBMANAGER_H__
#define __JOBMANAGER_H__

#include "libJob/AbstractJob.h"
#include "libJob/JobWorker.h"
#include "GS/GSCommon.h"
#include <QList>
#include <QMutex>


class JobManager
{

public:
	static JobManager* getInstance();
	void submitJob(AbstractJob* aj);

	virtual ~JobManager();

	AbstractJob* getNextJob();
	bool hasJobsToWork();

private:
	static JobManager* pInstance;
	JobManager();

	JobManager(JobManager const&){};
	JobManager& operator=(JobManager const&){};

	QList<JobWorker*>* jobWorkers;
	QList<AbstractJob*>* jobQueue;
	QMutex* queueLock;
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8