///////////////////////////////////////////////////////////
//  JobManager.h
//  Implementation of the Class JobManager
//  Created on:      04-Dec-2008 8:26:43 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__JOBMANAGER_H__)
#define __JOBMANAGER_H__

#include "AbstractJob.h"
#include "JobWorker.h"

class JobManager
{

public:
	JobManager();
	virtual ~JobManager();
	AbstractJob *m_AbstractJob;
	JobWorker *m_JobWorker;

private:
	std::list <AbstractJob&> jobQueue;

};
#endif // !defined(__JOBMANAGER_H__)



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
