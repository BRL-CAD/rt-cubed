///////////////////////////////////////////////////////////
//  AbstractNetMsgActionDef.h
//  Implementation of the Class AbstractNetMsgActionDef
//  Created on:      20-Nov-2008 8:00:07 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3C9C048E_A42D_4e70_8EA3_A00F665A13B8__INCLUDED_)
#define EA_3C9C048E_A42D_4e70_8EA3_A00F665A13B8__INCLUDED_

#include "AbstractJob.h"
#include "NetMsg.h"

/**
 * Base class to be extended from to implement all NetMsg to Job Conversions
 */
class AbstractNetMsgActionDef
{

public:
	AbstractNetMsgActionDef();
	virtual ~AbstractNetMsgActionDef();

	AbstractJob convert(NetMsg msg);

private:
	int msgType;

};
#endif // !defined(EA_3C9C048E_A42D_4e70_8EA3_A00F665A13B8__INCLUDED_)
