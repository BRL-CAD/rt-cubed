///////////////////////////////////////////////////////////
//  FloatFrag.h
//  Implementation of the Class FloatFrag
//  Created on:      06-Aug-2008 7:52:20 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(FLOATFRAG_H_INCLUDED_)
#define FLOATFRAG_H_INCLUDED_

#include "MsgFrag.h"

class FloatFrag : public MsgFrag<Float>
{

public:
	virtual ~FloatFrag();
	FloatFrag(float fl);
	FloatFrag(DataInputStream& in);
	void Deserialize(DataInputStream& in);

protected:
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(FLOATFRAG_H_INCLUDED_)
