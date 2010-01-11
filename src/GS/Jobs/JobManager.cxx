/*                  J O B M A N A G E R . C X X
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
/** @file JobManager.cxx
 *
 * Singleton.
 *
 */

#include "GS/Jobs/JobManager.h"
#include <QMutexLocker>

JobManager* JobManager::pInstance = NULL;

JobManager::JobManager()
{

	this->jobQueue = new QList<AbstractJob*> ();
	this->queueLock = new QMutex();

	this->jobWorkers = new QList<JobWorker*> ();

	for (quint32 i = 0; i < MAX_JOBWORKERS; ++i)
	{
		JobWorker* jw = new JobWorker();
		this->jobWorkers->append(jw);
		jw->start();
	}
}

JobManager::~JobManager()
{
	delete jobQueue;
	//TODO Should I loop through jobs, destroying them as well?
	delete queueLock;

	delete jobWorkers;
	//TODO Should I loop through workers, destroying them as well?
}

JobManager* JobManager::getInstance()
{
	if (!JobManager::pInstance)
	{
		pInstance = new JobManager();
	}
	return JobManager::pInstance;
}

void JobManager::submitJob(AbstractJob* job)
{
	QMutexLocker locker(this->queueLock);
	this->jobQueue->append(job);
}

AbstractJob* JobManager::getNextJob()
{
	QMutexLocker locker(this->queueLock);
	if (!this->jobQueue->isEmpty())
	{
		return this->jobQueue->takeFirst();
	}
	else
	{
		return NULL;
	}
}

bool JobManager::hasJobsToWork()
{
	QMutexLocker locker(this->queueLock);
	return !this->jobQueue->isEmpty();
}

//TODO add JobWorker Monitor.

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
