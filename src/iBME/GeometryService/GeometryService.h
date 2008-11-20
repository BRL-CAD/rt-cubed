///////////////////////////////////////////////////////////
//  GeometryService.h
//  Implementation of the Class GeometryService
//  Created on:      20-Nov-2008 12:36:14 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_1497BD4C_DB75_46d3_9E8C_9EABD9F38CB9__INCLUDED_)
#define EA_1497BD4C_DB75_46d3_9E8C_9EABD9F38CB9__INCLUDED_

#include "GeometryEngine.h"
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
#endif // !defined(EA_1497BD4C_DB75_46d3_9E8C_9EABD9F38CB9__INCLUDED_)
