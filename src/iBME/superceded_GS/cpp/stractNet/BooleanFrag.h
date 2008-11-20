///////////////////////////////////////////////////////////
//  BooleanFrag.h
//  Implementation of the Class BooleanFrag
//  Created on:      06-Aug-2008 7:52:28 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(BOOLEANFRAG_H_INCLUDED_)
#define BOOLEANFRAG_H_INCLUDED_

#include "MsgFrag.h"

class BooleanFrag : public MsgFrag<Boolean>
{

public:
	virtual ~BooleanFrag();
	BooleanFrag(boolean boo);
	BooleanFrag(DataInputStream& in);
	void Deserialize(DataInputStream& in);

protected:
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(BOOLEANFRAG_H_INCLUDED_)
