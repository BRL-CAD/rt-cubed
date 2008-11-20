///////////////////////////////////////////////////////////
//  NetMsgActionDefManager.h
//  Implementation of the Class NetMsgActionDefManager
//  Created on:      20-Nov-2008 8:00:16 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E5C42944_D443_48c9_9E41_7516D83CB97A__INCLUDED_)
#define EA_E5C42944_D443_48c9_9E41_7516D83CB97A__INCLUDED_

#include "AbstractNetMsgActionDef.h"

class NetMsgActionDefManager
{

public:
	NetMsgActionDefManager();
	virtual ~NetMsgActionDefManager();
	AbstractNetMsgActionDef *m_AbstractNetMsgActionDef;

	void registerNetMsgActionDef(AbstractNetMsgActionDef def);
	int unregisterNetMsgActionDef(AbstractNetMsgActionDef def);
	AbstractNetMsgActionDef unregisterNetMsgActionDef(int msgType);
	AbstractNetMsgActionDef getNetMsgActionDef(int msgType);

private:
	std::map <int, AbstractNetMsgActionDef> conversionDefs;

};
#endif // !defined(EA_E5C42944_D443_48c9_9E41_7516D83CB97A__INCLUDED_)
