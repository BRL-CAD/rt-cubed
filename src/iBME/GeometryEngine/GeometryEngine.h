///////////////////////////////////////////////////////////
//  GeometryEngine.h
//  Implementation of the Class GeometryEngine
//  Created on:      20-Nov-2008 8:00:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_935BCA7F_1D0E_4c01_AADD_69D9DEAE1E8D__INCLUDED_)
#define EA_935BCA7F_1D0E_4c01_AADD_69D9DEAE1E8D__INCLUDED_

#include "GED.h"
#include "ResourceManager.h"

/**
 * Singleton Class.
 * Will contain all Geometric Processing functions to include: Format Converters,
 * Tessilation, SVN access, IMG processors.
 */
class GeometryEngine
{

public:
	GeometryEngine();
	virtual ~GeometryEngine();
	GED *m_GED;
	ResourceManager *m_ResourceManager;

};
#endif // !defined(EA_935BCA7F_1D0E_4c01_AADD_69D9DEAE1E8D__INCLUDED_)
