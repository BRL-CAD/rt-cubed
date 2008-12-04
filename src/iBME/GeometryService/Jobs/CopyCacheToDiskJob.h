///////////////////////////////////////////////////////////
//  CopyCacheToDiskJob.h
//  Implementation of the Class CopyCacheToDiskJob
//  Created on:      04-Dec-2008 8:26:38 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_4FE47C7F_B663_42e9_8F16_E80617DB9D8D__INCLUDED_)
#define EA_4FE47C7F_B663_42e9_8F16_E80617DB9D8D__INCLUDED_

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
#endif // !defined(EA_4FE47C7F_B663_42e9_8F16_E80617DB9D8D__INCLUDED_)
