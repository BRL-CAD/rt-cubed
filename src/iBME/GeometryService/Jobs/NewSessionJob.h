///////////////////////////////////////////////////////////
//  NewSessionJob.h
//  Implementation of the Class NewSessionJob
//  Created on:      20-Nov-2008 12:36:19 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_486E93EA_60C8_406f_A311_D0F95800AA98__INCLUDED_)
#define EA_486E93EA_60C8_406f_A311_D0F95800AA98__INCLUDED_

#include "AbstractJob.h"

class NewSessionJob : public AbstractJob
{

public:
	NewSessionJob();
	virtual ~NewSessionJob();

	void NewSessionJob(AbstractPortal& portal);
	virtual bool doJob();

};
#endif // !defined(EA_486E93EA_60C8_406f_A311_D0F95800AA98__INCLUDED_)
