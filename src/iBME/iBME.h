///////////////////////////////////////////////////////////
//  iBME.h
//  Implementation of the Class iBME
//  Created on:      20-Nov-2008 8:00:13 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_8B8196C6_B31E_4c8c_B9C8_05BED0EBB48B__INCLUDED_)
#define EA_8B8196C6_B31E_4c8c_B9C8_05BED0EBB48B__INCLUDED_

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
#endif // !defined(EA_8B8196C6_B31E_4c8c_B9C8_05BED0EBB48B__INCLUDED_)
