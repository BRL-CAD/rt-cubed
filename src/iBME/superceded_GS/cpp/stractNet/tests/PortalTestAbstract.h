///////////////////////////////////////////////////////////
//  PortalTestAbstract.h
//  Implementation of the Class PortalTestAbstract
//  Created on:      06-Aug-2008 8:00:54 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_BEB15231_7E85_48f0_B6C3_1F800109D4D9__INCLUDED_)
#define EA_BEB15231_7E85_48f0_B6C3_1F800109D4D9__INCLUDED_

#include "SNRoot.h"

class PortalTestAbstract : public SNRoot
{

public:
	PortalTestAbstract();
	virtual ~PortalTestAbstract();

	PortalTestAbstract(String Name);

protected:
	InetAddress localhost;
	int mtsInUseA[];
	int mtsInUseB[];
	long sleep;

};
#endif // !defined(EA_BEB15231_7E85_48f0_B6C3_1F800109D4D9__INCLUDED_)
