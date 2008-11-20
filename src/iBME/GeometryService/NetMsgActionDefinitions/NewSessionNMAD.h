///////////////////////////////////////////////////////////
//  NewSessionNMAD.h
//  Implementation of the Class NewSessionNMAD
//  Created on:      20-Nov-2008 8:00:17 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_2654A8AA_B2FA_49a9_A09E_1682227A42CF__INCLUDED_)
#define EA_2654A8AA_B2FA_49a9_A09E_1682227A42CF__INCLUDED_

#include "AbstractJob.h"
#include "NetMsg.h"
#include "AbstractNetMsgActionDef.h"

class NewSessionNMAD : public AbstractNetMsgActionDef
{

public:
	NewSessionNMAD();
	virtual ~NewSessionNMAD();

	AbstractJob convert(NetMsg msg);

};
#endif // !defined(EA_2654A8AA_B2FA_49a9_A09E_1682227A42CF__INCLUDED_)
