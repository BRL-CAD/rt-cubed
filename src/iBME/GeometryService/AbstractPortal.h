///////////////////////////////////////////////////////////
//  AbstractPortal.h
//  Implementation of the Class AbstractPortal
//  Created on:      20-Nov-2008 12:36:08 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E01DD748_B11D_4223_9B40_4533C2135B1E__INCLUDED_)
#define EA_E01DD748_B11D_4223_9B40_4533C2135B1E__INCLUDED_

class AbstractPortal
{

public:
	AbstractPortal();
	virtual ~AbstractPortal();

private:
	int connectionType;
	std::string host;
	std::list <std::string> proxy_hosts;

};
#endif // !defined(EA_E01DD748_B11D_4223_9B40_4533C2135B1E__INCLUDED_)
