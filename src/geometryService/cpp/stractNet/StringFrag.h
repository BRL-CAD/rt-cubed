///////////////////////////////////////////////////////////
//  StringFrag.h
//  Implementation of the Class StringFrag
//  Created on:      06-Aug-2008 7:52:07 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(STRINGFRAG_H_INCLUDED_)
#define STRINGFRAG_H_INCLUDED_

#include "MsgFrag.h"

class StringFrag : public MsgFrag<String>
{

public:
	virtual ~StringFrag();
	StringFrag(String str);
	StringFrag(DataInputStream& in);
	void Deserialize(DataInputStream& in);

protected:
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(STRINGFRAG_H_INCLUDED_)
