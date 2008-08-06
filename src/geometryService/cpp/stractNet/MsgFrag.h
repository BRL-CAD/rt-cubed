///////////////////////////////////////////////////////////
//  MsgFrag.h
//  Implementation of the Class MsgFrag
//  Created on:      06-Aug-2008 7:51:32 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_7F69ABBB_419C_4b74_A909_67A3AFCCEA27__INCLUDED_)
#define EA_7F69ABBB_419C_4b74_A909_67A3AFCCEA27__INCLUDED_

#include "SNRoot.h"

template<E>
class MsgFrag : public SNRoot
{

public:
	MsgFrag();
	virtual ~MsgFrag();
	static const int mftBoolean = 0;
	static const int mftByteArray = 8;
	static const int mftDouble = 1;
	static const int mftFloat = 2;
	static const int mftInteger = 3;
	static const int mftLong = 4;
	static const int mftShort = 5;
	static const int mftString = 6;
	static const int mftWaypoint = 7;

	E getField(){

		return  NULL;
	}
	int getMFType(){

		return MFType;
	}
	byte Serialize(){

		return  NULL;
	}
	void Serialize(DataOutputStream out) throw IOException{

	}
	void setField(E val){

	}
	String toString(){

		return  NULL;
	}

protected:
	E field;
	int MFType;

	MsgFrag(String name, E in, int mfType){

	}
	MsgFrag(String name, DataInputStream in, int mfType){

	}
	virtual void Deserialize(DataInputStream in){

	}
	virtual void Serialize_Specific(DataOutputStream out){

	}

};
#endif // !defined(EA_7F69ABBB_419C_4b74_A909_67A3AFCCEA27__INCLUDED_)
