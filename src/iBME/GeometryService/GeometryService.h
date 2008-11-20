///////////////////////////////////////////////////////////
//  GeometryService.h
//  Implementation of the Class GeometryService
//  Created on:      20-Nov-2008 8:00:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_ABCBB439_21A8_4f2e_BF63_7A8CA9C1DC7F__INCLUDED_)
#define EA_ABCBB439_21A8_4f2e_BF63_7A8CA9C1DC7F__INCLUDED_

#include "JobManager.h"
#include "SessionManager.h"
#include "CommunicationsManager.h"
#include "NetMsgActionDefManager.h"
#include "AccessManager.h"
#include "GeometryEngine.h"

/**
 * Singleton Class.
 * 
 * Represents the object that is instantiated should the BME be set to run a
 * Geometry Service
 */
class GeometryService : public GeometryEngine
{

public:
	GeometryService();
	virtual ~GeometryService();
	CommunicationsManager *m_CommunicationsManager;
	SessionManager *m_SessionManager;
	AccessManager *m_AccessManager;

private:
	/**
	 * Configure jobMan to be a singleton??
	 */
	JobManager jobMan;
	SessionManager sessionMan;
	CommunicationsManager comMan;
	NetMsgActionDefManager nmadMan;
	AccessManager accessMan;

};
#endif // !defined(EA_ABCBB439_21A8_4f2e_BF63_7A8CA9C1DC7F__INCLUDED_)
