/*                     A C C O U N T . C X X
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
/** @file Account.cxx
 *
 * Class that represents a user's account information.
 *
 */

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include "Portal.h"

#include <ctime>

#include <QtCore/QString>

class Account
{
public:
  Account(QString uname, Portal* portal, quint32 id);
  virtual ~Account();
  QString getUname();
  time_t getInactivityTime();
  void stampLastAccess();
  quint32 getID();
  Portal* getPortal();
  
private:
  quint32 id;
  QString uname;
  Portal* portal;

  time_t lastAccess;
};

#endif /* __ACCOUNT_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
