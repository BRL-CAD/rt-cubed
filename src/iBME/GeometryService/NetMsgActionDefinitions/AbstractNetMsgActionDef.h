///////////////////////////////////////////////////////////
//  AbstractNetMsgActionDef.h
//  Implementation of the Class AbstractNetMsgActionDef
//  Created on:      20-Nov-2008 12:36:08 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_CC1B5F3F_D715_40c1_A8E1_03B3B6305FB4__INCLUDED_)
#define EA_CC1B5F3F_D715_40c1_A8E1_03B3B6305FB4__INCLUDED_

/**
 * Base class to be extended from to implement all NetMsg to Job Conversions
 */
class AbstractNetMsgActionDef
{

public:
	AbstractNetMsgActionDef();
	virtual ~AbstractNetMsgActionDef();

	AbstractJob& convert(NetMsg& msg);

private:
	int msgType;

};
#endif // !defined(EA_CC1B5F3F_D715_40c1_A8E1_03B3B6305FB4__INCLUDED_)
