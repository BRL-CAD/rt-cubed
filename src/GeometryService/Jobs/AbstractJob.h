///////////////////////////////////////////////////////////
//  AbstractJob.h
//  Implementation of the Class AbstractJob
//  Created on:      04-Dec-2008 8:26:35 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_C0023A04_2798_4dac_BBA9_E20DDE098FF3__INCLUDED_)
#define EA_C0023A04_2798_4dac_BBA9_E20DDE098FF3__INCLUDED_

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
#endif // !defined(EA_C0023A04_2798_4dac_BBA9_E20DDE098FF3__INCLUDED_)
