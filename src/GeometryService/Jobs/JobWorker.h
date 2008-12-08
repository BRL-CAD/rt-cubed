///////////////////////////////////////////////////////////
//  JobWorker.h
//  Implementation of the Class JobWorker
//  Created on:      04-Dec-2008 8:26:44 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_6514AFB8_3698_4744_95C3_77771F8129F7__INCLUDED_)
#define EA_6514AFB8_3698_4744_95C3_77771F8129F7__INCLUDED_

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
#endif // !defined(EA_6514AFB8_3698_4744_95C3_77771F8129F7__INCLUDED_)
