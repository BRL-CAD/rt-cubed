///////////////////////////////////////////////////////////
//  DoubleFrag.h
//  Implementation of the Class DoubleFrag
//  Created on:      06-Aug-2008 7:52:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(DOUBLEFRAG_H_INCLUDED_)
#define DOUBLEFRAG_H_INCLUDED_

#include "MsgFrag.h"

class DoubleFrag : public MsgFrag<Double>
{

public:
	virtual ~DoubleFrag();
	DoubleFrag(double db);
	DoubleFrag(DataInputStream& in);
	void Deserialize(DataInputStream& in);

protected:
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(DOUBLEFRAG_H_INCLUDED_)
