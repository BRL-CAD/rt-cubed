///////////////////////////////////////////////////////////
//  StdMsgUtil.h
//  Implementation of the Class StdMsgUtil
//  Created on:      06-Aug-2008 7:51:04 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3E6C4338_A1D6_473e_8555_6B6DE7F1BB48__INCLUDED_)
#define EA_3E6C4338_A1D6_473e_8555_6B6DE7F1BB48__INCLUDED_

#include "StdMsg.h"
#include "MessagingSystem.h"
#include "SNRoot.h"

class StdMsgUtil : public SNRoot
{

public:
	virtual ~StdMsgUtil();

	StdMsgUtil();
	static StdMsg RandGenMsgFactory(MessagingSystem ms);

};
#endif // !defined(EA_3E6C4338_A1D6_473e_8555_6B6DE7F1BB48__INCLUDED_)
