///////////////////////////////////////////////////////////
//  AbstractNetMsgActionDef.h
//  Implementation of the Class AbstractNetMsgActionDef
//  Created on:      04-Dec-2008 8:26:35 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D66052C8_4856_48ad_A092_F95B68B6C5B2__INCLUDED_)
#define EA_D66052C8_4856_48ad_A092_F95B68B6C5B2__INCLUDED_

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
#endif // !defined(EA_D66052C8_4856_48ad_A092_F95B68B6C5B2__INCLUDED_)
