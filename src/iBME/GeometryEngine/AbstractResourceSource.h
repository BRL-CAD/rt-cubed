///////////////////////////////////////////////////////////
//  AbstractResourceSource.h
//  Implementation of the Class AbstractDbObjectSource
//  Created on:      04-Dec-2008 8:26:34 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_09B0FD69_22E3_406c_97F4_190D33AC12B8__INCLUDED_)
#define EA_09B0FD69_22E3_406c_97F4_190D33AC12B8__INCLUDED_

class AbstractDbObjectSource
{

public:
	AbstractDbObjectSource();
	virtual ~AbstractDbObjectSource();

	virtual DbObject& getDbObjectByURL(URL url);
	bool putDbObject(DbObject& dbobj);

};
#endif // !defined(EA_09B0FD69_22E3_406c_97F4_190D33AC12B8__INCLUDED_)
