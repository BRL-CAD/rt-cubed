/*                   A B S T R A C T J O B . H
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
/** @file AbstractJob.h
 *
 * Brief description
 *
 */

#ifndef __ABSTRACTJOB_H__
#define __ABSTRACTJOB_H__

#include <QtCore/Qt>

enum JobStatus
{
	JOB_NOTSTARTED, JOB_RUNNING, JOB_FINISHED
};
enum JobResult
{
	JOB_COMPLETED_NO_ERRORS, JOB_COMPLETED_WITH_ERRORS, JOB_FAILED
};

class AbstractJob
{
public:
	AbstractJob();
	virtual ~AbstractJob();

	/**
	 * Submits this job to the JobManager.  (Dangerous, need to remove)
	 */
	void submit();

	/**
	 * Executes the code in _doJob().  This function performs status setup and sanity checks prior to executing subclass code.
	 */
	JobResult doJob();

	/**
	 * Returns the current JobStatus of this Job.
	 */
	JobStatus getStatus();

	/**
	 * Returns the JobID for this job.  JobID is a 32bit integer value.
	 */
	quint32 getJobId();

protected:

	/**
	 * Mandates subclass implementation of _doJob().  This function provides the actual
	 * functionality that defines the subclass.
	 */
	virtual JobResult _doJob() = 0;

	/**
	 * Internal field for storing Job's ID.
	 */
	quint32 jobID;

	/**
	 * Internal field for storing Job's current status.
	 */
	JobStatus status;

private:
	/* Disable copy cstr and =operator */
	AbstractJob(AbstractJob const&){};
	AbstractJob& operator=(AbstractJob const&){};
};

#endif /* __ABSTRACTJOB_H__ */

/*
 * Local Variables: ***
 * mode: C++ ***
 * tab-width: 8 ***
 * c-basic-offset: 2 ***
 * indent-tabs-mode: t ***
 * End: ***
 * ex: shiftwidth=2 tabstop=8
*/
