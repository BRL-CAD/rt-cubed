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
#include "GE/exception/IOException.h"
#include <netinet/in.h>

class DataStream {
 private:

  unsigned int currentSize;

  unsigned int bytesFilled;
  unsigned int bytesRead; 

  unsigned char *data;  

  unsigned int expand(unsigned int howMuch);
  unsigned int shrink();

  void setBytesRead(unsigned int v);


 public:
  DataStream();

  /// constructor for specifying initial size
  DataStream(unsigned int size);

  /// constructor for specifying both initial size and data to fit
  DataStream(void *_data, unsigned int size);

/***************************************
 *
 * DATA IO  Functions
 *
 **************************************/
  unsigned int copyIn(const void *_data, uint size = 0);
  unsigned int clear(unsigned char fill = '\0', uint size = 0);



  friend DataStream& operator<<(DataStream &dest, DataStream source);
  friend DataStream& operator<<(DataStream &b, char c);
  friend DataStream& operator<<(DataStream &b, unsigned char c);
  friend DataStream& operator<<(DataStream &b, short s);
  friend DataStream& operator<<(DataStream &b, unsigned short s);
  friend DataStream& operator<<(DataStream &b, int i);
  friend DataStream& operator<<(DataStream &b, unsigned int i);
  friend DataStream& operator<<(DataStream &b, long l);
  friend DataStream& operator<<(DataStream &b, ulong l);
  friend DataStream& operator<<(DataStream &b, float f);
  friend DataStream& operator<<(DataStream &b, double d);
  friend DataStream& operator<<(DataStream &b, std::string &s);

  void writeDataStream(DataStream& source);
  void writeDataStream(DataStream& source, unsigned int baSize);
  void writeUCharArray(unsigned char* ba, unsigned int baSize);

  void writeChar(const char c);
  void writeUChar(const unsigned char c);
  void writeShort(const short s);
  void writeUShort(const unsigned short s);
  void writeInt(const int i);
  void writeUInt(const unsigned int i);
  void writeLong(const long l);
  void writeULong(const unsigned long l);
  void writeFloat(const float f);
  void writeDouble(const double d);
  void writeString(const std::string s);



  friend DataStream& operator>>(DataStream &b, char &c);
  friend DataStream& operator>>(DataStream &b, unsigned char &c);
  friend DataStream& operator>>(DataStream &b, short &s);
  friend DataStream& operator>>(DataStream &b, unsigned short &s);
  friend DataStream& operator>>(DataStream &b, int &i);
  friend DataStream& operator>>(DataStream &b, unsigned int &i);
  friend DataStream& operator>>(DataStream &b, long &l);
  friend DataStream& operator>>(DataStream &b, unsigned long &l);
  friend DataStream& operator>>(DataStream &b, float &f);
  friend DataStream& operator>>(DataStream &b, double &d);
  friend DataStream& operator>>(DataStream &b, std::string &s);


  unsigned int readUCharArray(unsigned char* b, unsigned int size);
  char readChar();
  unsigned char readUChar();
  short readShort();
  unsigned short readUShort();
  int readInt();
  unsigned int readUInt();
  long readLong();
  unsigned long readULong();
  float readFloat();
  double readDouble();
  std::string readString();


  unsigned int peakUCharArray(unsigned char* b, unsigned int size, unsigned int offset = 0);
  char peakChar();
  unsigned char peakUChar();
  short peakShort();
  unsigned short peakUShort();
  int peakInt();
  unsigned int peakUInt();
  long peakLong();
  unsigned long peakULong();
  float peakFloat();
  double peakDouble();
  std::string peakString();

/***************************************
 *
 * Getters n Setters
 *
 **************************************/
  unsigned int getCurrentSize();
  unsigned int getBytesFilled();
  unsigned int getBytesRead();
  unsigned int getBytesAvailToRead(); 
  unsigned char* getData();

  bool empty();
  void reset();

/***************************************
 *
 * Utility Functions
 *
 **************************************/
  void nFerror(std::string mesg);
  void Ferror(std::string mesg);
  void toND(register unsigned char *out, register unsigned char *in, unsigned int n);
  void fromND(register unsigned char *out, register unsigned char *in, unsigned int n);
  void toNF(register unsigned char *out, register unsigned char *in, unsigned int n);
  void fromNF(register unsigned char *out, register unsigned char *in, unsigned int n);

};

#endif /* _DATASTREAM_H_ */
