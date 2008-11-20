///////////////////////////////////////////////////////////
//  CopyCacheToSvnJob.h
//  Implementation of the Class CopyCacheToSvnJob
//  Created on:      20-Nov-2008 12:36:13 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_47003FA6_4B8D_4b59_BD59_1015B982613E__INCLUDED_)
#define EA_47003FA6_4B8D_4b59_BD59_1015B982613E__INCLUDED_

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
#endif // !defined(EA_47003FA6_4B8D_4b59_BD59_1015B982613E__INCLUDED_)
