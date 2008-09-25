///////////////////////////////////////////////////////////
//  NetID.h
//  Implementation of the Class NetID
//  Created on:      06-Aug-2008 7:50:46 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_8BE75042_9F10_49ed_973D_2EDE117DAA72__INCLUDED_)
#define EA_8BE75042_9F10_49ed_973D_2EDE117DAA72__INCLUDED_

#include "StringFrag.h"
#include "LongFrag.h"
#include "SNRoot.h"

class NetID : public SNRoot
{

public:
	NetID();
	virtual ~NetID();

	NetID(long ID, String host);
	NetID(NetID addr);
	NetID(DataInputStream in) throw IOException;
	String getHost();
	long getID();
	byte Serialize();
	void Serialize(DataOutputStream out);
	String toString();

private:
	StringFrag Host;
	LongFrag ID;

};
#endif // !defined(EA_8BE75042_9F10_49ed_973D_2EDE117DAA72__INCLUDED_)
