///////////////////////////////////////////////////////////
//  LongFrag.h
//  Implementation of the Class LongFrag
//  Created on:      06-Aug-2008 7:51:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(LONGFRAG_H_INCLUDED_)
#define LONGFRAG_H_INCLUDED_

#include "MsgFrag.h"

class LongFrag : public MsgFrag<Long>
{

public:
	virtual ~LongFrag();
	LongFrag(Long lo);
	LongFrag(DataInputStream& in);
	void Deserialize(DataInputStream& in);

protected:
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(LONGFRAG_H_INCLUDED_)
