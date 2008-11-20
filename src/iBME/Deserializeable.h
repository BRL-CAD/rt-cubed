///////////////////////////////////////////////////////////
//  Deserializeable.h
//  Implementation of the Interface Deserializeable
//  Created on:      20-Nov-2008 8:00:11 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_0F798DF0_E85F_48ef_9970_25CB5E8FA82B__INCLUDED_)
#define EA_0F798DF0_E85F_48ef_9970_25CB5E8FA82B__INCLUDED_

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
#endif // !defined(EA_0F798DF0_E85F_48ef_9970_25CB5E8FA82B__INCLUDED_)
