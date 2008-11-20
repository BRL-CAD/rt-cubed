///////////////////////////////////////////////////////////
//  CopyCacheToDiskJob.h
//  Implementation of the Class CopyCacheToDiskJob
//  Created on:      20-Nov-2008 8:00:10 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_DA5100E0_51FB_4125_8C5E_313F70DAD449__INCLUDED_)
#define EA_DA5100E0_51FB_4125_8C5E_313F70DAD449__INCLUDED_

#include "AbstractJob.h"

class CopyCacheToDiskJob : public AbstractJob
{

public:
	CopyCacheToDiskJob();
	virtual ~CopyCacheToDiskJob();

	virtual bool doJob();

private:
	AbstractResource resToCopy;

};
#endif // !defined(EA_DA5100E0_51FB_4125_8C5E_313F70DAD449__INCLUDED_)
