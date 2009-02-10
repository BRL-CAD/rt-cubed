/*                   D A T A S T R E A M . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/** @file DataStream.h
 *
 *  Description - Combination of ByteBag, DataInputStream and DataOutputStream
 *      
 *
 *  Author - David Loman
 *
 */
#ifndef _DATASTREAM_H_
#define _DATASTREAM_H_

#include "iBME/iBMECommon.h"
#include "exception/IOException.h"
#include <netinet/in.h>

class DataStream {
 private:

  uInt currentSize;

  uInt bytesFilled;
  uInt bytesRead; 

  uByte *data;  

  uInt expand(uInt howMuch);
  uInt shrink();

  void setBytesRead(uInt v);


 public:
  DataStream();

  /// constructor for specifying initial size
  DataStream(uInt size);

  /// constructor for specifying both initial size and data to fit
  DataStream(void *_data, uInt size);

/***************************************
 *
 * DATA IO  Functions
 *
 **************************************/
  uInt copyIn(const void *_data, uInt size = 0);
  uInt clear(uByte fill = '\0', uInt size = 0);



  friend DataStream& operator<<(DataStream &dest, DataStream source);
  friend DataStream& operator<<(DataStream &b, Char c);
  friend DataStream& operator<<(DataStream &b, uChar c);
  friend DataStream& operator<<(DataStream &b, Short s);
  friend DataStream& operator<<(DataStream &b, uShort s);
  friend DataStream& operator<<(DataStream &b, Int i);
  friend DataStream& operator<<(DataStream &b, uInt i);
  //  friend DataStream& operator<<(DataStream &b, Long l);
  //  friend DataStream& operator<<(DataStream &b, uLong l);
  friend DataStream& operator<<(DataStream &b, float f);
  friend DataStream& operator<<(DataStream &b, double d);
  friend DataStream& operator<<(DataStream &b, std::string &s);

  void writeDataStream(DataStream& source);
  void writeDataStream(DataStream& source, uInt baSize);
  void writeUByteArray(uByte* ba, uInt baSize);

  void writeChar(const Char c);
  void writeUChar(const uChar c);
  void writeShort(const Short s);
  void writeUShort(const uShort s);
  void writeInt(const Int i);
  void writeUInt(const uInt i);
  //  void writeLong(const Long l);
  //  void writeULong(const uLong l);
  void writeFloat(const float f);
  void writeDouble(const double d);
  void writeString(const std::string s);




  friend DataStream& operator>>(DataStream &b, Char &c);
  friend DataStream& operator>>(DataStream &b, uChar &c);
  friend DataStream& operator>>(DataStream &b, Short &s);
  friend DataStream& operator>>(DataStream &b, uShort &s);
  friend DataStream& operator>>(DataStream &b, Int &i);
  friend DataStream& operator>>(DataStream &b, uInt &i);
  //  friend DataStream& operator>>(DataStream &b, Long &l);
  //  friend DataStream& operator>>(DataStream &b, uLong &l);
  friend DataStream& operator>>(DataStream &b, float &f);
  friend DataStream& operator>>(DataStream &b, double &d);
  friend DataStream& operator>>(DataStream &b, std::string &s);


  uInt readUByteArray(uByte* b, uInt size);
  Char readChar();
  uChar readUChar();
  Short readShort();
  uShort readUShort();
  Int readInt();
  uInt readUInt();
  //Long readLong();
  //uLong readULong();
  float readFloat();
  double readDouble();
  std::string readString();


  uInt peakUByteArray(uByte* b, uInt size, uInt offset = 0);
  Char peakChar();
  uChar peakUChar();
  Short peakShort();
  uShort peakUShort();
  Int peakInt();
  uInt peakUInt();
  //Long peakLong();
  //uLong peakULong();
  float peakFloat();
  double peakDouble();
  std::string peakString();

/***************************************
 *
 * Getters n Setters
 *
 **************************************/
  uInt getCurrentSize();
  uInt getBytesFilled();
  uInt getBytesRead();
  uInt getBytesAvailToRead(); 
  uByte* getData();

  bool empty();
  void reset();

/***************************************
 *
 * Utility Functions
 *
 **************************************/
  void nFerror(std::string mesg);
  void Ferror(std::string mesg);
  void toND(register uByte *out, register uByte *in, uInt n);
  void fromND(register uByte *out, register uByte *in, uInt n);
  void toNF(register uByte *out, register uByte *in, uInt n);
  void fromNF(register uByte *out, register uByte *in, uInt n);

};

#endif /* _DATASTREAM_H_ */
