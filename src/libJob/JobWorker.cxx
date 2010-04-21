/*                   J O B W O R K E R . C X X
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
/** @file JobWorker.cxx
 *
 * Brief description
 *
 */

#include "libJob/JobWorker.h"
#include "libJob/JobManager.h"
#include <iostream>

JobWorker::JobWorker()
{
    this->status = WORKER_NOTREADY;
    this->runCmd = true;
    this->workerId = QUuid::createUuid();
    this->log = Logger::getInstance();
}

JobWorker::~JobWorker()
{
}

void JobWorker::run()
{
    JobManager* jm = JobManager::getInstance();

    this->status = WORKER_READY;

    //TODO there must be a more dynamic way to have the workers idle other than a sleep
    while (this->runCmd) {
	if (!jm->hasJobsToWork()) {
	    this->msleep(100);
	}
	else {
	    AbstractJob* job = jm->getNextJob();

	    if (job == NULL) {
		continue;
	    }

	    std::cout << "JobWorker (" << this->getWorkerIdAsStdString()
		    << ") is working Job with ID of " << job->getJobId()
		    << std::endl;

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

QUuid JobWorker::getWorkerId()
{
    return this->workerId;
}

QString JobWorker::getWorkerIdAsQString()
{
    return this->workerId.toString();
}

std::string JobWorker::getWorkerIdAsStdString()
{
    return this->workerId.toString().toStdString();
}

void JobWorker::shutdown()
{
    this->runCmd = false;
    QString text = "JobWorker (" + this->getWorkerIdAsQString()
	    + ") received Shutdown Command.";
    this->log->logINFO("JobWorker", text);
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
