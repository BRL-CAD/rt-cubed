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
  // create a stream with  size = 32
  data = NULL;
  currentSize = 32;
  bytesFilled = 0;
  bytesRead = 0;
  data = new unsigned char[this->currentSize];
  if (data == NULL) {
    Ferror("new() failed");
  }
}


DataStream::DataStream(unsigned int size) 
{
  data = NULL;
  currentSize = size;
  bytesFilled = 0;
  bytesRead = 0;
  data = new unsigned char[size];
  if (data == NULL) {
    Ferror("new() failed");
  }
}

DataStream::DataStream(void *_data, unsigned int size) {
  data = NULL;
  currentSize = size;
  bytesFilled = 0;
  bytesRead = 0;
  data = new unsigned char[size];
  if (data == NULL) {
    Ferror("new() failed");
  }

  data = (unsigned char*)memcpy(data, _data, size);
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
unsigned int DataStream::copyIn(const void *_data, unsigned int size)
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
      unsigned int diffSize = ((this->bytesFilled + size) - this->currentSize);

      if (this->expand(diffSize) == 0) {
	memcpy(((unsigned char*)this->data + this->bytesFilled), _data, size);
	this->bytesFilled += size;
      } else {
	nFerror("expand() failed: copyIn() not completed");
	return 1;
      }
    } else {
      // No expand: Just copy directly to that position
      memcpy(((unsigned char *)this->data + this->bytesFilled), _data, size);
      this->bytesFilled += size;

    }
  }
  return 0;
}

// will clear the specified size with the designated character.
unsigned int DataStream::clear(unsigned char fill, unsigned int size)
{
  if (size == 0) {
    this->bytesFilled = 0;
    this->bytesRead = 0;
    memset(this->data, (unsigned int)fill, this->currentSize);
  }
  else {
    this->bytesFilled -= size;
    if (this->currentSize - size < this->bytesRead)
      this->bytesRead = this->currentSize - size;
    if (this->bytesFilled < 0) this->bytesFilled = 0;
    memset((unsigned char*)this->data + this->bytesFilled, (unsigned int)fill, size);
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

extern DataStream& operator<<(DataStream &b, char c)
{
  b.writeUChar((unsigned char)c);
  return b;
}
extern DataStream& operator<<(DataStream &b, unsigned char c)
{
  b.writeUChar(c);
    return b;
}


extern DataStream& operator<<(DataStream &b, short s)
{
  b.writeUShort((unsigned short)s);
  return b;
}
extern DataStream& operator<<(DataStream &b, unsigned short s)
{
  b.writeUShort(s);
  return b;
}


extern DataStream& operator<<(DataStream &b, int i)
{
  b.writeUInt((unsigned int)i);  
  return b;
}
extern DataStream& operator<<(DataStream &b, unsigned int i)
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
void DataStream::writeDataStream(DataStream& source, unsigned int baSize)
{
  unsigned int availBytes = source.getBytesAvailToRead();
  if (availBytes > 0)
    {
      for (unsigned int i = 0; i < baSize; i++)
	{
	  this->writeUChar(source.readUChar());
	}      
    }
}
void DataStream::writeUCharArray(unsigned char* ba, unsigned int baSize)
{
  for (unsigned int i = 0; i < baSize; i++)
    {
      this->writeUChar(ba[i]);
    }      
}

void DataStream::writeChar(const char c) 
{
  this->writeUChar((unsigned char)c);
}
void DataStream::writeUChar(const unsigned char c)
{
  this->copyIn((void *)(&c), sizeof(unsigned char));
}

void DataStream::writeShort(const short s) 
{
  this->writeUShort((unsigned short)s);
}
void DataStream::writeUShort(const unsigned short s)
{
  unsigned short c = htons(s);
  this->copyIn((void *)(&c), sizeof(unsigned short));
}


void DataStream::writeInt(const int i)
{
  this->writeUInt((unsigned int)i);
}
void DataStream::writeUInt(const unsigned int i)
{
  unsigned int c = htonl(i);
  this->copyIn((void *)(&c), sizeof(unsigned int));
}

void DataStream::writeFloat(const float f)
{
  float nf;
  this->toND((unsigned char *)&nf, (unsigned char *)&f, 1);
  this->copyIn((void *)(&nf), sizeof(float)); 
}
void DataStream::writeDouble(const double d)
{
  double c;
  this->toND((unsigned char *)&c, (unsigned char *)&d, 1);
  this->copyIn((void *)(&c), sizeof(double)); 
}

void DataStream::writeString(const std::string s)
{
  this->writeUInt((unsigned int)s.length());
  this->copyIn((void *)(s.c_str()), s.length());
}








/********************
 * Output
 ********************/
extern DataStream& operator>>(DataStream &b, char& c)
{
  c = b.readChar();
  return b;
}
extern DataStream& operator>>(DataStream &b, unsigned char& c)
{
  c = b.readUChar();
  return b;
}

extern DataStream& operator>>(DataStream &b, short& s)
{
  s = b.readShort();
  return b;
}
extern DataStream& operator>>(DataStream &b, unsigned short& s)
{
  s = b.readUShort();
  return b;
}

extern DataStream& operator>>(DataStream &b, int& i)
{
  i = b.readInt();
  return b;
}
extern DataStream& operator>>(DataStream &b, unsigned int& i)
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



unsigned int DataStream::readUCharArray(unsigned char* b, unsigned int size)
{
  unsigned int retVal = this->peakUCharArray(b, size);
  this->setBytesRead( this->getBytesRead() + retVal);
  return retVal;
}


char DataStream::readChar()
{
  return (char)this->readUChar();
}
unsigned char DataStream::readUChar()
{
  unsigned char c = this->peakUChar();
  this->setBytesRead( this->getBytesRead() + sizeof(unsigned char));
  return c;
}

short DataStream::readShort()
{
  return (short)this->readUShort();
}
unsigned short DataStream::readUShort()
{
  unsigned short s = this->peakUShort();
  this->setBytesRead( this->getBytesRead() + sizeof(unsigned short));
  return s;
}

int DataStream::readInt()
{
  return (int)this->readUInt();
}
unsigned int DataStream::readUInt()
{
  unsigned int i = this->peakUInt();
  this->setBytesRead( this->getBytesRead() + sizeof(unsigned int));
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
  this->setBytesRead( this->getBytesRead() + s.length() + sizeof(unsigned int));
  return s;
}



/********************
 * Peaks
 ********************/


char DataStream::peakChar()
{
  return (char)this->peakUChar();
}
unsigned char DataStream::peakUChar()
{
  if (this->empty()) throw IOException("Stream is Empty");
  unsigned char b;
  unsigned char *pos = (this->data + this->bytesRead);
  b = 0;
  b |= *(pos);
  return b;
}


short DataStream::peakShort()
{
  return (short)this->peakUShort();
}
unsigned short DataStream::peakUShort()
{
  if (this->empty()) throw IOException("Stream is Empty");
  unsigned short s;
  unsigned char *pos = (this->data + this->bytesRead);
  s = 0;
  s |= *((unsigned short *)pos);
  s = ntohs(s);
  return s;
}

int DataStream::peakInt()
{
  return (int)this->peakUInt();
}
unsigned int DataStream::peakUInt()
{
  if (this->empty()) throw IOException("Stream is Empty");
  unsigned char *pos = (this->data + this->bytesRead);
  unsigned int i = 0;
  i |= *((unsigned int*)pos);
  i = (unsigned int)ntohl(i);

  //std::cout << "Peaked a unsigned int of " << i << "\n";

  return i;
}

float DataStream::peakFloat()
{
  if (this->empty()) throw IOException("Stream is Empty");
  unsigned char *pos = (this->data + this->bytesRead);
  float f;
  this->fromNF((unsigned char *)&f, (unsigned char *)(pos), 1);
  return f;
}
double DataStream::peakDouble()
{
  if (this->empty()) throw IOException("Stream is Empty");
  unsigned char *pos = (this->data + this->bytesRead);
  double d;
  this->fromND((unsigned char *)&d, (unsigned char *)(pos), 1);
  return d;
}


std::string DataStream::peakString()
{
  //Get the std::stringLen:
  unsigned int i = this->peakUInt();

  unsigned char *buf;
  buf = new unsigned char[ i + 1 ]; // for null-character

  unsigned int used = this->peakUCharArray(buf, i, sizeof(unsigned int));

  buf[used] = '\0';

  std::string  s = std::string((char*)buf);
  return s;
}




unsigned int DataStream::peakUCharArray(unsigned char* b, unsigned int size, unsigned int offset)
{
  if (this->empty()) throw IOException("Stream is Empty");

  unsigned int realSize = size;
  unsigned int availableBytes;
  availableBytes = this->getBytesAvailToRead();

  //std::cout << "\tRequested unsigned charArray Size: " << size << "\n";

  //Check to see if there is enough room to perform a read of i bytes
  if (availableBytes < size) {
    std::cerr << "Warning:  unsigned char[] length requested exceeds current ";
    std::cerr << "Stream's endpoint. Returning all available data.\n";
    realSize = availableBytes;
  }

  unsigned char *pos = ((unsigned char *)this->getData() + this->getBytesRead() + offset);

  for (unsigned int i = 0; i < realSize; ++i) {
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
unsigned int DataStream::expand(unsigned int howMuch)
{
  unsigned char* newData = NULL;
  if (howMuch == 0) {
    return 0;
  }

  newData = new unsigned char[this->currentSize + howMuch];
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
unsigned int DataStream::shrink()
{
  unsigned char * newData = NULL;
  if (this->bytesFilled < this->currentSize) {
    newData = new unsigned char[this->bytesFilled];
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
unsigned int DataStream::getCurrentSize() 
{ 
  return this->currentSize;
}

unsigned int DataStream::getBytesFilled() 
{ 
  return this->bytesFilled;
}

unsigned int DataStream::getBytesRead() 
{ 
  return this->bytesRead;
}

unsigned int DataStream::getBytesAvailToRead() 
{ 
  return this->bytesFilled - this->bytesRead;
}



void DataStream::setBytesRead(unsigned int v) 
{ 
  this->bytesRead = v;
}

unsigned char* DataStream::getData()
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
void DataStream::toNF(register unsigned char *out, register unsigned char *in, unsigned int n)
{
  *out = *in;
  //htonf(out, in , n);
}

void DataStream::fromNF(register unsigned char *out, register unsigned char *in, unsigned int n)
{
  *out = *in;
  //ntohf(out, in, n);
}

// utility fns to convert host order doubles to network order, and back.
void DataStream::toND(register unsigned char *out, register unsigned char *in, unsigned int n)
{
  *out = *in;
  //htond(out, in , n);
}

void DataStream::fromND(register unsigned char *out, register unsigned char *in, unsigned int n)
{
  *out = *in;
  //ntohd(out, in, n);
}

