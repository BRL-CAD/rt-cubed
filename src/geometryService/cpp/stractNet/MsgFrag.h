///////////////////////////////////////////////////////////
//  MsgFrag.h
//  Implementation of the Class MsgFrag
//  Created on:      06-Aug-2008 7:51:32 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(MSGFRAG_H_INCLUDED_)
#define MSGFRAG_H_INCLUDED_

#include "SNRoot.h"

template<E>
class MsgFrag : public SNRoot
{

public:
	static const int mftBoolean = 0;
	static const int mftByteArray = 8;
	static const int mftDouble = 1;
	static const int mftFloat = 2;
	static const int mftInteger = 3;
	static const int mftLong = 4;
	static const int mftShort = 5;
	static const int mftString = 6;
	static const int mftWaypoint = 7;

	virtual ~MsgFrag();

	E getField(); //TODO returning by value will not work for objects...
	void setField(E val);
	int getMFType();


	byte* Serialize(); //returns pointer to byte array //TODO Is this the best way to do this?  Why not hand the socket stream right to the serializer instead of going through a byte array?
	void Serialize(DataOutputStream& out);

	std::string toString();

protected:
	E field;
	int MFType;

	MsgFrag(String name, E& in, int mfType);
	MsgFrag(String name, DataInputStream& in, int mfType);
	virtual void Deserialize(DataInputStream& in);
	virtual void Serialize_Specific(DataOutputStream& out);
};
#endif // !defined(MSGFRAG_H_INCLUDED_)
