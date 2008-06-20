--------------------------------------------------------
INTRODUCTION
--------------------------------------------------------

This is the open source release of Mocha,
a custom C++ types library. (Version 0.1.3)

Mocha is copyright (c) Right Brain Games Inc.
For more information, visit http://www.rightbraingames.com

--------------------------------------------------------
LICENSE INFORMATION
--------------------------------------------------------

Mocha is released under the terms of the LGPL license. The contents
of the license can be viewed here: http://www.gnu.org/licenses/lgpl.html

If you would like to use Mocha as a static library without the restrictions
of the LGPL, you may obtain a separate commercial license from us. Please
contact us via our website (http://www.rightbraingames.com/contact.php) or
send an email to shane@rightbraingames.com.

--------------------------------------------------------
OVERVIEW
--------------------------------------------------------

Mocha is a small library that contains useful types for common
tasks in C++. Some of it's most important features include:

* A small and simple 3D math library, including 3D vectors, matrices and quaternions

* Input/Output stream classes for data persistance

* A COM-like class system for building application components that can be scripted

* A high-level scripting system wrapper around the Lua programming language, with
  easy to use support for micro-threading

* Thread management and synchronization classes

* A high quality random number generator class

* An easy to use class for reading/writing a simple but flexible
  XML-like data description language

* Functions for performing common string manipulation routines

* A powerful variant value type, that allows storing multiple types
  of data within a single variable

* Plenty of other useful stuff!

--------------------------------------------------------
NEW IN RELEASE 0.1.3
--------------------------------------------------------

This release adds support for serializing the Value class
to and from streams, as well as several minor bug fixes
in the stream classes. The stream read/write methods have
been renamed to readData/writeData to avoid conflicts with
using the templated read/write methods.

--------------------------------------------------------
BUILDING - Windows
--------------------------------------------------------

You must have Visual C++ 8 to use the provided project file. To compile
Mocha you must download and install the zlib compression library, which can be
retrieved from here: http://www.zlib.net

The project file contains several build configurations for building debug and
release mode DLLs, as well as debug and release modes for static linking. Please
contact us for licensing information if you would like to build Mocha for
static linking without the restrictions of the LGPL.

--------------------------------------------------------
BUILDING - Linux
--------------------------------------------------------

Building under linux uses scons ( http://www.scons.org/ ).

Cd into the Mocha directory and type scons to build. This will
build Mocha as both a static lib and a dynamically loaded lib.

Support for Linux has been provided by Paul Vollweiler.

--------------------------------------------------------
SUPPORT
--------------------------------------------------------

We will do our best to improve documentation of the library over time.
Commercial support may be obtained for a fee upon request. Please contact us
for information via our website at: http://www.rightbraingames.com/contact.php
