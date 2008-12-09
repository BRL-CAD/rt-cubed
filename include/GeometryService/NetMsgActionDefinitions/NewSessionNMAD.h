///////////////////////////////////////////////////////////
//  NewSessionNMAD.h
//  Implementation of the Class NewSessionNetMsgActionDef
//  Created on:      04-Dec-2008 8:26:46 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NEWSESSIONNMAD_H__)
#define __NEWSESSIONNMAD_H__

#include "GeometryService/NetMsgActionDefinitions/AbstractNetMsgActionDef.h"

class NewSessionNetMsgActionDef : public AbstractNetMsgActionDef
{

public:
	NewSessionNetMsgActionDef();
	virtual ~NewSessionNetMsgActionDef();

	AbstractJob& convert(NetMsg& msg);

};
#endif // !defined(__NEWSESSIONNMAD_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

