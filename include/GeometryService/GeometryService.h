///////////////////////////////////////////////////////////
//  GeometryService.h
//  Implementation of the Class GeometryService
//  Created on:      04-Dec-2008 8:26:41 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__GEOMETRYSERVICE_H__)
#define __GEOMETRYSERVICE_H__

#include "GeometryEngine/GeometryEngine.h"
#include "GeometryService/NetMsgActionDefinitions/NetMsgActionDefManager.h"
#include "GeometryService/Jobs/JobManager.h"
#include "GeometryService/CommunicationsManager.h"
#include "GeometryService/SessionManager.h"
#include "GeometryService/AccessManager.h"
#include "GeometryService/GeometryService.h"

/**
 * Singleton Class.
 *
 * Represents the object that is instantiated should the iBME be set to run a
 * Geometry Service
 */
class GeometryService
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
