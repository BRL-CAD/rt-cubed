///////////////////////////////////////////////////////////
//  AbstractJob.h
//  Implementation of the Class AbstractJob
//  Created on:      20-Nov-2008 8:00:07 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_23281174_6F52_4fab_8A5E_E5B27A3EAE5E__INCLUDED_)
#define EA_23281174_6F52_4fab_8A5E_E5B27A3EAE5E__INCLUDED_

#include "JobManager.h"

class AbstractJob
{

public:
	AbstractJob();
	virtual ~AbstractJob();
	JobManager *m_JobManager;

	void AbstractJob(JobManager jm);
	virtual bool doJob();

private:
	int jobID;
	JobManager jobMan;

};
#endif // !defined(EA_23281174_6F52_4fab_8A5E_E5B27A3EAE5E__INCLUDED_)
