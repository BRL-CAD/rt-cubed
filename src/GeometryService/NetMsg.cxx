///////////////////////////////////////////////////////////
//  NetMsg.cxx
//  Implementation of the Class NetMsg
//  Created on:      04-Dec-2008 8:26:44 AM
//  Original author: Dave Loman
//
// $Revision$
// $LastChangedDate$
// $LastChangedBy$
//
///////////////////////////////////////////////////////////

#include "GeometryService/NetMsg.h"


NetMsg::NetMsg()
{
}

NetMsg::~NetMsg()
{
}

NetMsg::NetMsg(int mLen, int mType, std::string mUUID, std::string rUUID):
    msgLen(mLen), msgType(mType), msgUUID(mUUID), reUUID(rUUID)
{
}

NetMsg::NetMsg(char* uint8_tArray):data(uint8_tArray)
{
}

char* NetMsg::serialize()
{
}

void NetMsg::serialize(char* data)
{
}

void NetMsg::_deserialize()
{
}

char* NetMsg::_serialize()
{
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
