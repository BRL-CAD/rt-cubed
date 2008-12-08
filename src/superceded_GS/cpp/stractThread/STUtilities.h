///////////////////////////////////////////////////////////
//  STUtilities.h
//  Implementation of the Class STUtilities
//  Created on:      17-Sep-2008 8:02:26 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_64994D0F_979D_43d4_B5BF_A0B8D056C5D5__INCLUDED_)
#define EA_64994D0F_979D_43d4_B5BF_A0B8D056C5D5__INCLUDED_

#include "StractThread.h"

class STUtilities : public StractThread
{

public:
	STUtilities();
	virtual ~STUtilities();

	static void pause(long ms);

};
#endif // !defined(EA_64994D0F_979D_43d4_B5BF_A0B8D056C5D5__INCLUDED_)
