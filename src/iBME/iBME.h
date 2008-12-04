///////////////////////////////////////////////////////////
//  iBME.h
//  Implementation of the Class iBME
//  Created on:      04-Dec-2008 8:26:42 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_EB8F01CF_BF30_4e5e_9512_75DCECA6F1A3__INCLUDED_)
#define EA_EB8F01CF_BF30_4e5e_9512_75DCECA6F1A3__INCLUDED_

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
#endif // !defined(EA_EB8F01CF_BF30_4e5e_9512_75DCECA6F1A3__INCLUDED_)
