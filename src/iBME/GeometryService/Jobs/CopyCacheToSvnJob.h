///////////////////////////////////////////////////////////
//  CopyCacheToSvnJob.h
//  Implementation of the Class CopyCacheToSvnJob
//  Created on:      20-Nov-2008 8:00:11 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_C031906E_9965_4a09_8A10_3F9E14163718__INCLUDED_)
#define EA_C031906E_9965_4a09_8A10_3F9E14163718__INCLUDED_

#include "AbstractJob.h"

class CopyCacheToSvnJob : public AbstractJob
{

public:
	CopyCacheToSvnJob();
	virtual ~CopyCacheToSvnJob();

	virtual bool doJob();

private:
	AbstractResource resToCopy;

};
#endif // !defined(EA_C031906E_9965_4a09_8A10_3F9E14163718__INCLUDED_)
