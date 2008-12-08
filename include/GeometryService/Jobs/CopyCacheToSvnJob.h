///////////////////////////////////////////////////////////
//  CopyCacheToSvnJob.h
//  Implementation of the Class CopyCacheToSvnJob
//  Created on:      04-Dec-2008 8:26:38 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__COPYCACHETOSVNJOB_H__)
#define __COPYCACHETOSVNJOB_H__

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
#endif // !defined(__COPYCACHETOSVNJOB_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

