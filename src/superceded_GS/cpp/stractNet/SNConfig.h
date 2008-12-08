///////////////////////////////////////////////////////////
//  SNConfig.h
//  Implementation of the Class SNConfig
//  Created on:      06-Aug-2008 7:50:04 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(SNCONFIG_H_INCLUDED_)
#define SNCONFIG_H_INCLUDED_

#include "SNRoot.h"
#include "SNConfig.h"

class SNConfig : public SNRoot
{

public:
	virtual ~SNConfig();
	SNConfig(String Name);

};
#endif // !defined(SNCONFIG_H_INCLUDED_)
