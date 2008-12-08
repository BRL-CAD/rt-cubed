///////////////////////////////////////////////////////////
//  GeometryService.h
//  Implementation of the Class GeometryService
//  Created on:      04-Dec-2008 8:26:41 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__GEOMETRYSERVICE_H__)
#define __GEOMETRYSERVICE_H__

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

private:
  JobManager& jobMan();
  SessionManager& sessionMan();
  CommunicationsManager& comMan();
  NetMsgActionDefManager& nmadMan();
  AccessManager& accessMan();

};
#endif // !defined(__GEOMETRYSERVICE_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
