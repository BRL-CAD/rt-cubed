///////////////////////////////////////////////////////////
//  NetMsgActionJob.h
//  Implementation of the Class NetMsgActionJob
//  Created on:      04-Dec-2008 8:26:45 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NETMSGACTIONJOB_H__)
#define __NETMSGACTIONJOB_H__

#include "GeometryService/Jobs/AbstractJob.h"
#include "GeometryService/NetMsg.h"

class NetMsgActionJob : public AbstractJob
{

public:

  virtual ~NetMsgActionJob();

  NetMsgActionJob(NetMsg& msg);
  virtual bool doJob();

private:
  NetMsgActionJob();
  NetMsg& msg();

};
#endif // !defined(__NETMSGACTIONJOB_H__)



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
