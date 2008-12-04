///////////////////////////////////////////////////////////
//  Deserializeable.h
//  Implementation of the Interface Deserializeable
//  Created on:      04-Dec-2008 8:26:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_CAC4FE53_9F72_4cca_B848_5DA867026D98__INCLUDED_)
#define EA_CAC4FE53_9F72_4cca_B848_5DA867026D98__INCLUDED_

class Deserializeable
{

public:
	Deserializeable() {

	}

	virtual ~Deserializeable() {

	}

	virtual void Deserializeable(std::list<byte> ba) =0;
	virtual void Deserializeable(std::istream istr) =0;

};
#endif // !defined(EA_CAC4FE53_9F72_4cca_B848_5DA867026D98__INCLUDED_)
