///////////////////////////////////////////////////////////
//  NewSessionJob.h
//  Implementation of the Class NewSessionJob
//  Created on:      20-Nov-2008 8:00:17 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_DF68A09F_07DA_42b5_97B5_0F282FE72AB1__INCLUDED_)
#define EA_DF68A09F_07DA_42b5_97B5_0F282FE72AB1__INCLUDED_

#include "AbstractPortal.h"
#include "AbstractJob.h"

class NewSessionJob : public AbstractJob
{

public:
	NewSessionJob();
	virtual ~NewSessionJob();

	void NewSessionJob(AbstractPortal portal);
	virtual bool doJob();

};
#endif // !defined(EA_DF68A09F_07DA_42b5_97B5_0F282FE72AB1__INCLUDED_)
