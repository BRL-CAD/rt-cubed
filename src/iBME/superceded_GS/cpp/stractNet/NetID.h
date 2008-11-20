///////////////////////////////////////////////////////////
//  NetID.h
//  Implementation of the Class NetID
//  Created on:      06-Aug-2008 7:50:46 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(NETID_H_INCLUDED_)
#define NETID_H_INCLUDED_

#include "StringFrag.h"
#include "LongFrag.h"
#include "SNRoot.h"
#include <vector>
#include <string>


class NetID: public SNRoot {

public:
	virtual ~NetID();
	NetID(long ID, std::string host);
	NetID(NetID& addr);
	NetID(DataInputStream& in);

	std::string getHost();
	long getID();
	std::vector<byte> Serialize();
	void Serialize(DataOutputStream& out);
	std::string toString();

private:
	StringFrag Host;
	LongFrag ID;

};
#endif // !defined(NETID_H_INCLUDED_)
