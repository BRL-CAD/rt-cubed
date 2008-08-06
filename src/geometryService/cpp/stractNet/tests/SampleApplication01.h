///////////////////////////////////////////////////////////
//  SampleApplication01.h
//  Implementation of the Class SampleApplication01
//  Created on:      06-Aug-2008 8:03:30 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_7DCC4F10_8F7D_4e2e_9685_25E4D343C7CC__INCLUDED_)
#define EA_7DCC4F10_8F7D_4e2e_9685_25E4D343C7CC__INCLUDED_

class SampleApplication01
{

public:
	SampleApplication01();
	virtual ~SampleApplication01();

	SampleApplication01(InetAddress host, int port);
	static void main(String[] args);

};
#endif // !defined(EA_7DCC4F10_8F7D_4e2e_9685_25E4D343C7CC__INCLUDED_)
