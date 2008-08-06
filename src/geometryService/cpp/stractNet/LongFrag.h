///////////////////////////////////////////////////////////
//  LongFrag.h
//  Implementation of the Class LongFrag
//  Created on:      06-Aug-2008 7:51:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E60DFF19_2099_4b1d_9A9E_BEBA965FCFF7__INCLUDED_)
#define EA_E60DFF19_2099_4b1d_9A9E_BEBA965FCFF7__INCLUDED_

#include "MsgFrag.h"

class LongFrag : public MsgFrag<Long>
{

public:
	LongFrag();
	virtual ~LongFrag();

	LongFrag(Long lo);
	LongFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_E60DFF19_2099_4b1d_9A9E_BEBA965FCFF7__INCLUDED_)
