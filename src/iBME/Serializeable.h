///////////////////////////////////////////////////////////
//  Serializeable.h
//  Implementation of the Interface Serializeable
//  Created on:      20-Nov-2008 12:36:21 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_369B7B00_186D_4c22_BE50_9BF58E2CFC6D__INCLUDED_)
#define EA_369B7B00_186D_4c22_BE50_9BF58E2CFC6D__INCLUDED_

class Serializeable
{

public:
	Serializeable() {

	}

	virtual ~Serializeable() {

	}

	virtual byte[] SerializeToByteArray() =0;
	virtual void SerializeToStream(std::ostream ostr) =0;

};
#endif // !defined(EA_369B7B00_186D_4c22_BE50_9BF58E2CFC6D__INCLUDED_)
