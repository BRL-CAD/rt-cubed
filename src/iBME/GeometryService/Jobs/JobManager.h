///////////////////////////////////////////////////////////
//  JobManager.h
//  Implementation of the Class JobManager
//  Created on:      20-Nov-2008 12:36:16 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_5257E0FF_7478_470c_9222_6682395C661F__INCLUDED_)
#define EA_5257E0FF_7478_470c_9222_6682395C661F__INCLUDED_

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
#endif // !defined(EA_5257E0FF_7478_470c_9222_6682395C661F__INCLUDED_)
