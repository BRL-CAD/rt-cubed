///////////////////////////////////////////////////////////
//  NetMsgActionDefManager.h
//  Implementation of the Class NetMsgActionDefManager
//  Created on:      04-Dec-2008 8:26:45 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NETMSGACTIONDEFMANAGER_H__)
#define __NETMSGACTIONDEFMANAGER_H__

#include "AbstractNetMsgActionDef.h"

class NetMsgActionDefManager
{

public:
	NetMsgActionDefManager();
	virtual ~NetMsgActionDefManager();
	AbstractNetMsgActionDef *m_AbstractNetMsgActionDef;

	void registerNetMsgActionDef(AbstractNetMsgActionDef& def);
	int unregisterNetMsgActionDef(AbstractNetMsgActionDef& def);
	AbstractNetMsgActionDef& unregisterNetMsgActionDef(int msgType);
	AbstractNetMsgActionDef& getNetMsgActionDef(int msgType);

private:
	std::map <int, AbstractNetMsgActionDef&> conversionDefs;

};
#endif // !defined(__NETMSGACTIONDEFMANAGER_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
