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


using boost::asio::ip::tcp;

///////////////////////////////////////////////////////////
//
//       Session Class
//
///////////////////////////////////////////////////////////


class session
{
public:
  session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
    std::cout << "New Session\n";
  }

  ~session() 
  { 
    std::cout << "End Session\n\n";
  }


  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    //kick things off by prepping to read.

   socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));

  }

  void handle_read(const boost::system::error_code& error,
		   size_t uint8_ts_transferred)
  {
    if (!error)
      {

	//Form recieved data

	uByte* pd = (uByte*)data_;

	array<uByte> newData(pd, uint8_ts_transferred);


	std::string str(data_);
 
	if (str.find("noecho") == std::string::npos)
	  {
	    std::cout << "Writing: (" << str.size()  << ") " << data_  << std::endl;

	    str = "You said: " + str;
	    
	    for (int i = 0; i < str.length(); ++i) {
	      data_[i] = str[i];
	    }

	    std::cout << "Writing: (" << str.size()  << ") " << data_  << std::endl;

	    //Prep a Write job:
	    boost::asio::async_write(socket_,
				     boost::asio::buffer(data_, str.length()),
				     boost::bind(&session::handle_write, 
						 this,
						 boost::asio::placeholders::error));
	  } 
	else
	  {
	    std::cout << "Skipping write...\n";
	    //Setup to read again.
	    socket_.async_read_some(boost::asio::buffer(data_, max_length),
				    boost::bind(&session::handle_read, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	  }

      }
    else
      {

	
	std::cerr << "Exception " << error << " on handle_read() \n";


	delete this;
      }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {

      std::string str(data_);
      std::cout << "Waiting for Read.\n";


      //flush the buffer when we are done with it.
      for (int i = 0; i < this->max_length; ++i ) {
	data_[i] = 0;
      }

      //Setup to read again.  Pass in an empty buffer to be used.
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
			      boost::bind(&session::handle_read, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred));
    }
    else
    {
	std::cerr << "Exception " << error << " on handle_write() \n";
      delete this;
    }
  }

private:
  tcp::socket socket_;
  enum { max_length = 10240 };
  char data_[max_length];
};


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
    session* new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
			   boost::bind(&server::handle_accept, this, new_session,
				       boost::asio::placeholders::error));
  }

  void handle_accept(session* new_session,
		     const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
      new_session = new session(io_service_);
      acceptor_.async_accept(new_session->socket(),
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
