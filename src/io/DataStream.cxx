/*                   D A T A S T R E A M . C X X
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

/** @file DataStream.cxx
 *
 *  Description - Combination of ByteBag, DataInputStream and DataOutputStream
 *      
 *
 *  Author - David Loman
 *
 */

#include "io/DataStream.h"


DataStream::DataStream()
{
  // create a stream with a DEFAULT_SIZE size
  data = NULL;
  currentSize = DEFAULT_SIZE;
  bytesFilled = 0;
  bytesRead = 0;
  data = new uByte[DEFAULT_SIZE];
  if (data == NULL) {
    Ferror("new() failed");
  }
}

DataStream::DataStream(uInt size) 
{
  data = NULL;
  currentSize = size;
  bytesFilled = 0;
  bytesRead = 0;
  data = new uByte[size];
  if (data == NULL) {
    Ferror("new() failed");
  }
}

DataStream::DataStream(void *_data, uInt size) {
  data = NULL;
  currentSize = size;
  bytesFilled = 0;
  bytesRead = 0;
  data = new uByte[size];
  if (data == NULL) {
    Ferror("new() failed");
  }

  data = (uByte*)memcpy(data, _data, size);
  if (data == NULL) {
    nFerror("memcpy() failed");
  }
}

/***************************************
 *
 * DATA IO  Functions
 *
 **************************************/


// copy _data into this stream.
uInt DataStream::copyIn(const void *_data, uInt size)
{
  if (size == 0) { // assume that data is same size as stream
    memcpy(this->data, _data, this->currentSize);
    if (this->data == NULL) {
      this->nFerror("copyIn(): Out of memory!");
    }
    return 0;
  } else {

    //Check to see if we need to expand the stream
    if (this->bytesFilled + size > this->currentSize) {
      //Attempt to expand:
	  
      //calc the difference in current size and needed size
      uInt diffSize = ((this->bytesFilled + size) - this->currentSize);

      if (this->expand(diffSize) == 0) {
	memcpy(((uByte*)this->data + this->bytesFilled), _data, size);
	this->bytesFilled += size;
      } else {
	nFerror("expand() failed: copyIn() not completed");
	return 1;
      }
    } else {
      // No expand: Just copy directly to that position
      memcpy(((uByte *)this->data + this->bytesFilled), _data, size);
      this->bytesFilled += size;

    }
  }
  return 0;
}

// will clear the specified size with the designated character.
uInt DataStream::clear(uChar fill, uInt size)
{
  if (size == 0) {
    this->bytesFilled = 0;
    this->bytesRead = 0;
    memset(this->data, (uInt)fill, this->currentSize);
  }
  else {
    this->bytesFilled -= size;
    if (this->currentSize - size < this->bytesRead)
      this->bytesRead = this->currentSize - size;
    if (this->bytesFilled < 0) this->bytesFilled = 0;
    memset((uByte*)this->data + this->bytesFilled, (uInt)fill, size);
  }
  return 0;
}



/********************
 * Input
 ********************/
extern DataStream& operator<<(DataStream &dest, DataStream source)
{
  dest.writeDataStream(source, source.getBytesAvailToRead());
  return dest;
}

extern DataStream& operator<<(DataStream &b, Char c)
{
  b.writeUChar((uChar)c);
  return b;
}
extern DataStream& operator<<(DataStream &b, uChar c)
{
  b.writeUChar(c);
    return b;
}


extern DataStream& operator<<(DataStream &b, Short s)
{
  b.writeUShort((uShort)s);
  return b;
}
extern DataStream& operator<<(DataStream &b, uShort s)
{
  b.writeUShort(s);
  return b;
}


extern DataStream& operator<<(DataStream &b, Int i)
{
  b.writeUInt((uInt)i);  
  return b;
}
extern DataStream& operator<<(DataStream &b, uInt i)
{
  b.writeUInt(i);
  return b;
}

extern DataStream& operator<<(DataStream &b, float f)
{
  b.writeFloat(f);
  return b;
}
extern DataStream& operator<<(DataStream &b, double d)
{
  b.writeDouble(d);
  return b;
}


extern DataStream& operator<<(DataStream &b, std::string &s)
{
  b.writeString(s);
  return b;
}




void DataStream::writeDataStream(DataStream& source)
{
  this->writeDataStream(source, source.getBytesAvailToRead());
}
void DataStream::writeDataStream(DataStream& source, uInt baSize)
{
  uInt availBytes = source.getBytesAvailToRead();
  if (availBytes > 0)
    {
      for (uInt i = 0; i < baSize; i++)
	{
	  this->writeUChar(source.readUChar());
	}      
    }
}
void DataStream::writeUByteArray(uByte* ba, uInt baSize)
{
  for (uInt i = 0; i < baSize; i++)
    {
      this->writeUChar(ba[i]);
    }      
}

void DataStream::writeChar(const Char c) 
{
  this->writeUChar((uChar)c);
}
void DataStream::writeUChar(const uChar c)
{
  this->copyIn((void *)(&c), sizeof(uChar));
}

void DataStream::writeShort(const Short s) 
{
  this->writeUShort((uShort)s);
}
void DataStream::writeUShort(const uShort s)
{
  uShort c = htons(s);
  this->copyIn((void *)(&c), sizeof(uShort));
}


void DataStream::writeInt(const Int i)
{
  this->writeUInt((uInt)i);
}
void DataStream::writeUInt(const uInt i)
{
  uInt c = htonl(i);
  this->copyIn((void *)(&c), sizeof(uInt));
}

void DataStream::writeFloat(const float f)
{
  float nf;
  this->toND((uByte *)&nf, (uByte *)&f, 1);
  this->copyIn((void *)(&nf), sizeof(float)); 
}
void DataStream::writeDouble(const double d)
{
  double c;
  this->toND((uByte *)&c, (uByte *)&d, 1);
  this->copyIn((void *)(&c), sizeof(double)); 
}

void DataStream::writeString(const std::string s)
{
  this->writeUInt((uInt)s.length());
  this->copyIn((void *)(s.c_str()), s.length());
}








/********************
 * Output
 ********************/
extern DataStream& operator>>(DataStream &b, Char& c)
{
  c = b.readChar();
  return b;
}
extern DataStream& operator>>(DataStream &b, uChar& c)
{
  c = b.readUChar();
  return b;
}

extern DataStream& operator>>(DataStream &b, Short& s)
{
  s = b.readShort();
  return b;
}
extern DataStream& operator>>(DataStream &b, uShort& s)
{
  s = b.readUShort();
  return b;
}

extern DataStream& operator>>(DataStream &b, Int& i)
{
  i = b.readInt();
  return b;
}
extern DataStream& operator>>(DataStream &b, uInt& i)
{
  i = b.readUInt();
  return b;
}

extern DataStream& operator>>(DataStream &b, float& f)
{
  f = b.readFloat();
  return b;
}
extern DataStream& operator>>(DataStream &b, double& d)
{
  d = b.readDouble();
  return b;
}

extern DataStream& operator>>(DataStream &b, std::string &s)
{
  s = b.readString();
  return b;
}



uInt DataStream::readUByteArray(uByte* b, uInt size)
{
  uInt retVal = this->peakUByteArray(b, size);
  this->setBytesRead( this->getBytesRead() + retVal);
  return retVal;
}


Char DataStream::readChar()
{
  return (Char)this->readUChar();
}
uChar DataStream::readUChar()
{
  uChar c = this->peakUChar();
  this->setBytesRead( this->getBytesRead() + sizeof(uChar));
  return c;
}

Short DataStream::readShort()
{
  return (Short)this->readUShort();
}
uShort DataStream::readUShort()
{
  uShort s = this->peakUShort();
  this->setBytesRead( this->getBytesRead() + sizeof(uShort));
  return s;
}

Int DataStream::readInt()
{
  return (Int)this->readUInt();
}
uInt DataStream::readUInt()
{
  uInt i = this->peakUInt();
  this->setBytesRead( this->getBytesRead() + sizeof(uInt));
  return i;
}

float DataStream::readFloat()
{
  float f = this->peakFloat();
  this->setBytesRead( this->getBytesRead() + sizeof(float));
  return f;
}
double DataStream::readDouble()
{
  double d = this->peakDouble();
  this->setBytesRead( this->getBytesRead() + sizeof(double));
  return d;
}

std::string DataStream::readString()
{
  std::string s;
  s = this->peakString();
  this->setBytesRead( this->getBytesRead() + s.length() + sizeof(uInt));
  return s;
}



/********************
 * Peaks
 ********************/


Char DataStream::peakChar()
{
  return (Char)this->peakUChar();
}
uChar DataStream::peakUChar()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uByte b;
  uByte *pos = (this->data + this->bytesRead);
  b = 0;
  b |= *(pos);
  return b;
}


Short DataStream::peakShort()
{
  return (Short)this->peakUShort();
}
uShort DataStream::peakUShort()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uShort s;
  uByte *pos = (this->data + this->bytesRead);
  s = 0;
  s |= *((uShort *)pos);
  s = ntohs(s);
  return s;
}

Int DataStream::peakInt()
{
  return (Int)this->peakUInt();
}
uInt DataStream::peakUInt()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uByte *pos = (this->data + this->bytesRead);
  uInt i = 0;
  i |= *((uInt*)pos);
  i = (uInt)ntohl(i);

  //std::cout << "Peaked a uInt of " << i << "\n";

  return i;
}

float DataStream::peakFloat()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uByte *pos = (this->data + this->bytesRead);
  float f;
  this->fromNF((uByte *)&f, (uByte *)(pos), 1);
  return f;
}
double DataStream::peakDouble()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uByte *pos = (this->data + this->bytesRead);
  double d;
  this->fromND((uByte *)&d, (uByte *)(pos), 1);
  return d;
}


std::string DataStream::peakString()
{
  //Get the StringLen:
  uInt i = this->peakUInt();

  uChar *buf;
  buf = new uChar[ i + 1 ]; // for null-character

  uInt used = this->peakUByteArray(buf, i, sizeof(uInt));

  buf[used] = '\0';

  std::string  s = std::string((char*)buf);
  return s;
}




uInt DataStream::peakUByteArray(uByte* b, uInt size, uInt offset)
{
  if (this->empty()) throw IOException("Stream is Empty");

  uInt realSize = size;
  uInt availableBytes;
  availableBytes = this->getBytesAvailToRead();

  //std::cout << "\tRequested uByteArray Size: " << size << "\n";

  //Check to see if there is enough room to perform a read of i bytes
  if (availableBytes < size) {
    std::cerr << "Warning:  uByte[] length requested exceeds current ";
    std::cerr << "Stream's endpoint. Returning all available data.\n";
    realSize = availableBytes;
  }

  uChar *pos = ((uChar *)this->getData() + this->getBytesRead() + offset);

  for (uInt i = 0; i < realSize; ++i) {
    b[i] = *pos;
    pos++;
  }

  return realSize;
}





/***************************************
 *
 * Stream Size Adjust Functions
 *
 **************************************/

// expand the stream by size if possible
uInt DataStream::expand(uInt howMuch)
{
  uByte* newData = NULL;
  if (howMuch == 0) {
    return 0;
  }

  newData = new uByte[this->currentSize + howMuch];
  if (newData == NULL) {
    nFerror("new() failed, expand() did not complete");
    return 1;
  }

  memcpy(newData, this->data, this->currentSize);
  if (newData == NULL) {
    nFerror("memcpy() failed");
    return 2;
  }

  this->data = newData;
  this->currentSize += howMuch;
  return 0;
}

// shrink the stream to the size of bytesFilled.
uInt DataStream::shrink()
{
  uByte * newData = NULL;
  if (this->bytesFilled < this->currentSize) {
    newData = new uByte[this->bytesFilled];
    if (newData == NULL) {
      nFerror("new() failed, shrink() did not complete");
      return 1;
    }

    memcpy(newData, this->data, this->bytesFilled);
    if (newData == NULL) {
      nFerror("memcpy() failed");
    }
  }
  this->data = newData;
  return 0;
}


/***************************************
 *
 * Getters n Setters
 *
 **************************************/
uInt DataStream::getCurrentSize() 
{ 
  return this->currentSize;
}

uInt DataStream::getBytesFilled() 
{ 
  return this->bytesFilled;
}

uInt DataStream::getBytesRead() 
{ 
  return this->bytesRead;
}

uInt DataStream::getBytesAvailToRead() 
{ 
  return this->bytesFilled - this->bytesRead;
}



void DataStream::setBytesRead(uInt v) 
{ 
  this->bytesRead = v;
}

uByte* DataStream::getData()
{
  return this->data;
}


bool DataStream::empty() {
  if (this->currentSize == 0 || this->bytesRead >= this->bytesFilled)
    return true;
  return false;
}

void DataStream::reset() {
  this->bytesRead = 0;
}

/***************************************
 *
 * Utility Functions
 *
 **************************************/
void DataStream::nFerror(std::string mesg)
{
  std::cerr << "DataStream (NONFATAL): \t" << mesg << std::endl;
}

void DataStream::Ferror(std::string mesg)
{
  std::cerr << "DataStream (FATAL): \t" << mesg << std::endl;
  exit(-1);
}

// utility fns to convert host order Floats to network order, and back.
void DataStream::toNF(register uByte *out, register uByte *in, uInt n)
{
  *out = *in;
  //htonf(out, in , n);
}

void DataStream::fromNF(register uByte *out, register uByte *in, uInt n)
{
  *out = *in;
  //ntohf(out, in, n);
}

// utility fns to convert host order doubles to network order, and back.
void DataStream::toND(register uByte *out, register uByte *in, uInt n)
{
  *out = *in;
  //htond(out, in , n);
}

void DataStream::fromND(register uByte *out, register uByte *in, uInt n)
{
  *out = *in;
  //ntohd(out, in, n);
}

