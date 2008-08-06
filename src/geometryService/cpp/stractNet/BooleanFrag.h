///////////////////////////////////////////////////////////
//  BooleanFrag.h
//  Implementation of the Class BooleanFrag
//  Created on:      06-Aug-2008 7:52:28 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_1F57D000_5859_498b_8D6D_9B169E7E2DB2__INCLUDED_)
#define EA_1F57D000_5859_498b_8D6D_9B169E7E2DB2__INCLUDED_

#include "MsgFrag.h"

class BooleanFrag : public MsgFrag<Boolean>
{

public:
	BooleanFrag();
	virtual ~BooleanFrag();

	BooleanFrag(boolean boo);
	BooleanFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_1F57D000_5859_498b_8D6D_9B169E7E2DB2__INCLUDED_)
