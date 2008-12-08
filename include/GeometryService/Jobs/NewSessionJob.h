///////////////////////////////////////////////////////////
//  NewSessionJob.h
//  Implementation of the Class NewSessionJob
//  Created on:      04-Dec-2008 8:26:46 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NEWSESSIONJOB_H__)
#define __NEWSESSIONJOB_H__

#include "AbstractJob.h"
#include "AbstractPortal.h"

class NewSessionJob : public AbstractJob
{

public:

  virtual ~NewSessionJob();
  NewSessionJob(AbstractPortal& portal);
  virtual bool doJob();

private:
  NewSessionJob();

};
#endif // !defined(__NEWSESSIONJOB_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
