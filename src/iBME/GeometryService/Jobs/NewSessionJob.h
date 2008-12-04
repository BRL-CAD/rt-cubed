///////////////////////////////////////////////////////////
//  NewSessionJob.h
//  Implementation of the Class NewSessionJob
//  Created on:      04-Dec-2008 8:26:46 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_1DD2ED9F_5538_43ce_A65B_37A818E571EE__INCLUDED_)
#define EA_1DD2ED9F_5538_43ce_A65B_37A818E571EE__INCLUDED_

#include "AbstractJob.h"

class NewSessionJob : public AbstractJob
{

public:
	NewSessionJob();
	virtual ~NewSessionJob();

	void NewSessionJob(AbstractPortal& portal);
	virtual bool doJob();

};
#endif // !defined(EA_1DD2ED9F_5538_43ce_A65B_37A818E571EE__INCLUDED_)
