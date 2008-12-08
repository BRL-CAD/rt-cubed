///////////////////////////////////////////////////////////
//  ResourceDiskLink.h
//  Implementation of the Class SourceDiskLink
//  Created on:      04-Dec-2008 8:26:48 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__RESOURCEDISKLINK_H__)
#define __RESOURCEDISKLINK_H__

#include "iBMECommon.h"
#include "SourceDiskLink.h"
#include "AbstractDbObjectSource.h"
#include "DbObject.h"


class SourceDiskLink : public AbstractDbObjectSource
{

public:
	SourceDiskLink();
	virtual ~SourceDiskLink();

	virtual DbObject& getDbObjectByURL(URL& url);
	bool putDbObject(DbObject& dbobj);

};
#endif // !defined(__RESOURCEDISKLINK_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
