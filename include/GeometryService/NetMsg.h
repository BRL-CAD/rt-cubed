///////////////////////////////////////////////////////////
//  NetMsg.h
//  Implementation of the Class NetMsg
//  Created on:      04-Dec-2008 8:26:44 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NETMSG_H__)
#define __NETMSG_H__

#include "iBME/iBMECommon.h"




class NetMsg
{

public:

  //Default Constructor
  NetMsg();

  //Regular Constructor
  NetMsg(int mLen, int mType, std::string mUUID, std::string rUUID);

  //Deserializing Constructor
  NetMsg(char* uint8_tArray);


  virtual ~NetMsg();
  

  void serialize(char* data);
  char* serialize();



private:
  int msgLen;
  int msgType;
  UUID msgUUID;
  UUID reUUID;
  char* data;


  void _deserialize();
  char* _serialize();

};
#endif // !defined(__NETMSG_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
