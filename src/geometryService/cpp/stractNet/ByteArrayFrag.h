///////////////////////////////////////////////////////////
//  ByteArrayFrag.h
//  Implementation of the Class ByteArrayFrag
//  Created on:      06-Aug-2008 7:52:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_2F9DFEE6_BD43_4c45_A58A_43688FA45A18__INCLUDED_)
#define EA_2F9DFEE6_BD43_4c45_A58A_43688FA45A18__INCLUDED_

#include "MsgFrag.h"

class ByteArrayFrag : public MsgFrag<byte[]>
{

public:
	ByteArrayFrag();
	virtual ~ByteArrayFrag();

	ByteArrayFrag(byte[] b);
	ByteArrayFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_2F9DFEE6_BD43_4c45_A58A_43688FA45A18__INCLUDED_)
