///////////////////////////////////////////////////////////
//  ByteArrayFrag.h
//  Implementation of the Class ByteArrayFrag
//  Created on:      06-Aug-2008 7:52:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(BYTEARRAYFRAG_H_INCLUDED_)
#define BYTEARRAYFRAG_H_INCLUDED_

#include "MsgFrag.h"

class ByteArrayFrag : public MsgFrag<byte[]>
{

public:
	virtual ~ByteArrayFrag();
	ByteArrayFrag(byte b[]);
	ByteArrayFrag(DataInputStream& in);
	void Deserialize(DataInputStream& in);

protected:
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(BYTEARRAYFRAG_H_INCLUDED_)
