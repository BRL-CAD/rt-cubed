///////////////////////////////////////////////////////////
//  CopyCacheToDiskJob.h
//  Implementation of the Class CopyCacheToDiskJob
//  Created on:      20-Nov-2008 12:36:12 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_2165E136_E8BE_4a67_8D31_71C2998BB642__INCLUDED_)
#define EA_2165E136_E8BE_4a67_8D31_71C2998BB642__INCLUDED_

#include "AbstractJob.h"

class CopyCacheToDiskJob : public AbstractJob
{

public:
	CopyCacheToDiskJob();
	virtual ~CopyCacheToDiskJob();

	virtual bool doJob();

private:
	AbstractResource& resToCopy;

};
#endif // !defined(EA_2165E136_E8BE_4a67_8D31_71C2998BB642__INCLUDED_)
