///////////////////////////////////////////////////////////
//  AbstractResourceSource.h
//  Implementation of the Class AbstractDbObjectSource
//  Created on:      04-Dec-2008 8:26:34 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__ABSTRACTRESOURCESOURCE_H__)
#define __ABSTRACTRESOURCESOURCE_H__

class AbstractDbObjectSource
{

public:
	AbstractDbObjectSource();
	virtual ~AbstractDbObjectSource();

	virtual DbObject& getDbObjectByURL(URL url);
	bool putDbObject(DbObject& dbobj);

};
#endif // !defined(__ABSTRACTRESOURCESOURCE_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
