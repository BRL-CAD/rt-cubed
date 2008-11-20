///////////////////////////////////////////////////////////
//  AbstractResource.h
//  Implementation of the Class AbstractResource
//  Created on:      20-Nov-2008 12:36:08 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_9A7A2B01_318D_4090_9512_0AF27D7704A9__INCLUDED_)
#define EA_9A7A2B01_318D_4090_9512_0AF27D7704A9__INCLUDED_

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
#endif // !defined(EA_9A7A2B01_318D_4090_9512_0AF27D7704A9__INCLUDED_)
