///////////////////////////////////////////////////////////
//  AbstractResource.h
//  Implementation of the Class DbObject
//  Created on:      04-Dec-2008 8:26:39 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__ABSTRACTRESOURCE_H__)
#define __ABSTRACTRESOURCE_H__

class DbObject {

public:
	DbObject();
	virtual ~DbObject();

	void DbObject(long id, string name, unsigned int geoType, bool locked =
			false);
	string getName();
	void setName(string name);
	unsigned int getGeoType();
	void setGeoType(unsigned int geoType);
	void lock();
	void unlock();

private:
	std::string name;
	UUID uuid;
	std::list<DbObject&> parents;
	std::list<DbObject&> children;
	int geoType;
	BrlcadDb& db_file;

};
#endif // !defined(__ABSTRACTRESOURCE_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
