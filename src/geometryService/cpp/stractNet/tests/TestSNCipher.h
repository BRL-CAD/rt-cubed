///////////////////////////////////////////////////////////
//  TestSNCipher.h
//  Implementation of the Class TestSNCipher
//  Created on:      06-Aug-2008 8:02:21 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_060F0D6C_6700_4ea8_8E57_67A929ECE85E__INCLUDED_)
#define EA_060F0D6C_6700_4ea8_8E57_67A929ECE85E__INCLUDED_

class TestSNCipher
{

public:
	TestSNCipher();
	virtual ~TestSNCipher();

	static void main(String[] args);

private:
	static void printByteArray(byte[] data);

};
#endif // !defined(EA_060F0D6C_6700_4ea8_8E57_67A929ECE85E__INCLUDED_)
