///////////////////////////////////////////////////////////
//  Serializeable.h
//  Implementation of the Interface Serializeable
//  Created on:      04-Dec-2008 8:26:47 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_C13C7A58_EF8F_412a_B4E0_C470C7AD927A__INCLUDED_)
#define EA_C13C7A58_EF8F_412a_B4E0_C470C7AD927A__INCLUDED_

class Serializeable
{

public:
	Serializeable() {

	}

	virtual ~Serializeable() {

	}

	virtual std::list<byte> SerializeToByteArray() =0;
	virtual void SerializeToStream(std::ostream ostr) =0;

};
#endif // !defined(EA_C13C7A58_EF8F_412a_B4E0_C470C7AD927A__INCLUDED_)
