///////////////////////////////////////////////////////////
//  NetMsgActionJob.h
//  Implementation of the Class NetMsgActionJob
//  Created on:      20-Nov-2008 12:36:18 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_00AD97BE_E1CA_4c71_B925_A0BE0D95E3B8__INCLUDED_)
#define EA_00AD97BE_E1CA_4c71_B925_A0BE0D95E3B8__INCLUDED_

#include "AbstractJob.h"

class NetMsgActionJob : public AbstractJob
{

public:
	NetMsgActionJob();
	virtual ~NetMsgActionJob();

	void NetMsgActionJob(NetMsg& msg);
	virtual bool doJob();

private:
	NetMsg& msg;

};
#endif // !defined(EA_00AD97BE_E1CA_4c71_B925_A0BE0D95E3B8__INCLUDED_)
