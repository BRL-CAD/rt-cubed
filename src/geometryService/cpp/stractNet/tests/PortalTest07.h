///////////////////////////////////////////////////////////
//  PortalTest07.h
//  Implementation of the Class PortalTest07
//  Created on:      06-Aug-2008 8:01:43 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3C6FEADC_DE83_4079_8DE8_64BE41D4B0BC__INCLUDED_)
#define EA_3C6FEADC_DE83_4079_8DE8_64BE41D4B0BC__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a localhost set of 7 Portals  A->B v  v C->D->E ^  ^ F->G   B   E /
 * \ / \ A   D   G \ / \ / C   F  Msg sent from A, only one should arrive at G
 */
class PortalTest07 : public PortalTestAbstract
{

public:
	virtual ~PortalTest07();

	PortalTest07();
	static void main(String[] args);

};
#endif // !defined(EA_3C6FEADC_DE83_4079_8DE8_64BE41D4B0BC__INCLUDED_)
