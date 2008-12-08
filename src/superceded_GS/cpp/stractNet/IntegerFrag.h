///////////////////////////////////////////////////////////
//  IntegerFrag.h
//  Implementation of the Class IntegerFrag
//  Created on:      06-Aug-2008 7:51:51 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(INTEGER_H_INCLUDED_)
#define INTEGER_H_INCLUDED_

#include "MsgFrag.h"

class IntegerFrag : public MsgFrag<Integer>
{

public:
	virtual ~IntegerFrag();
	IntegerFrag(int in);
	IntegerFrag(DataInputStream& in);
	void Deserialize(DataInputStream& in);

protected:
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(INTEGER_H_INCLUDED_)
