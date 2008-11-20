///////////////////////////////////////////////////////////
//  JobWorker.h
//  Implementation of the Class JobWorker
//  Created on:      20-Nov-2008 12:36:17 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D8980F52_3648_46c9_8C5A_BCDB4278B3C3__INCLUDED_)
#define EA_D8980F52_3648_46c9_8C5A_BCDB4278B3C3__INCLUDED_

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
#endif // !defined(EA_D8980F52_3648_46c9_8C5A_BCDB4278B3C3__INCLUDED_)
