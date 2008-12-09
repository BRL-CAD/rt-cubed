///////////////////////////////////////////////////////////
//  CopyCacheToDiskJob.h
//  Implementation of the Class CopyCacheToDiskJob
//  Created on:      04-Dec-2008 8:26:38 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__COPYCACHETODISKJOB_H__)
#define __COPYCACHETODISKJOB_H__

#include "GeometryService/Jobs/AbstractJob.h"
#include "GeometryEngine/DbObject.h"


class CopyCacheToDiskJob : public AbstractJob
{

public:
  CopyCacheToDiskJob(DbObject& resToCopy);
  virtual ~CopyCacheToDiskJob();

  virtual bool doJob();

private:
  DbObject& resToCopy();

};
#endif // !defined(__COPYCACHETODISKJOB_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
