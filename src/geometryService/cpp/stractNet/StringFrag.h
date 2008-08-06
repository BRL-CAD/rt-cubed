///////////////////////////////////////////////////////////
//  StringFrag.h
//  Implementation of the Class StringFrag
//  Created on:      06-Aug-2008 7:52:07 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_DC000EB2_F3F3_421f_8EE1_1D04B06930C4__INCLUDED_)
#define EA_DC000EB2_F3F3_421f_8EE1_1D04B06930C4__INCLUDED_

#include "MsgFrag.h"

class StringFrag : public MsgFrag<String>
{

public:
	StringFrag();
	virtual ~StringFrag();

	StringFrag(String str);
	StringFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_DC000EB2_F3F3_421f_8EE1_1D04B06930C4__INCLUDED_)
