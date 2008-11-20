///////////////////////////////////////////////////////////
//  STPauseable.h
//  Implementation of the Interface STPauseable
//  Created on:      17-Sep-2008 8:02:24 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E646627F_9CC3_4a26_96DF_49FC9A0C0BC3__INCLUDED_)
#define EA_E646627F_9CC3_4a26_96DF_49FC9A0C0BC3__INCLUDED_

#include "STRunnable.h"

class STPauseable : public STRunnable
{

public:
	STPauseable() {

	}

	virtual ~STPauseable() {

	}

	void enable() =0;
	void disable() =0;
	boolean isEnabled() =0;

};
#endif // !defined(EA_E646627F_9CC3_4a26_96DF_49FC9A0C0BC3__INCLUDED_)
