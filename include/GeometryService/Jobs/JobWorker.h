///////////////////////////////////////////////////////////
//  JobWorker.h
//  Implementation of the Class JobWorker
//  Created on:      04-Dec-2008 8:26:44 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__JOBWORKER_H__)
#define __JOBWORKER_H__

#include "JobManager.h"
#include "AbstractJob.h"

class JobWorker
{

public:
	JobWorker();
	virtual ~JobWorker();
	JobManager *m_JobManager;
	AbstractJob *m_AbstractJob;

private:
	AbstractJob& job;
	int status;

};
#endif // !defined(__JOBWORKER_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

