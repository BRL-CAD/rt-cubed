///////////////////////////////////////////////////////////
//  AbstractJob.h
//  Implementation of the Class AbstractJob
//  Created on:      04-Dec-2008 8:26:35 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__ABSTRACTJOB_H__)
#define __ABSTRACTJOB_H__

class AbstractJob {

public:
  virtual ~AbstractJob();

  AbstractJob();
  virtual bool doJob();

private:
  int jobID;

};
#endif // !defined(__ABSTRACTJOB_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
