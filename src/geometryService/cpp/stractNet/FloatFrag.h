///////////////////////////////////////////////////////////
//  FloatFrag.h
//  Implementation of the Class FloatFrag
//  Created on:      06-Aug-2008 7:52:20 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_34BAE8DF_320B_400e_8914_A1DF2627E7EA__INCLUDED_)
#define EA_34BAE8DF_320B_400e_8914_A1DF2627E7EA__INCLUDED_

#include "MsgFrag.h"

class FloatFrag : public MsgFrag<Float>
{

public:
	FloatFrag();
	virtual ~FloatFrag();

	FloatFrag(float fl);
	FloatFrag(DataInputStream in);
	void Deserialize(DataInputStream in);

protected:
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_34BAE8DF_320B_400e_8914_A1DF2627E7EA__INCLUDED_)
