///////////////////////////////////////////////////////////
//  NewSessionNMAD.h
//  Implementation of the Class NewSessionNetMsgActionDef
//  Created on:      04-Dec-2008 8:26:46 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_6DD86C3C_9C35_4344_B578_17A0DDAF52DF__INCLUDED_)
#define EA_6DD86C3C_9C35_4344_B578_17A0DDAF52DF__INCLUDED_

#include "AbstractNetMsgActionDef.h"

class NewSessionNetMsgActionDef : public AbstractNetMsgActionDef
{

public:
	NewSessionNetMsgActionDef();
	virtual ~NewSessionNetMsgActionDef();

	AbstractJob& convert(NetMsg& msg);

};
#endif // !defined(EA_6DD86C3C_9C35_4344_B578_17A0DDAF52DF__INCLUDED_)
