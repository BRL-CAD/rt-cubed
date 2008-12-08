///////////////////////////////////////////////////////////
//  AbstractPortal.h
//  Implementation of the Class AbstractPortal
//  Created on:      04-Dec-2008 8:26:36 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E11D0280_A321_42fb_81AD_E940D83D21E7__INCLUDED_)
#define EA_E11D0280_A321_42fb_81AD_E940D83D21E7__INCLUDED_

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
#endif // !defined(EA_E11D0280_A321_42fb_81AD_E940D83D21E7__INCLUDED_)
