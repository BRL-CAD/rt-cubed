///////////////////////////////////////////////////////////
//  AbstractJob.h
//  Implementation of the Class AbstractJob
//  Created on:      20-Nov-2008 12:36:07 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3014E829_A810_4c4a_A62A_D0F7ED422E81__INCLUDED_)
#define EA_3014E829_A810_4c4a_A62A_D0F7ED422E81__INCLUDED_

#include "JobManager.h"

class AbstractJob
{

public:
	AbstractJob();
	virtual ~AbstractJob();
	JobManager *m_JobManager;

	void AbstractJob(JobManager& jm);
	virtual bool doJob();

private:
	int jobID;
	JobManager& jobMan;

};
#endif // !defined(EA_3014E829_A810_4c4a_A62A_D0F7ED422E81__INCLUDED_)
