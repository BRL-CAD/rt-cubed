///////////////////////////////////////////////////////////
//  AbstractNetMsgActionDef.h
//  Implementation of the Class AbstractNetMsgActionDef
//  Created on:      04-Dec-2008 8:26:35 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__ABSTRACTNETMSGACTIONDEF_H__)
#define __ABSTRACTNETMSGACTIONDEF_H__

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
#endif // !defined(__ABSTRACTNETMSGACTIONDEF_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
