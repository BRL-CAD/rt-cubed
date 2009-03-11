/*                  N E T M S G S E R I A L T E S T . C X X 
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

/** @file netMsgSerialTest.cxx
 *
 *  Description -  Tests the serialization routines of NetMsg and its
 * 		Subclasses.
 *      
 *
 *  Author - David Loman
 *
 */

#include "GeometryService/netMsg/NetMsg.h"
#include "GeometryService/netMsg/RemHostNameSetMsg.h"
#include "GeometryService/netMsg/RemHostNameSetFailMsg.h"
#include "GeometryService/netMsg/GeometryReqMsg.h"
#include "GeometryService/netMsg/GeometryManifestMsg.h"
#include "io/DataStream.h"


int main(int argc, char* argv[])
{

  unsigned int dsLen;
  DataStream* pds;


  std::cout << "\n\n\n*******************\n";
  std::cout << "Testing NetMsg.cxx:\n";
  std::cout << "*******************\n";

  NetMsg* n1 = new NetMsg(100, "60a03846-c39b-42e6-865f-394056a4fa04", "90645abd-3109-4538-a425-07810542cc2d");

  std::cout << "\nOriginal Data: \n";
  n1->printMe();

  pds = n1->serialize();

  *pds >> dsLen;
  std::cout << "\nDataStream Data: " << pds->getBytesFilled() << " bytes filled, " << pds->getBytesRead() << " bytes read. ";
  std::cout << "DataStream remaining Len is: " << dsLen << "\n";

  NetMsg* n2 = new NetMsg(pds);

  std::cout << "\nResultant Data: \n";
  n2->printMe();
  std::cout << "\n";

  delete pds;
  delete n1;
  delete n2;
 




  std::cout << "\n\n\n*******************\n";
  std::cout << "Testing RemHostNameSetMsg.cxx:\n";
  std::cout << "*******************\n";

  RemHostNameSetMsg* n3 = new RemHostNameSetMsg(100, "60a03846-c39b-42e6-865f-394056a4fa04", "90645abd-3109-4538-a425-07810542cc2d", "shota");

  std::cout << "\nOriginal Data: \n";
  n3->printMe();

  pds = n3->serialize();

  *pds >> dsLen;
  std::cout << "\nDataStream Data: " << pds->getBytesFilled() << " bytes filled, " << pds->getBytesRead() << " bytes read. ";
  std::cout << "DataStream remaining Len is: " << dsLen << "\n";

  RemHostNameSetMsg* n4 = new RemHostNameSetMsg(pds);

  std::cout << "\nResultant Data: \n";
  n4->printMe();
  std::cout << "\n";

  delete pds;
  delete n3;
  delete n4;






 

  std::cout << "\n\n\n*******************\n";
  std::cout << "Testing RemHostNameSetFailMsg.cxx:\n";
  std::cout << "*******************\n";

  RemHostNameSetFailMsg* n5 = new RemHostNameSetFailMsg(100, "60a03846-c39b-42e6-865f-394056a4fa04", "90645abd-3109-4538-a425-07810542cc2d", 150);

  std::cout << "\nOriginal Data: \n";
  n5->printMe();

  pds = n5->serialize();

  *pds >> dsLen;
  std::cout << "\nDataStream Data: " << pds->getBytesFilled() << " bytes filled, " << pds->getBytesRead() << " bytes read. ";
  std::cout << "DataStream remaining Len is: " << dsLen << "\n";

  RemHostNameSetFailMsg* n6 = new RemHostNameSetFailMsg(pds);

  std::cout << "\nResultant Data: \n";
  n6->printMe();
  std::cout << "\n";

  delete pds;
  delete n5;
  delete n6;






 

  std::cout << "\n\n\n*******************\n";
  std::cout << "Testing GeometryReqMsg.cxx:\n";
  std::cout << "*******************\n";

  GeometryReqMsg* n7 = new GeometryReqMsg(100, "60a03846-c39b-42e6-865f-394056a4fa04", "90645abd-3109-4538-a425-07810542cc2d", 160, "50a03846-c39b-42e6-865f-394056a4f99" );

  std::cout << "\nOriginal Data: \n";
  n7->printMe();

  pds = n7->serialize();

  *pds >> dsLen;
  std::cout << "\nDataStream Data: " << pds->getBytesFilled() << " bytes filled, " << pds->getBytesRead() << " bytes read. ";
  std::cout << "DataStream remaining Len is: " << dsLen << "\n";

  GeometryReqMsg* n8 = new GeometryReqMsg(pds);

  std::cout << "\nResultant Data: \n";
  n8->printMe();
  std::cout << "\n";

  delete pds;
  delete n7;
  delete n8;






 

  std::cout << "\n\n\n*******************\n";
  std::cout << "Testing GeometryManifestMsg.cxx:\n";
  std::cout << "*******************\n";

  GeometryManifestMsg* n9 = new GeometryManifestMsg(100, "60a03846-c39b-42e6-865f-394056a4fa04", "90645abd-3109-4538-a425-07810542cc2d");

  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a0000");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a1111");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a2222");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a3333");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a4444");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a5555");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a6666");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a7777");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a8888");
  n9->getItemData()->push_back("50a03846-c39b-42e6-865f-394056a9999");

  std::cout << "\nOriginal Data: \n";
  n9->printMe();

  pds = n9->serialize();

  *pds >> dsLen;
  std::cout << "\nDataStream Data: " << pds->getBytesFilled() << " bytes filled, " << pds->getBytesRead() << " bytes read. ";
  std::cout << "DataStream remaining Len is: " << dsLen << "\n";

  GeometryManifestMsg* n10 = new GeometryManifestMsg(pds);

  std::cout << "\nResultant Data: \n";
  n10->printMe();
  std::cout << "\n";
 
  delete pds;
  delete n9;
  delete n10;



  return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
