///////////////////////////////////////////////////////////
//  ShortFrag.h
//  Implementation of the Class ShortFrag
//  Created on:      06-Aug-2008 7:51:59 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_8E5AA740_585E_4a78_8B55_CABB461754F7__INCLUDED_)
#define EA_8E5AA740_585E_4a78_8B55_CABB461754F7__INCLUDED_

#include "MsgFrag.h"

class ShortFrag : public MsgFrag<Short>
{

public:
	ShortFrag();
	virtual ~ShortFrag();

	ShortFrag(Short sh);
	ShortFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_8E5AA740_585E_4a78_8B55_CABB461754F7__INCLUDED_)
