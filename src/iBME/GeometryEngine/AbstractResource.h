///////////////////////////////////////////////////////////
//  AbstractResource.h
//  Implementation of the Class AbstractResource
//  Created on:      20-Nov-2008 8:00:08 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_20FF477B_33BE_4e59_8DE4_2B2B50165BF9__INCLUDED_)
#define EA_20FF477B_33BE_4e59_8DE4_2B2B50165BF9__INCLUDED_

class AbstractResource
{

public:
	AbstractResource();
	virtual ~AbstractResource();

	void AbstractResource(long id, string name, unsigned int geoType, bool locked = false);
	string getName();
	void setName(string name);
	unsigned int getGeoType();
	void setGeoType(unsigned int geoType);
	void lock();
	void unlock();

private:
	std::string name;
	UUID uuid;
	std::list<AbstractResource> parents;
	std::list<AbstractResource> children;
	int geoType;
	BrlcadDbResrc db_file;

};
#endif // !defined(EA_20FF477B_33BE_4e59_8DE4_2B2B50165BF9__INCLUDED_)
