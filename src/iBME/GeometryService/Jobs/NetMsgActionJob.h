///////////////////////////////////////////////////////////
//  NetMsgActionJob.h
//  Implementation of the Class NetMsgActionJob
//  Created on:      04-Dec-2008 8:26:45 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_5F644D4B_D513_4226_8731_6C79B3504BF4__INCLUDED_)
#define EA_5F644D4B_D513_4226_8731_6C79B3504BF4__INCLUDED_

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
#endif // !defined(EA_5F644D4B_D513_4226_8731_6C79B3504BF4__INCLUDED_)
