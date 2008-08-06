///////////////////////////////////////////////////////////
//  DoubleFrag.h
//  Implementation of the Class DoubleFrag
//  Created on:      06-Aug-2008 7:52:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_EE9D6A7A_2375_4574_9A3B_F0F382147DFE__INCLUDED_)
#define EA_EE9D6A7A_2375_4574_9A3B_F0F382147DFE__INCLUDED_

#include "MsgFrag.h"

class DoubleFrag : public MsgFrag<Double>
{

public:
	DoubleFrag();
	virtual ~DoubleFrag();

	DoubleFrag(double db);
	DoubleFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_EE9D6A7A_2375_4574_9A3B_F0F382147DFE__INCLUDED_)
