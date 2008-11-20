///////////////////////////////////////////////////////////
//  JobManager.h
//  Implementation of the Class JobManager
//  Created on:      20-Nov-2008 8:00:14 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_254D317D_906D_4600_B293_3BED2BBDE078__INCLUDED_)
#define EA_254D317D_906D_4600_B293_3BED2BBDE078__INCLUDED_

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
	std::list <AbstractJob> jobQueue;

};
#endif // !defined(EA_254D317D_906D_4600_B293_3BED2BBDE078__INCLUDED_)
