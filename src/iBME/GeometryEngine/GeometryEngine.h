///////////////////////////////////////////////////////////
//  GeometryEngine.h
//  Implementation of the Class GeometryEngine
//  Created on:      20-Nov-2008 12:36:14 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_0435AF58_6F02_4c83_B821_C9A85CB6FF89__INCLUDED_)
#define EA_0435AF58_6F02_4c83_B821_C9A85CB6FF89__INCLUDED_

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
#endif // !defined(EA_0435AF58_6F02_4c83_B821_C9A85CB6FF89__INCLUDED_)
