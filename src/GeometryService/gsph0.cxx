/*                   G S P H 0 . C X X
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

/** @file gsph0.cxx
 *
 *  Description -
 *      Initial stab at GeometryService Phase Zero.
 *
 *  Author - David Loman
 *
 */

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "iBME/iBMECommon.h"
#include "common/array.h"
#include "GeometryService/Session.h"


using boost::asio::ip::tcp;

///////////////////////////////////////////////////////////
//
//       Server Class
//
///////////////////////////////////////////////////////////


class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      acceptor_(io_service, 
      tcp::endpoint(tcp::v4(), port))
  {
    Session* new_session = new Session(io_service_);
    acceptor_.async_accept(new_session->Socket(),
			   boost::bind(&server::handle_accept, this, new_session,
				       boost::asio::placeholders::error));
  }

  void handle_accept(Session* new_session,
		     const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->Start();
      new_session = new Session(io_service_);
      acceptor_.async_accept(new_session->Socket(),
			     boost::bind(&server::handle_accept, this, new_session,
					 boost::asio::placeholders::error));
    }
    else
    {
	std::cerr << "Exception " << error << " on handle_accept() \n";
       delete new_session;
    }
  }

private:
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};



///////////////////////////////////////////////////////////
//
//        EXE entry point
//
///////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: gsph0 <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    //boost::asio::io_service::work work(io_service);

    using namespace std; // For atoi.
    server s(io_service, atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
