///////////////////////////////////////////////////////////
//  JobWorker.h
//  Implementation of the Class JobWorker
//  Created on:      20-Nov-2008 8:00:15 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D7262FD7_6707_4792_9036_6A4738DDC87F__INCLUDED_)
#define EA_D7262FD7_6707_4792_9036_6A4738DDC87F__INCLUDED_

#include "AbstractJob.h"
#include "JobManager.h"

class JobWorker
{

public:
	JobWorker();
	virtual ~JobWorker();
	JobManager *m_JobManager;
	AbstractJob *m_AbstractJob;

private:
	AbstractJob job;
	int status;

};
#endif // !defined(EA_D7262FD7_6707_4792_9036_6A4738DDC87F__INCLUDED_)
