///////////////////////////////////////////////////////////
//  Serializeable.h
//  Implementation of the Interface Serializeable
//  Created on:      20-Nov-2008 8:00:19 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_AA739D73_A4BA_4473_AD33_C006ECD0883E__INCLUDED_)
#define EA_AA739D73_A4BA_4473_AD33_C006ECD0883E__INCLUDED_

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
#endif // !defined(EA_AA739D73_A4BA_4473_AD33_C006ECD0883E__INCLUDED_)
