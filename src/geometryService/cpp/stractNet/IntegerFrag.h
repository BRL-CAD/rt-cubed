///////////////////////////////////////////////////////////
//  IntegerFrag.h
//  Implementation of the Class IntegerFrag
//  Created on:      06-Aug-2008 7:51:51 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_772433B9_5456_46d4_8DE2_9FF255CD4F98__INCLUDED_)
#define EA_772433B9_5456_46d4_8DE2_9FF255CD4F98__INCLUDED_

#include "MsgFrag.h"

class IntegerFrag : public MsgFrag<Integer>
{

public:
	IntegerFrag();
	virtual ~IntegerFrag();

	IntegerFrag(int in);
	IntegerFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_772433B9_5456_46d4_8DE2_9FF255CD4F98__INCLUDED_)
