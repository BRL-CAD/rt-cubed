///////////////////////////////////////////////////////////
//  CopyCacheToSvnJob.h
//  Implementation of the Class CopyCacheToSvnJob
//  Created on:      04-Dec-2008 8:26:38 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D6B90250_71D9_4973_AF4B_440367432A04__INCLUDED_)
#define EA_D6B90250_71D9_4973_AF4B_440367432A04__INCLUDED_

#include "AbstractJob.h"

class CopyCacheToSvnJob : public AbstractJob
{

public:
	CopyCacheToSvnJob();
	virtual ~CopyCacheToSvnJob();

	virtual bool doJob();

private:
	AbstractResource& resToCopy;

};
#endif // !defined(EA_D6B90250_71D9_4973_AF4B_440367432A04__INCLUDED_)
