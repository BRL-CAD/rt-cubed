///////////////////////////////////////////////////////////
//  NetMsgActionDefManager.h
//  Implementation of the Class NetMsgActionDefManager
//  Created on:      04-Dec-2008 8:26:45 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_47EEEEB4_86FF_42a0_BA79_83CF4EF92054__INCLUDED_)
#define EA_47EEEEB4_86FF_42a0_BA79_83CF4EF92054__INCLUDED_

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
#endif // !defined(EA_47EEEEB4_86FF_42a0_BA79_83CF4EF92054__INCLUDED_)
