///////////////////////////////////////////////////////////
//  GeometryService.h
//  Implementation of the Class GeometryService
//  Created on:      04-Dec-2008 8:26:41 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3D6AB01F_95E0_476a_9A5C_7D27DC5CD966__INCLUDED_)
#define EA_3D6AB01F_95E0_476a_9A5C_7D27DC5CD966__INCLUDED_

#include "GeometryEngine.h"
#include "NetMsgActionDefManager.h"
#include "JobManager.h"
#include "CommunicationsManager.h"
#include "SessionManager.h"
#include "AccessManager.h"

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
	NetMsgActionDefManager *m_NetMsgActionDefManager;
	JobManager *m_JobManager;
	CommunicationsManager *m_CommunicationsManager;
	SessionManager *m_SessionManager;
	AccessManager *m_AccessManager;

private:
	/**
	 * Configure jobMan to be a singleton??
	 */
	JobManager& jobMan;
	SessionManager& sessionMan;
	CommunicationsManager& comMan;
	NetMsgActionDefManager& nmadMan;
	AccessManager& accessMan;

};
#endif // !defined(EA_3D6AB01F_95E0_476a_9A5C_7D27DC5CD966__INCLUDED_)
