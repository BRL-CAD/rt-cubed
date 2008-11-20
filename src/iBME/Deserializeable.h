///////////////////////////////////////////////////////////
//  Deserializeable.h
//  Implementation of the Interface Deserializeable
//  Created on:      20-Nov-2008 12:36:13 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_C1C3674E_6A22_45c2_B945_673502BE4D7D__INCLUDED_)
#define EA_C1C3674E_6A22_45c2_B945_673502BE4D7D__INCLUDED_

class Deserializeable
{

public:
	Deserializeable() {

	}

	virtual ~Deserializeable() {

	}

	virtual void Deserializeable(byte[] ba) =0;
	virtual void Deserializeable(std::istream istr) =0;

};
#endif // !defined(EA_C1C3674E_6A22_45c2_B945_673502BE4D7D__INCLUDED_)
