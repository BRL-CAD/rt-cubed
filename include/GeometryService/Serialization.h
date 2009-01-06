///////////////////////////////////////////////////////////
//  serialization.h
//  Static routines to serialize all major datatypes
//  Created on:      016-Dec-2008
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NETMSG_H__)
#define __NETMSG_H__

#include "iBME/iBMECommon.h"


class Serialization
{
 public:

  static unsigned int putByte(const unsigned char, unsigned char* dataArray);
  static unsigned int putShort(const unsigned short value, unsigned char* dataArray);
  static unsigned int putInt(const unsigned int value, unsigned char* dataArray);
  static unsigned int putLong(const unsigned long value, unsigned char* dataArray);
  static unsigned int putFloat(const unsigned float value, unsigned char* dataArray);
  static unsigned int putDouble(const unsigned double value, unsigned char* dataArray);
  static unsigned int putString(const std::string value, unsigned char* dataArray);


  static unsigned char getByte(const unsigned char* dataArray);
  static unsigned short getShort(const unsigned char* dataArray);
  static unsigned int getInt(const unsigned char* dataArray);
  static unsigned long getLong(const unsigned char* dataArray);
  static unsigned float getFloat(const unsigned char* dataArray);
  static unsigned double getDouble(const unsigned char* dataArray);
  static std::string getString(const unsigned char* dataArray);



}
