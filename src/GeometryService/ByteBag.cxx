/*                     B Y T E B A G . C X X
 * BRL-CAD
 *
 * Copyright (c) 1997-2008 United States Government as represented by
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
/** @file ByteBag.cxx
 *
 *  Description -
 *      Source file for the ByteBag class.
 *
 *  Author - Jason Owens
 *
 */

#include "ByteBag.hpp"

// exception classes for ByteBag
ByteBagError::ByteBagError()
{
    print();
}

ByteBagError::~ByteBagError()
{
}

void ByteBagError::print()
{
    std::cerr << "class ByteBag Error" << std::endl;
}

ByteBagOutOfMemoryError::ByteBagOutOfMemoryError()
{
    print();
}
ByteBagOutOfMemoryError::~ByteBagOutOfMemoryError()
{
}

void ByteBagOutOfMemoryError::print()
{
    std::cerr << "Out Of Memory" << std::endl;
}

ByteBagEmptyError::ByteBagEmptyError()
{
    print();
}

ByteBagEmptyError::~ByteBagEmptyError()
{
}

void ByteBagEmptyError::print()
{
    std::cerr << "ByteBag is empty. Operation failed" << std::endl;
}


////////////////////////////////
////////////////////////////////
////////////////////////////////


// expand the bag by size if possible
int ByteBag::expand(int howMuch)
{
    char * newData = NULL;
    if (howMuch == 0) {
	return BRLCAD_OK;
    }
    newData = new char[currentSize + howMuch];
    if (newData == NULL) {
	nFerror("new() failed", "expand() did not complete");
	return BRLCAD_ERROR;
    }
    memcpy(newData, data, currentSize);
    if (newData == NULL) {
	nFerror("memcpy() failed");
	return BRLCAD_ERROR;
    }
    data = newData;
    currentSize += howMuch;
    return BRLCAD_OK;
}


// will clear the specified size with the designated character.
int ByteBag::clear(char fill, long size)
{
    if (size == 0) {
	uint8_tsFilled = 0;
	uint8_tsRead = 0;
	memset(data, (int)fill, currentSize);
    }
    else {
	uint8_tsFilled -= size;
	if (currentSize-size < uint8_tsRead)
	    uint8_tsRead = currentSize-size;
	if (uint8_tsFilled < 0) uint8_tsFilled = 0;
	memset((char*)data+uint8_tsFilled, (int)fill, size);
    }
    return BRLCAD_OK;
}

// define a plus-equals operator - this will add whatever is in the
// lvalue ByteBag into the current one
void ByteBag::operator+=(ByteBag &b)
{
    // we want to insert the other uint8_tbag's data into this uint8_tbag...
    register int bsize = b.getSize();
    if (bsize + uint8_tsFilled > currentSize) {
	if (expand((bsize+uint8_tsFilled)-currentSize)) {
	    copyIn(b.data, bsize);
	}
    }
}

// now define a concatenation operator (+)
extern ByteBag operator+(ByteBag &b, ByteBag &b1) {
    // this operator will concatenate 2 uint8_tbags and return a new
    // uint8_tbag with both sets of data... the concatenation will be
    // performed like a queue: b1b2b3b4... etc
    ByteBag newbb(b.getSize()+ b1.getSize());
    newbb.copyIn(b.data, b.getSize());
    newbb.copyIn(b1.data, b1.getSize());
    return newbb;
}

// define an assignment operator (=)
ByteBag& ByteBag::operator=(ByteBag &b)
{
    // delete the current data stored in b
    delete [] data; currentSize = uint8_tsFilled = 0;
    // copy the data in b1 into b
    copyIn(b.data, b.getSize());
    return *this;
}

// provide support for the built-in datatypes
extern ByteBag& operator<<(ByteBag &b, char c)
{
    b.copyIn(PARAM(&c), sizeof(char));
    return b;
}

extern ByteBag& operator<<(ByteBag &b, short s)
{
    short c = htons(s);
    b.copyIn(PARAM(&c), sizeof(short));
    return b;
}

extern ByteBag& operator<<(ByteBag &b, int i)
{
    // ints are not supported...
    long c = htonl((long)i);
    b.copyIn(PARAM(&c), sizeof(long));
    return b;
}

extern ByteBag& operator<<(ByteBag &b, long l)
{
    long c = htonl(l);
    b.copyIn(PARAM(&c), sizeof(long));
    return b;
}

extern ByteBag& operator<<(ByteBag &b, double d)
{
    double c;
    b.toND((unsigned char *)&c, (unsigned char *)&d, 1);
    b.copyIn(PARAM(&c), sizeof(double));
    return b;
}


extern ByteBag& operator<<(ByteBag &b, std::string &s)
{
    unsigned long l = s.length();
    switch (b.m_lwid) {
	case WID_8:
	    b << (char)l;
	    break;
	case WID_16:
	    b << (short)l;
	    break;
	case WID_32:
	    b << (long)l;
	    break;
	case WID_64:
	    b << (long)l;
	    break;
    }
    b.copyIn(PARAM(s.c_str()), l);
    return b;
}

extern ByteBag& operator>>(ByteBag &b, std::string &s)
{
    if (b.uint8_tsRead >= b.uint8_tsFilled) throw ByteBagEmptyError();
    long l;
    char *buf;
    switch (b.m_lwid) {
	case WID_8:
	    char c;
	    b >> c;
	    l = c;
	    break;
	case WID_16:
	    short s;
	    b >> s;
	    l = s;
	    break;
	case WID_32:
	    b >> l;
	    break;
	case WID_64:
	    b >> l;
	    break;
    }

    buf = new char[l+1]; // for null-character
    char *pos = ((char *)b.data+b.uint8_tsRead);
    for (int i = 0; i < l; i++) {
	buf[i] = *pos;
	pos++;
    }
    buf[l] = '\0';
    s = std::string(buf);
    b.uint8_tsRead += sizeof(char)*(l);
    return b;
}

extern ByteBag& operator>>(ByteBag &b, char& c)
{
    if (b.uint8_tsRead >= b.uint8_tsFilled) throw ByteBagEmptyError();
    char *pos = (b.data+b.uint8_tsRead);
    c = 0;
    c |= *(pos);
    b.uint8_tsRead += sizeof(char);
    return b;
}

extern ByteBag& operator>>(ByteBag &b, short& s)
{
    if (b.uint8_tsRead >= b.uint8_tsFilled) throw ByteBagEmptyError();
    char *pos = b.data+b.uint8_tsRead;
    s = 0;
    s |= *((short *)pos); s = ntohs(s);
    b.uint8_tsRead += sizeof(short);
    return b;
}

extern ByteBag& operator>>(ByteBag &b, int& i)
{
    // again, ints are not really suppported
    if (b.uint8_tsRead >= b.uint8_tsFilled) throw ByteBagEmptyError();
    char *pos = b.data+b.uint8_tsRead;
    long l = 0;
    l |= *((long*)pos); i = (int)ntohl(l);
    b.uint8_tsRead += sizeof(long);
    return b;
}

extern ByteBag& operator>>(ByteBag &b, long& l)
{
    if (b.uint8_tsRead >= b.uint8_tsFilled) throw ByteBagEmptyError();
    char *pos = b.data+b.uint8_tsRead;
    l = 0;
    l |= *((long*)pos); l = ntohl(l);
    b.uint8_tsRead += sizeof(long);
    return b;
}

extern ByteBag& operator>>(ByteBag &b, double& d)
{
    if (b.uint8_tsRead >= b.uint8_tsFilled) throw ByteBagEmptyError();
    char *pos = b.data+b.uint8_tsRead;
    b.fromND((unsigned char *)&d, (unsigned char *)(pos), 1);
    b.uint8_tsRead += sizeof(double);
    return b;
}

// utility functions to convert host order doubles to network order,
// and back.
void ByteBag::toND(register unsigned char *out, register unsigned char *in, int n)
{
    // since we know the intel machines are in little-endian uint8_t
    // order and ieee754 compliant, just flip the uint8_ts around first,
    // check to see if we are on an intel machine
    htond(out, in , n);
}

void ByteBag::fromND(register unsigned char *out, register unsigned char *in, int n)
{
    ntohd(out, in, n);
}


////////////////////////////////
////////////////////////////////
////////////////////////////////


void ByteBag::nFerror(char *mesg, char *mesg2)
{
    std::cerr << "ByteBag (NONFATAL): " << mesg << std::endl;
    if (mesg2 != 0) {
	std::cerr << "  Details: " << mesg2 << std::endl;
    }
}

void ByteBag::Ferror(char *mesg)
{
    std::cerr << "ByteBag (FATAL): " << mesg << std::endl;
    exit(-1);
}

// copy into this bag, the data (if partially full, will append like a
// stack.
int ByteBag::copyIn(const void *_data, long size)
{
    if (size == 0) { // assume that data is same size as bag
	memcpy(data, _data, currentSize);
	if (data == NULL) {
	    throw ByteBagOutOfMemoryError();
	}
	return BRLCAD_OK;
    } else {
	if (uint8_tsFilled + size > currentSize) {
	    // we need to attempt an expand...
	    if (expand((uint8_tsFilled+size) - currentSize) == BRLCAD_OK) {
		memcpy(((char*)data+uint8_tsFilled), _data, size);
		uint8_tsFilled += size;
	    } else {
		nFerror("expand() failed", "copyIn() not completed");
		return BRLCAD_ERROR;
	    }
	} else {
	    // just copy directly to that position
	    memcpy(((char *)data+uint8_tsFilled), _data, size);
	    uint8_tsFilled += size;
	}
    }
    return BRLCAD_OK;
}

//
// S H R I N K - COMPRESS THE BYTEBAG TO IT'S CURRENT FILLED SIZE.
// This should probably not be used often, since it's not implemented
// very efficiently
//
int ByteBag::shrink()
{
    char * newData = NULL;
    if (uint8_tsFilled < currentSize) {
	newData = new char[uint8_tsFilled];
	if (newData == NULL) {
	    nFerror("new() failed", "shrink() did not complete");
	    return BRLCAD_ERROR;
	}
	memcpy(newData, data, uint8_tsFilled);
	if (newData == NULL) {
	    nFerror("memcpy() failed");
	}
    }
    data = newData;
    return BRLCAD_OK;
}

//
// B B C A T    - concatenate 2 uint8_t bags together
//
ByteBag * bbCat(ByteBag &bb1, ByteBag &bb2)
{
    ByteBag *newbb;

    bb1.shrink();
    bb2.shrink();

    newbb = new ByteBag(bb1.getSize() + bb2.getSize());
    newbb->copyIn(bb1.data, bb1.getSize());
    newbb->copyIn(bb2.data, bb2.getSize());
    return newbb;
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
