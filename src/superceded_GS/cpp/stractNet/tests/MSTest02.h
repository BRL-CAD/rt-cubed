///////////////////////////////////////////////////////////
//  MSTest02.h
//  Implementation of the Class MSTest02
//  Created on:      06-Aug-2008 8:02:44 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_A3C41B15_9C3B_4309_AD08_A4C8E2C33C1D__INCLUDED_)
#define EA_A3C41B15_9C3B_4309_AD08_A4C8E2C33C1D__INCLUDED_

#include "SNRoot.h"

/**
 * Message Delievery Speed test
 */
class MSTest02 : public SNRoot
{

public:
	virtual ~MSTest02();
	static const long Delay = 0L;
	static const int ITERATIONS = 25;
	static const int MsgsToSend = 5000;
	static MSTest02 test;
	float throughput;
	long totMsgs;
	long totTime;

	MSTest02();
	static void main(String[] args);

};
#endif // !defined(EA_A3C41B15_9C3B_4309_AD08_A4C8E2C33C1D__INCLUDED_)
