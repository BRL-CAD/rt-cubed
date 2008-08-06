///////////////////////////////////////////////////////////
//  SNUtilities.h
//  Implementation of the Class SNUtilities
//  Created on:      06-Aug-2008 7:49:44 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E72E52F4_A5C3_432f_BDA4_25757E105ABC__INCLUDED_)
#define EA_E72E52F4_A5C3_432f_BDA4_25757E105ABC__INCLUDED_

#include "SNRoot.java"

class SNUtilities : public SNRoot
{

public:
	virtual ~SNUtilities();

	SNUtilities();
	static int byteArrayToInt(byte[] b);
	static int byteArrayToIntArray(byte[] b);
	static long byteArrayToLong(byte[] b);
	static long byteArrayToLongArray(byte[] b);
	static byte intArrayToByteArray(int[] ia);
	static byte intToByteArray(int i);
	static byte longArrayToByteArray(long[] la);
	static byte longToByteArray(long l);
	static byte randomByteArrayGenerator();
	static byte randomByteArrayGenerator(int length);

};
#endif // !defined(EA_E72E52F4_A5C3_432f_BDA4_25757E105ABC__INCLUDED_)
