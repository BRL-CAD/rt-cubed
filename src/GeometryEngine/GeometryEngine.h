///////////////////////////////////////////////////////////
//  GeometryEngine.h
//  Implementation of the Class GeometryEngine
//  Created on:      04-Dec-2008 8:26:41 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_78A0F8DA_4FE4_41ba_8F84_D12EF37ADF51__INCLUDED_)
#define EA_78A0F8DA_4FE4_41ba_8F84_D12EF37ADF51__INCLUDED_

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
	DbObjectManager *m_DbObjectManager;

};
#endif // !defined(EA_78A0F8DA_4FE4_41ba_8F84_D12EF37ADF51__INCLUDED_)
