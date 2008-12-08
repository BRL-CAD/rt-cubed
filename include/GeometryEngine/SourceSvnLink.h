///////////////////////////////////////////////////////////
//  ResourceSvnLink.h
//  Implementation of the Class SourceSvnLink
//  Created on:      04-Dec-2008 8:26:48 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__RESOURCESVNLINK_H__)
#define __RESOURCESVNLINK_H__

#include "iBMECommon.h"
#include "AbstractDbObjectSource.h"
#include "DbObject.h"

class SourceSvnLink : public AbstractDbObjectSource
{

public:
	SourceSvnLink();
	virtual ~SourceSvnLink();

	virtual DbObject& getDbObjectByURL(URL& url);
	bool putDbObject(DbObject& dbobj);

};
#endif // !defined(__RESOURCESVNLINK_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
