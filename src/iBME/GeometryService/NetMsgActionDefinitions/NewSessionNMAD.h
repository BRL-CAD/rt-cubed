///////////////////////////////////////////////////////////
//  NewSessionNMAD.h
//  Implementation of the Class NewSessionNMAD
//  Created on:      20-Nov-2008 12:36:19 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_43C0003D_DFCD_4eac_98DC_788A0C73A0BF__INCLUDED_)
#define EA_43C0003D_DFCD_4eac_98DC_788A0C73A0BF__INCLUDED_

#include "AbstractNetMsgActionDef.h"

class NewSessionNMAD : public AbstractNetMsgActionDef
{

public:
	NewSessionNMAD();
	virtual ~NewSessionNMAD();

	AbstractJob& convert(NetMsg& msg);

};
#endif // !defined(EA_43C0003D_DFCD_4eac_98DC_788A0C73A0BF__INCLUDED_)
