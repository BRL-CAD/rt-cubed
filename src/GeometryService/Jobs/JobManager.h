///////////////////////////////////////////////////////////
//  JobManager.h
//  Implementation of the Class JobManager
//  Created on:      04-Dec-2008 8:26:43 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_A016A121_F929_4702_A7E7_1417533F8829__INCLUDED_)
#define EA_A016A121_F929_4702_A7E7_1417533F8829__INCLUDED_

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
#endif // !defined(EA_A016A121_F929_4702_A7E7_1417533F8829__INCLUDED_)
