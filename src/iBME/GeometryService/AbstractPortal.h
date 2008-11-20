///////////////////////////////////////////////////////////
//  AbstractPortal.h
//  Implementation of the Class AbstractPortal
//  Created on:      20-Nov-2008 8:00:07 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E02FC3F7_1E66_4b69_BCCC_E77FFF45019E__INCLUDED_)
#define EA_E02FC3F7_1E66_4b69_BCCC_E77FFF45019E__INCLUDED_

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
#endif // !defined(EA_E02FC3F7_1E66_4b69_BCCC_E77FFF45019E__INCLUDED_)
