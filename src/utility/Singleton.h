/*                     S I N G L E T O N . H
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file Singleton.h
 *
 * Brief description
 *
 */

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

/* system headers */
#ifdef HAVE_ATEXIT
#	ifdef HAVE_CSTDLIB
#include <cstdlib>
using std::atexit;
#	else
#include <stdlib.h>
#	endif
#endif

/* Singleton template class
 *
 * This template class pattern provides a traditional Singleton pattern.
 * Allows you to designate a single-instance global class by inheriting
 * off of the template class.
 *
 * Example:
 *
 *   class Whatever : public Singleton<Whatever> ...
 *
 * The class will need to provide either a public or a protected friend
 * constructor:
 *
 *   friend class Singleton<Whatever>;
 *
 * The class will also need to initialize it's own instance in a single
 * compilation unit (a .cxx file):
 *
 *   // statically initialize the instance to nothing
 *   template <>
 *   Whatever* Singleton<Whatever>::_instance = 0;
 *
 * The class can easily be extended to support different allocation
 * mechanisms or multithreading access.  This implementation, however,
 * only uses new/delete and is not thread safe.
 *
 * The Singleton will automatically get destroyed when the application
 * terminates (via an atexit() hook) unless the inheriting class has an
 * accessible destructor.
 */
template < typename T >
class Singleton {

private:

  static T* _instance;

protected:

  // protection from instantiating a non-singleton Singleton
  Singleton() { }
  Singleton(T* instancePointer) { _instance = instancePointer; }
  Singleton(const Singleton &) { } // do not use
  Singleton& operator=(const Singleton&) { return *this; } // do not use
  ~Singleton() { _instance = 0; } // do not delete

  static void destroy() {
    if ( _instance != 0 ) {
      delete(_instance);
      _instance = 0;
    }
  }

public:

  /** returns a singleton
   */
  inline static T& instance() {
    if ( _instance == 0 ) {
      _instance = new T;
      // destroy the singleton when the application terminates
#ifdef HAVE_ATEXIT
      atexit(Singleton::destroy);
#endif
    }
    return *Singleton::_instance;
  }

  /** returns a singleton pointer
   */
  inline static T* pInstance() {
    if (_instance == 0) {
      _instance = new T;
#ifdef HAVE_ATEXIT
      atexit(Singleton::destroy);
#endif
    }
    return Singleton::_instance;
  }

  /** returns a const singleton reference
   */
  inline static const T& constInstance() { return *instance(); }
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
