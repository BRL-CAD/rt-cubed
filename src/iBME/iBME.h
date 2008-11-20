///////////////////////////////////////////////////////////
//  iBME.h
//  Implementation of the Class iBME
//  Created on:      20-Nov-2008 12:36:15 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_B140D342_018A_417a_9ACC_6864426581EF__INCLUDED_)
#define EA_B140D342_018A_417a_9ACC_6864426581EF__INCLUDED_

#include "GeometryService.h"
#include "AbstractGui.h"

/**
 * Main static class for launching the IBEAM binary.
 */
class iBME : public GeometryService
{

public:
	iBME();
	virtual ~iBME();
	AbstractGui *m_AbstractGui;

};
#endif // !defined(EA_B140D342_018A_417a_9ACC_6864426581EF__INCLUDED_)
