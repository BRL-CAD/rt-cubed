/*                S E S S I O N . C X X
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

/** @file Session.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GeometryService/Session.h"

using boost::asio::ip::tcp;

Session::Session(boost::asio::io_service& io_service)
  : socket_(io_service)
{
  this->sessionBuffer = new DataStream(128);
  this->newMsgFlag = true;
  std::cout << "New Session\n";
}

Session::~Session() 
{ 
  delete this->sessionBuffer;
  std::cout << "End Session\n\n";
}


tcp::socket& Session::Socket()
{
  return socket_;
}

void Session::Start()
{
  //kick things off by listening for a NewRead event
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
			  boost::bind(&Session::HandleRead, this,
				      boost::asio::placeholders::error,
				      boost::asio::placeholders::bytes_transferred));

}

void Session::HandleRead(const boost::system::error_code& error,
			 size_t bytesXferred)
{
  if (!error)
    {
      
      //Read in New Data:
      this->sessionBuffer->writeUByteArray(data_, bytesXferred);
      std::cout << "\tNew data(" <<  bytesXferred << "): " << data_ << "\n";

      //Do we have more than 4 bytes of data yet?
      if (this->sessionBuffer->getBytesAvailToRead() < 4)
	{
	  socket_.async_read_some(boost::asio::buffer(data_, max_length),
				  boost::bind(&Session::HandleRead, this,
					      boost::asio::placeholders::error,
					      boost::asio::placeholders::bytes_transferred));
	  std::cout << "\tReading More...\n";
	  return;
	}


      std::cout << "\tNewMsgFlag: " << this->newMsgFlag << "\n";

      //Check to see if we are processing a new msg
      if (this->newMsgFlag) {
	//pull the 'msgLEN' out of the buffer
	this->targetLen = this->sessionBuffer->readUInt();
      }
      std::cout << "\tExpected MsgLen: " << this->targetLen << "\n";

      std::cout << "\tsessionBuffer Data: " << this->sessionBuffer->getBytesFilled() << " bytes filled, ";
      std::cout << this->sessionBuffer->getBytesRead() << " bytes read. ";
      std::cout << this->sessionBuffer->getBytesAvailToRead() << " bytes available.\n";

      //check to see if the full message has been recieved yet
      if (this->sessionBuffer->getBytesAvailToRead() < this->targetLen)
	{
	  //Setup to read some more!
	  socket_.async_read_some(boost::asio::buffer(data_, max_length),
				  boost::bind(&Session::HandleRead, this,
					      boost::asio::placeholders::error,
					      boost::asio::placeholders::bytes_transferred));
	  this->newMsgFlag = false;
	  std::cout << "\tReading More...\n";
	  return;
	} 
      else
	{
	  this->newMsgFlag = true;
	}
      std::cout << "\n\tDone Reading, making Msg.\n";


      //Now that we are >= targetLen, lets build a netMsg

      uInt msgType = this->sessionBuffer->peakUInt();
      NetMsg* msg;
      NetMsg* retMsg;
      std::cout << "\tDiscovered Msg is of type: " << msgType << "\n";


      //TODO: move these msgTypes over to a DEFINES
      switch (msgType) {

      case 0: //RemHostNameSET
	try {

	  //Recieved a RemHostNameSetMsg
	  msg = new RemHostNameSetMsg(this->sessionBuffer);

	  std::cout << "\tRecieved: ";
	  msg->printMe();

	  //Respond with a RemHostNameSetOKMsg
	  retMsg = new NetMsg(10, msg->getReUUID(), msg->getMsgUUID() );
	  this->SendMsg(retMsg);
	  delete retMsg;

	  //Then send a RemHostNameSetMsg
	  retMsg = new RemHostNameSetMsg(0,"7e213dfe-71cf-4233-8d03-c147685c4bb7",msg->getMsgUUID(),"Klaatu");
	  this->SendMsg(retMsg);

	  delete retMsg;
	  delete msg;
	} catch (IOException ioe){
	  std::cerr << ioe.getMessage() << "\n";
	  std::cerr << "There are " <<this->sessionBuffer->getBytesAvailToRead() << " bytes remaining that need to be flushed.";
	}
	break;

      case 5: //RemHostNameSETFAIL
	msg = new RemHostNameSetFailMsg(this->sessionBuffer);

	//yikes!!!!!
	delete this;
	delete msg;
	break;

      case 10: //RemHostNameSETOK
	msg = new NetMsg(this->sessionBuffer);

	std::cout << "\tRecieved: ";
	msg->printMe();
	std::cout << "\tNo Reply to this msgType.\n";
	delete msg;
	break;

      case 15: //DisconnectREQ
	msg = new NetMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();
	delete msg;
	break;

      case 20: //NewHostOneNetINFO
	msg = new RemHostNameSetMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();
	delete msg;
	break;

      case 40: //NewSessionREQ
	//Received a request for a new session:
	msg = new NetMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();

	//reply with the Session UUID
	retMsg = new RemHostNameSetMsg(50,"5e9d8909-b1e1-4af8-adff-7df78425d498", msg->getMsgUUID() ,"e277f49c-f599-4982-8284-3aNewSession");
	this->SendMsg(retMsg);

	delete retMsg;
	delete msg;

	break;

      case 45: //NewSessionREQFAIL
	msg = new RemHostNameSetFailMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();
	delete msg;
	break;

      case 50: //NewSessionREQOK
	msg = new RemHostNameSetMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();
	delete msg;
	break;

      case 100: //GeometryREQ
	msg = new GeometryReqMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();

	//Open file

	
	//Build & send manifest


	//Send CHUNK


	//Send null CHUNK


	delete msg;
	break;

      case 105: //GeometryREQFAIL
	msg = new RemHostNameSetFailMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();
	delete msg;
	break;

      case 110: //GeometryMANIFEST
	msg = new GeometryManifestMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();
	delete msg;
	break;

      case 115: //GeometryCHUNK
	msg = new RemHostNameSetMsg(this->sessionBuffer);
	std::cout << "\tRecieved: ";
	msg->printMe();
	delete msg;
	break;

        
      default:
	//We have got a bad MsgType... or corrupt data!
	std::cerr << "\nUnknown MsgType: " <<  msgType << "\nFlushing Buffer:\n";

	std::cerr << this->sessionBuffer->getBytesAvailToRead() << " bytes remaining in Buffer.\n";
	for (uInt flusher = 0 ; flusher < targetLen; ++flusher)
	  {
	    this->sessionBuffer->readUChar();
	  }
	std::cerr << this->sessionBuffer->getBytesAvailToRead() << " bytes remaining in Buffer.\n";
	

	break;

      }
      
      std::cout << "\n\n\t";
      std::cout << this->sessionBuffer->getBytesAvailToRead() << " bytes remaining in Buffer.\n";
      std::cout << "Done with Read & Send, Listening for next read...\n\n";

      //do we need to flush the buffer?

      for (uInt cnt = 0; cnt < max_length; ++cnt)
	{
	  this->data_[cnt] = '\0';
	}


      socket_.async_read_some(boost::asio::buffer(data_, max_length),
			      boost::bind(&Session::HandleRead, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred));


    }
  else
    {	 
      std::cerr << "Exception " << error << " in HandleRead() \n";
      delete this;
    }
}


void Session::SendMsg(NetMsg* msg) {
  DataStream* ds = new DataStream(128);
  msg->serialize(ds);
  
  uInt msgLen = ds->peakUInt();
  uInt dsLen = ds->getBytesAvailToRead();

  //std::cout << "According to the peakInt(), len=" << msgLen << "\n";
  //std::cout << "According to the ds.getBytesAvailToRead(), len=" << dsLen << "\n";

  uByte* dataToSend;
  dataToSend = new uByte[dsLen];
  
  msgLen = ds->readUByteArray(dataToSend, dsLen);
  //std::cout << "According to the ds->readUByteArray, len=" << msgLen << "\n";

  std::cout << "\n\tSending Msg: msgLen:\t " << msgLen << "\t ";
  msg->printMe();
  
  boost::asio::async_write(socket_,
			   boost::asio::buffer(dataToSend, dsLen),
			   boost::bind(&Session::HandleWrite, this,
				       boost::asio::placeholders::error));
  delete ds;
}




void Session::HandleWrite(const boost::system::error_code& error)
{
  if (!error)
    {
      //Setup to read again.  Pass in an empty buffer to be used.
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
			      boost::bind(&Session::HandleRead, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred));
    }
  else
    {
      std::cerr << "Exception " << error << " on handleWrite() \n";
      delete this;
    }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
