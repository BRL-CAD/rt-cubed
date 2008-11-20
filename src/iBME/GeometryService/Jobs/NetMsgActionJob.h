///////////////////////////////////////////////////////////
//  NetMsgActionJob.h
//  Implementation of the Class NetMsgActionJob
//  Created on:      20-Nov-2008 8:00:16 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3C7365A2_8281_40bc_9591_E982D9F725DA__INCLUDED_)
#define EA_3C7365A2_8281_40bc_9591_E982D9F725DA__INCLUDED_

#include "NetMsg.h"
#include "AbstractJob.h"

class NetMsgActionJob : public AbstractJob
{

public:
	NetMsgActionJob();
	virtual ~NetMsgActionJob();

	void NetMsgActionJob(NetMsg msg);
	virtual bool doJob();

private:
	NetMsg msg;

};
#endif // !defined(EA_3C7365A2_8281_40bc_9591_E982D9F725DA__INCLUDED_)
