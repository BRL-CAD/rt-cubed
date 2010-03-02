/*       F A I L U R E . C X X
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
/** @file FailureMsg.cxx
 *
 * Brief description
 *
 */


#include "GS/libNetwork/FailureMsg.h"
#include <sstream>

//Normal Constructor
FailureMsg::FailureMsg(quint8 failureCode):
  GenericOneByteMsg(FAILURE, failureCode)
{
}

//Reply  Constructor
FailureMsg::FailureMsg(NetMsg* msg, quint8 failureCode):
  GenericOneByteMsg(FAILURE, msg, failureCode)
{
}

//Deserializing Constructors
FailureMsg::FailureMsg(QDataStream* ds):
  GenericOneByteMsg(ds)
{
}

/*
 *Getters n Setters
 */
quint8 FailureMsg::getFailureCode() {return this->data;}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
