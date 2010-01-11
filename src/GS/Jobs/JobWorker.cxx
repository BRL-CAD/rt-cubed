/*                   J O B W O R K E R . C X X
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
/** @file JobWorker.cxx
 *
 * Brief description
 *
 */

#include "GS/Jobs/JobWorker.h"
#include "GS/Jobs/JobManager.h"

JobWorker::JobWorker()
{
	this->status = WORKER_NOTREADY;
	this->runCmd = true;
}

JobWorker::~JobWorker()
{
}

void JobWorker::run()
{
	JobManager* jm = JobManager::getInstance();

	this->status = WORKER_READY;

	while (this->runCmd)
	{
		if (!jm->hasJobsToWork())
		{
			this->msleep(100);
		}
		else
		{
			AbstractJob* job = jm->getNextJob();

			if (job == NULL)
			{
				continue;
			}

			JobResult result = job->doJob();

			//TODO log the result?

		}
	}
	this->status = WORKER_NOTREADY;
}

JobWorkerStatus JobWorker::getStatus()
{
	return this->status;
}

void JobWorker::shutdown()
{
	this->runCmd = false;
}
// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
