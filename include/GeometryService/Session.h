/*                S E S S I O N . H
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

/** @file Session.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(__SESSION_H__)
#define __SESSION_H__

#include <cstdlib>
#include <iostream>
#include <ios>
#include <fstream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "iBME/iBMECommon.h"

#include "io/DataStream.h"
#include "GeometryService/netMsg/NetMsg.h"
#include "GeometryService/netMsg/GeometryChunkMsg.h"
#include "GeometryService/netMsg/GeometryManifestMsg.h"
#include "GeometryService/netMsg/GeometryReqMsg.h"
#include "GeometryService/netMsg/RemHostNameSetMsg.h"
#include "GeometryService/netMsg/RemHostNameSetFailMsg.h"


class Session
{

public:
  Session(boost::asio::io_service& io_service);
  virtual ~Session();

  
  boost::asio::ip::tcp::socket& Socket();
  void Start();
  void HandleRead(const boost::system::error_code& error, size_t bytesXferred);
  void SendMsg(NetMsg* msg);
  void HandleWrite(const boost::system::error_code& error);

private:
  boost::asio::ip::tcp::socket socket_;
  enum { max_length = 32 };
  uChar data_[max_length];
  DataStream* sessionBuffer;
  uInt targetLen;
  bool newMsgFlag;


  void Handle_RemHostNameSet();
  void Handle_RemHostNameSetFail();
  void Handle_RemHostNameSetOk();

  void Handle_DisconnectReq();
  void Handle_NewHostOnNet();

  void Handle_NewSessionReq();
  void Handle_NewSessionReqFail();
  void Handle_NewSessionReqOk();

  void Handle_GeometryReq();
  void Handle_GeometryReqFail();
  void Handle_GeometryManifest();
  void Handle_GeometryChunk();



};

#endif // !defined(__SESSION_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
