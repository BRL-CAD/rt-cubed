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
  // create a bag with a DEFAULT_SIZE size
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



/*
 * Input
 */
extern DataStream& operator<<(DataStream &b, Char c)
{
  b << (uChar)c;
  return b;
}
extern DataStream& operator<<(DataStream &b, uChar c)
{
  b.copyIn((void *)(&c), sizeof(uChar));
  return b;
}


extern DataStream& operator<<(DataStream &b, Short s)
{
  b << (uShort)s;
  return b;
}
extern DataStream& operator<<(DataStream &b, uShort s)
{
  uShort c = htons(s);
  b.copyIn((void *)(&c), sizeof(uShort));
  return b;
}


extern DataStream& operator<<(DataStream &b, Int i)
{
  b << (uInt)i;
  return b;
}
extern DataStream& operator<<(DataStream &b, uInt i)
{
  uInt c = htonl(i);
  b.copyIn((void *)(&c), sizeof(uInt));
  return b;
}

/*
extern DataStream& operator<<(DataStream &b, Long l)
{
  b << (uLong)l;
  return b;
}
extern DataStream& operator<<(DataStream &b, uLong l)
{
  uLong nl = htonl(l);
  b.copyIn((void *)(&nl), sizeof(uLong));
  return b;
}
*/

extern DataStream& operator<<(DataStream &b, float f)
{
  float nf;
  b.toND((uByte *)&nf, (uByte *)&f, 1);
  b.copyIn((void *)(&nf), sizeof(float)); 
  return b;
}
extern DataStream& operator<<(DataStream &b, double d)
{
  double c;
  b.toND((uByte *)&c, (uByte *)&d, 1);
  b.copyIn((void *)(&c), sizeof(double)); 
  return b;
}


extern DataStream& operator<<(DataStream &b, std::string &s)
{
  b << (uInt)s.length();
  b.copyIn((void *)(s.c_str()), s.length());
  return b;
}






/*
 * Output
 */
extern DataStream& operator>>(DataStream &b, Char& c)
{
  uChar uc;
  b >> uc;
  c = (Char)uc;
  return b;
}
extern DataStream& operator>>(DataStream &b, uChar& c)
{
  if (b.empty()) throw IOException("Stream is Empty");
  uByte *pos = (b.getData() + b.getBytesRead());
  c = 0;
  c |= *(pos);
  b.setBytesRead( b.getBytesRead() + sizeof(uChar));
  return b;
}


extern DataStream& operator>>(DataStream &b, Short& s)
{
  uShort us;
  b >> us;
  s = (Short) us;
  return b;
}
extern DataStream& operator>>(DataStream &b, uShort& s)
{
  if (b.empty()) throw IOException("Stream is Empty");
  uByte *pos = b.getData() + b.getBytesRead();
  s = 0;
  s |= *((uShort *)pos);
  s = ntohs(s);
  b.setBytesRead( b.getBytesRead() + sizeof(uShort));
  return b;
}

extern DataStream& operator>>(DataStream &b, Int& i)
{
  uInt ui;
  b >> ui;
  i = (Int) ui;
  return b;
}
extern DataStream& operator>>(DataStream &b, uInt& i)
{
  if (b.empty()) throw IOException("Stream is Empty");
  uByte *pos = b.getData() + b.getBytesRead();
  uInt l = 0;
  l = *((uInt*)pos);
  i = (uInt)ntohl(l);
  b.setBytesRead( b.getBytesRead() + sizeof(uInt));
  return b;
}
/*
extern DataStream& operator>>(DataStream &b, Long& l)
{
  uLong ul;
  b >> ul;
  l = (uLong) ul;
  return b;
}
extern DataStream& operator>>(DataStream &b, uLong& l)
{
  if (b.empty()) throw IOException("Stream is Empty");
  uByte *pos = b.getData() + b.getBytesRead();
  uInt nl = 0;
  nl = *((uInt*)pos);
  l = (uInt)ntohl(nl);
  b.setBytesRead( b.getBytesRead() + sizeof(uLong));
  return b;
}
*/

extern DataStream& operator>>(DataStream &b, float& f)
{
  if (b.empty()) throw IOException("Stream is Empty");
  uByte *pos = (b.getData() + b.getBytesRead());
  b.fromNF((uByte *)&f, (uByte *)(pos), 1);
  b.setBytesRead( b.getBytesRead() + sizeof(float));
  return b;
}
extern DataStream& operator>>(DataStream &b, double& d)
{
  if (b.empty()) throw IOException("Stream is Empty");

  uByte *pos = (b.getData() + b.getBytesRead());
  b.fromND((uByte *)&d, (uByte *)(pos), 1);
  b.setBytesRead( b.getBytesRead() + sizeof(double));
  return b;
}

extern DataStream& operator>>(DataStream &b, std::string &s)
{
  if (b.empty()) throw IOException("Stream is Empty");

  //Get the StringLen:
  uInt i;
  b >> i;
  
  uInt availableBytes;
  availableBytes = b.getBytesFilled() - b.getBytesRead(); 

  //Check to see if there is enough room to perform a read of i bytes
  if (availableBytes < i) {
    std::cerr << "Warning:  StringLength requested exceeds current Stream's endpoint. Truncating.\n";
    i = availableBytes;
  }

  uChar *buf;

  buf = new uChar[ i + 1 ]; // for null-character
  uChar *pos = ((uChar *)b.getData() + b.getBytesRead());

  for (uInt cnt = 0; cnt < i; cnt++) {
    buf[cnt] = *pos;
    pos++;
  }

  buf[i] = '\0';
  s = std::string((char*)buf);
  b.setBytesRead( b.getBytesRead() + sizeof(uChar)*i);
  return b;
}







std::string DataStream::peakString()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uInt i;
  i = this->peakInt();
  uChar *buf;
  buf = new uChar[ i + 1 ]; // for null-character
  uChar *pos = ((uChar *)this->data + this->bytesRead + 4); // + 4 for peakInt()
  for (uInt cnt = 0; cnt < i; cnt++) {
    buf[cnt] = *pos;
    pos++;
  }
  buf[i] = '\0';
  std::string s;
  s = std::string((char*)buf);
  return s;
}

uByte DataStream::peakByte()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uByte b;
  uByte *pos = (this->data + this->bytesRead);
  b = 0;
  b |= *(pos);
  return b;
}

uShort DataStream::peakShort()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uShort s;
  uByte *pos = (this->data + this->bytesRead);
  s = 0;
  s |= *((uShort *)pos);
  s = ntohs(s);
  return s;
}

uInt DataStream::peakInt()
{
  if (this->empty()) throw IOException("Stream is Empty");
  uByte *pos = (this->data + this->bytesRead);
  uInt i = 0;
  i |= *((uInt*)pos);
  i = (uInt)ntohl(i);
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
  //htonf(out, in , n);
}

void DataStream::fromNF(register uByte *out, register uByte *in, uInt n)
{
  //ntohf(out, in, n);
}

// utility fns to convert host order doubles to network order, and back.
void DataStream::toND(register uByte *out, register uByte *in, uInt n)
{
  //htond(out, in , n);
}

void DataStream::fromND(register uByte *out, register uByte *in, uInt n)
{
  //ntohd(out, in, n);
}

