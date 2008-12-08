///////////////////////////////////////////////////////////
//  GeometryEngine.h
//  Implementation of the Class GeometryEngine
//  Created on:      04-Dec-2008 8:26:41 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__GEOMETRYENGINE_H__)
#define __GEOMETRYENGINE_H__

#include "GED.h"
#include "DbObjectManager.h"

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

};
#endif // !defined(__GEOMETRYENGINE_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
