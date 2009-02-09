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
      //      NetMsg* msg = NULL;
      //      NetMsg* retMsg = NULL;
      std::cout << "\tDiscovered Msg is of type: " << msgType << "\n";







      //TODO: move these msgTypes over to a DEFINES
      switch (msgType) {

      case RemHostNameSET:
	this->Handle_RemHostNameSet();
	break;

      case RemHostNameSETFAIL:
	this->Handle_RemHostNameSetFail();
	break;

      case RemHostNameSETOK:
	this->Handle_RemHostNameSetOk();
	break;

      case DisconnectREQ:
	this->Handle_DisconnectReq();
	break;

      case NewHostOnNetINFO:
	this->Handle_NewHostOnNet();
	break;

      case NewSessionREQ:
	this->Handle_NewSessionReq();
	break;

      case NewSessionREQFAIL:
	this->Handle_NewSessionReqFail();
	break;

      case NewSessionREQOK:
	this->Handle_NewSessionReqOk();
	break;

      case GeometryREQ:
	this->Handle_GeometryReq();
	break;

      case GeometryREQFAIL:
	this->Handle_GeometryReqFail();
	break;

      case GeometryMANIFEST:
	this->Handle_GeometryManifest();
	break;

      case GeometryCHUNK:
	this->Handle_GeometryChunk();
	break;

      default:
	//We have got a bad MsgType... or corrupt data!
	std::cerr << "\nUnknown MsgType: " <<  msgType << "\nFlushing Buffer:\n";

	//Take the remainder of the 'message' and remove it from the DataStream
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

      /*
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
			      boost::bind(&Session::HandleRead, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred));
      */

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




/*
 * MessageType Handlers
 */


void Session::Handle_RemHostNameSet()
{
  try {

    //Recieved a RemHostNameSetMsg
    RemHostNameSetMsg* inMsg = new RemHostNameSetMsg(this->sessionBuffer);

    std::cout << "\tRecieved: ";
    inMsg->printMe();

    //Respond with a RemHostNameSetOKMsg
    NetMsg* setOkMsg = new NetMsg(RemHostNameSETOK, inMsg->getReUUID(), inMsg->getMsgUUID() );
    this->SendMsg(setOkMsg);
    delete setOkMsg;

    //Then send a RemHostNameSetMsg
    RemHostNameSetMsg* setMsg = new RemHostNameSetMsg(RemHostNameSET,"7e213dfe-71cf-4233-8d03-c147685c4bb7",inMsg->getMsgUUID(),"Klaatu");
    this->SendMsg(setMsg);
    delete setMsg;

    delete inMsg;
  } catch (IOException ioe){
    std::cerr << ioe.getMessage() << "\n";
    std::cerr << "There are " <<this->sessionBuffer->getBytesAvailToRead() << " bytes remaining that need to be flushed.";
  }

}

void Session::Handle_RemHostNameSetFail()
{
  RemHostNameSetFailMsg* setFailMsg = new RemHostNameSetFailMsg(this->sessionBuffer);
  setFailMsg->printMe();

  delete setFailMsg;
  //yikes!!!!!
  delete this;
}

void Session::Handle_RemHostNameSetOk()
{
  NetMsg* setOkMsg = new NetMsg(this->sessionBuffer);

  std::cout << "\tRecieved: ";
  setOkMsg->printMe();
  std::cout << "\tNo Reply to this msgType.\n";

  delete setOkMsg;
}



void Session::Handle_DisconnectReq()
{
  NetMsg* disReqMsg = new NetMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  disReqMsg->printMe();
  delete disReqMsg;

}

void Session::Handle_NewHostOnNet()
{
  RemHostNameSetMsg* newHostMsg = new RemHostNameSetMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  newHostMsg->printMe();
  delete newHostMsg;

}

void Session::Handle_NewSessionReq()
{
  //Received a request for a new session:
  NetMsg* sessReqMsg = new NetMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  sessReqMsg->printMe();

  //reply with the Session UUID
  RemHostNameSetMsg* sessReqOkMsg = new RemHostNameSetMsg(NewSessionREQOK,"5e9d8909-b1e1-4af8-adff-7df78425d498", sessReqMsg->getMsgUUID() ,"e277f49c-f599-4982-8284-3aNewSession");
  this->SendMsg(sessReqOkMsg);

  delete sessReqOkMsg;
  delete sessReqMsg;

}
void Session::Handle_NewSessionReqFail()
{
  RemHostNameSetFailMsg* sessFailMsg = new RemHostNameSetFailMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  sessFailMsg->printMe();
  delete sessFailMsg;

}
void Session::Handle_NewSessionReqOk()
{
  RemHostNameSetMsg* reqOkMsg = new RemHostNameSetMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  reqOkMsg->printMe();
  delete reqOkMsg;

}

void Session::Handle_GeometryReq()
{
  GeometryReqMsg* geoReqMsg = new GeometryReqMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  geoReqMsg->printMe();

  RemHostNameSetFailMsg* geoFailMsg = NULL;

  //Get which type of request it is (Fila&Path or UUID)

  if (geoReqMsg->getReqType() == ReqByUUID) {

    std::cout << "Geometry Requested By UUID\n";

    //Send a Geometry Fail
    geoFailMsg = new RemHostNameSetFailMsg(GeometryREQFAIL,"7e213dfe-71cf-4233-8d03-c147685c4bb7",geoReqMsg->getMsgUUID(), UUIDNotFoundFailure );
    this->SendMsg(geoFailMsg);
    delete geoFailMsg;


  } else { 
    std::cout << "Geometry Requested By File and Path\n";

    //Open file
    std::string fileAndPath = geoReqMsg->getData();
    std::ifstream file(fileAndPath.c_str(), std::ios::in|std::ios::binary);

    std::cout << "File requested: " << fileAndPath;

    if(!file.is_open()) {
      std::cout << " was not found.\n";

      //Send a Geometry Fail
      geoFailMsg = new RemHostNameSetFailMsg(GeometryREQFAIL,"7e213dfe-71cf-4233-8d03-c147685c4bb8",geoReqMsg->getMsgUUID(), UUIDNotFoundFailure );
      this->SendMsg(geoFailMsg);
      delete geoFailMsg;
      
    } else {
      std::cout << " was found.\n";

      // get the length of the file
      file.seekg(0, std::ios::end);
      size_t fileSize = file.tellg();
      file.seekg(0, std::ios::beg);

      std::cout << "File requested: " << fileAndPath << " and is " << fileSize << " bytes in length.\n\n";


      //Read the file into a buffer
      uByte* tBuff = new uByte[fileSize];
      file.read((char*)tBuff, fileSize);
      file.close();

      //Build & send manifest

      std::string myGeoChunkUUID = "55e20e06-cc0e-41b6-ba9f-407a6e29ed6a";

      GeometryManifestMsg* gmm = new GeometryManifestMsg(GeometryMANIFEST, "7e213dfe-71cf-4233-8d03-c147685c4bb9",geoReqMsg->getMsgUUID());
      gmm->getItemData()->push_back(myGeoChunkUUID);
      this->SendMsg(gmm);
      delete gmm;

      //Send CHUNK(s)

      GeometryChunkMsg* gcm = new GeometryChunkMsg(GeometryCHUNK,"7e213dfe-71cf-4233-8d03-c147685c4bb9",geoReqMsg->getMsgUUID(), tBuff, fileSize);
      this->SendMsg(gcm);
      delete gcm;

      //Send null CHUNK
      uByte* nullBuff = new uByte[0];
      GeometryChunkMsg* gcmNull = new GeometryChunkMsg(GeometryCHUNK,"7e213dfe-71cf-4233-8d03-c147685c4bb9",geoReqMsg->getMsgUUID(), nullBuff, 0);
      this->SendMsg(gcmNull);
      delete gcmNull;
      delete nullBuff;

      //Send Disconnect 
      //Respond with a RemHostNameSetOKMsg
      NetMsg* disconnectMsg = new NetMsg(DisconnectREQ, geoReqMsg->getReUUID(), geoReqMsg->getMsgUUID() );
      this->SendMsg(disconnectMsg);
      delete disconnectMsg;

    }

  }
	
  //  delete geoFailMsg;
  delete geoReqMsg;

}
void Session::Handle_GeometryReqFail()
{
  RemHostNameSetFailMsg* geoReqFail = new RemHostNameSetFailMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  geoReqFail->printMe();
  delete geoReqFail;;

}
void Session::Handle_GeometryManifest()
{
  GeometryManifestMsg* msg = new GeometryManifestMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  msg->printMe();
  delete msg;

}
void Session::Handle_GeometryChunk()
{
  RemHostNameSetMsg* msg = new RemHostNameSetMsg(this->sessionBuffer);
  std::cout << "\tRecieved: ";
  msg->printMe();
  delete msg;

}







// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
