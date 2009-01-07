/*                     B Y T E B A G . H P P
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
/** @file ByteBag.hpp
 *
 *  Description -
 *      The header file for the ByteBag class. This class simply represents
 *      an anonymous bag of bytes. This is how binary data should be passed
 *
 *  Author - Jason Owens
 *
 */

// so what are some additional things to do with the bytebag?  we
// might want to just insert data directly into the bag. primitive
// data types, like short, char, long, double, should be supported.

#ifndef _BYTEBAG_H_
#define _BYTEBAG_H_

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#ifdef WIN32
#  include <winsock2.h>
#else
#include <sys/types.h>
#include <netinet/in.h>
#endif

#include "bu.h"


// we will use the top of the attribute type to encode
// the width - since the type will always be a char... (one byte)
#define WID_MASK 0300
#define TYPE_MASK 0x3f
#define WID_SHIFT 6
#define WID_8 0
#define WID_16 1
#define WID_32 2
#define WID_64 3

const int DEFAULT_SIZE = 8;
#define PARAM(v) ((void *)(v))

// exception classes for ByteBag
class ByteBagError {
public:
    ByteBagError();
    ~ByteBagError();
    inline virtual void print();
};

class ByteBagOutOfMemoryError : public ByteBagError {
public:
    ByteBagOutOfMemoryError();
    ~ByteBagOutOfMemoryError() ;
    inline void print();
};

class ByteBagEmptyError : public ByteBagError {
public:
    ByteBagEmptyError();
    ~ByteBagEmptyError();
    inline void print();
};

class ByteBag {
private:
    int currentSize;
    int bytesFilled;

    long bytesRead;

    void nFerror(char *mesg, char *mesg2 = 0);
    void Ferror(char *mesg);

    char m_lwid;

public:
    char *data;

    /// default constructor
    ByteBag() {
	// create a bag with a default size of 8 bytes (64 bits)
	data = NULL;
	currentSize = DEFAULT_SIZE;
	bytesFilled = 0;
	bytesRead = 0;
	data = new char[DEFAULT_SIZE];
	if (data == NULL) {
	    Ferror("new() failed");
	}
	m_lwid = WID_32;
    }

    /// constructor for specifying initial size
    ByteBag(long size) {
	data = NULL;
	currentSize = size;
	bytesFilled = 0;
	bytesRead = 0;
	data = new char[size];
	if (data == NULL) {
	    Ferror("new() failed");
	}
	m_lwid = WID_32;
    }

    /// constructor for specifying both initial size and data to fit
    ByteBag(void *_data, long size) {
	data = NULL;
	currentSize = size;
	bytesFilled = 0;
	bytesRead = 0;
	data = new char[size];
	if (data == NULL) {
	    Ferror("new() failed");
	}
	data = (char*)memcpy(data, _data, size);
	if (data == NULL) {
	    nFerror("memcpy() failed");
	}
	m_lwid = WID_32;
    }

    /// return the current filled size of the bag
    inline int getSize();

    /// tell me if the bag is empty or not
    inline bool empty();

    inline void reset();

    /// shrink the bag to currently filled size, if possible
    inline int shrink();

    /// expand the bag by size if possible
    inline int expand(int howMuch);

    /// copy into this bag, the data (if partially full, will append like a queue
    inline int copyIn(const void *_data, long size = 0);

    /// will clear the specified size with the designated character.
    inline int clear(char fill = '\0', long size = 0);

    /**
     * define a plus-equals operator - this will add whatever is in
     * the lvalue ByteBag into the current one
     */
    inline void operator+=(ByteBag &b);

    /// now define a concatenation operator (+)
    inline friend ByteBag operator+(ByteBag &b, ByteBag &b1);

    /// define an assignment operator (=)
    inline ByteBag& operator=(ByteBag &b);

    /// provide support for the built-in datatypes
    inline friend ByteBag& operator<<(ByteBag &b, char c);
    inline friend ByteBag& operator<<(ByteBag &b, short s);
    inline friend ByteBag& operator<<(ByteBag &b, int i);
    inline friend ByteBag& operator<<(ByteBag &b, long l);
    inline friend ByteBag& operator<<(ByteBag &b, double d);
    inline friend ByteBag& operator<<(ByteBag &b, std::string &s);

    // this stupid function sets the width for strength length
    // fields... the default is long
    inline void lwid(int w);

    inline friend ByteBag& operator>>(ByteBag &b, std::string &s);
    inline friend ByteBag& operator>>(ByteBag &b, char& c);
    inline friend ByteBag& operator>>(ByteBag &b, short& s);
    inline friend ByteBag& operator>>(ByteBag &b, int& i);
    inline friend ByteBag& operator>>(ByteBag &b, long& l);
    inline friend ByteBag& operator>>(ByteBag &b, double& d);

    /// utility functions to convert host order doubles to network order, and back
    inline void toND(register unsigned char *out, register unsigned char *in, int n);
    inline void fromND(register unsigned char *out, register unsigned char *in, int n);
};

/// will concatenate two bytebags together...
ByteBag * bbCat(const ByteBag &bb1, const ByteBag &bb2);

/**
 * this stupid function sets the width for strength length
 * fields... the default is long.
 */
inline void ByteBag::lwid(int w) {
    m_lwid = w;
}


/// return the current filled size of the bag
inline int ByteBag::getSize() { return bytesFilled; }

/// tell me if the bag is empty or not
inline bool ByteBag::empty() {
    if (currentSize == 0 || bytesRead == bytesFilled)
	return true;
    return false;
}

inline void ByteBag::reset() {
    bytesRead = 0;
}

#endif /* _BYTEBAG_H_ */


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
