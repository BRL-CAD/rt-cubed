///////////////////////////////////////////////////////////
//  AbstractResource.h
//  Implementation of the Class DbObject
//  Created on:      04-Dec-2008 8:26:39 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_50D6C7A3_6145_4055_8ABE_196D74D8D9FC__INCLUDED_)
#define EA_50D6C7A3_6145_4055_8ABE_196D74D8D9FC__INCLUDED_

class DbObject
{

public:
	DbObject();
	virtual ~DbObject();

	void DbObject(long id, string name, unsigned int geoType, bool locked = false);
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
#endif // !defined(EA_50D6C7A3_6145_4055_8ABE_196D74D8D9FC__INCLUDED_)
