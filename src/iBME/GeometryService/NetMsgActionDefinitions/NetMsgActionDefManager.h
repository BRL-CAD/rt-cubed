///////////////////////////////////////////////////////////
//  NetMsgActionDefManager.h
//  Implementation of the Class NetMsgActionDefManager
//  Created on:      20-Nov-2008 12:36:18 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_1A1BBFF4_3CE6_4836_96AE_21987FEDCD02__INCLUDED_)
#define EA_1A1BBFF4_3CE6_4836_96AE_21987FEDCD02__INCLUDED_

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
#endif // !defined(EA_1A1BBFF4_3CE6_4836_96AE_21987FEDCD02__INCLUDED_)
