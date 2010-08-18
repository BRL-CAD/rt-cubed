/*                  P K G C P P T E S T . C X X
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
/** @file pkgcppTest.cxx
 *
 * Brief description
 *
 */

#include "brlcad/bu.h"
#include "brlcad/pkg.h"
#include "libpkgcpp.h"
#include <stdio.h>
#include <iostream>

#define SERVER_NAME "ImaServer"
#define CLIENT_NAME "ImaClient"
#define ENET_PROTO "tcp"

/* simple network transport protocol. connection starts with a HELO,
 * then a variable number of GEOM/ARGS messages, then a CIAO to end.
 */

#define MSG_HELO        1
#define MSG_DATA        2
#define MSG_CIAO        3


//Declares
void printUsage(std::string customMsg);
std::string getValidIpOrHostname(char* data);
int getValidPort(char* data);

int runServer(int port);
int runClient(std::string ipOrHostname, int port);

void server_helo(struct pkg_conn* connection, char* buf);
void server_data(struct pkg_conn* connection, char* buf);
void server_ciao(struct pkg_conn* connection, char* buf);



int
main(int argc, char** argv)
{

  if (argc > 4 || argc < 3)
    {
      printUsage("Incorrect ARG count.");
      bu_exit(1, "");
    }

  bool isServer;

  //Get app mode.  Either client or server
  std::string cliServ(argv[1]);
  std::transform(cliServ.begin(), cliServ.end(), cliServ.begin(), tolower);

  if (cliServ == "client" ) {
    isServer = false;
  } else if (cliServ == "server") {
    isServer = true;
  } else {
    printUsage("Unknown mode: '" + cliServ + "'");
    bu_exit(1, "");
  }

  int exitVal = 0;
  if (isServer) {
    int port = getValidPort(argv[2]);
    exitVal = runServer(port);

  } else {
    std::string ipOrHostname = getValidIpOrHostname(argv[2]);
    int port = getValidPort(argv[3]);
    exitVal = runClient(ipOrHostname, port);
  }

  return exitVal;
}

/**
 * Converts char* data to a std::string that represents an IP or a hostname
 */
std::string
getValidIpOrHostname(char* data)
{
  //Check IP/Host
   std::string ipOrHostname(data);

   if (ipOrHostname.length() > 0 ) {
     //More validation goes here, if needed.
   } else {
     printUsage("Supplied IP/Host: '" + ipOrHostname+ "' is invalid");
     bu_exit(1, "");
   }

   return ipOrHostname;
}

/**
 * Converts char* data to a valid port number
 */
int
getValidPort(char* data)
{
  std::string portStr(data);
  int port = atoi(data);

  //Hardcode prolly not best for OS determined port range....
  if (port > 0x0000 && port < 0xFFFF ) {
    //More validation goes here, if needed.
  } else {
    printUsage("Supplied Port '" + portStr+ "' is invalid.");
    bu_exit(1, "");
  }
  return port;
}

int
runServer(int port)
{

  struct pkg_switch callbacks[] = {
       {MSG_HELO, server_helo, "HELO"},
       {MSG_DATA, server_data, "DATA"},
       {MSG_CIAO, server_ciao, "CIAO"},
       {0, 0, (char* )0}
  };


  PkgServer pkgServer(callbacks);
  pkgServer.listen(port);


  //Setup vars
  struct pkg_conn* currentClient;
  int netfd;
  int pkg_result  = 0;
  char* buffer;

  PkgClient* pkgClient = NULL;

  /* listen for a good client indefinitely.  this is a simple
   * handshake that waits for a HELO message from the client.  if it
   * doesn't get one, the server continues to wait.
   */
  do
    {
      pkgClient = pkgServer.waitForClient();

      currentClient = pkg_getclient(netfd, callbacks, NULL, 0);
      if (pkgClient == NULL)
        continue;

      /* got a connection, process it */
      buffer = pkg_bwaitfor(MSG_HELO, currentClient);
      if (buffer == NULL)
        {
          bu_log("Failed to process the client connection, still waiting\n");
          pkg_close(currentClient);
          currentClient = PKC_NULL;
        }
      else
        {
          /* validate magic header that client should have sent */
//          if (strcmp(buffer, MAGIC_ID) != 0)
//            {
//              bu_log(
//                  "Bizarre corruption, received a HELO without at matching MAGIC ID!\n");
//              pkg_close(currentClient);
//              currentClient = PKC_NULL;
//            }
        }
    }
  while (pkgClient == NULL);

  /* we got a validated client, process packets from the
   * connection.  boilerplate triple-call loop.
   */
  bu_log("Processing data from client\n");
  do {
      /* process packets potentially received in a processing callback */
      pkg_result = pkg_process(currentClient);
      if (pkg_result < 0) {
          bu_log("Unable to process packets? Weird.\n");
      } else {
          bu_log("Processed %d packet%s\n", pkg_result, pkg_result == 1 ? "" : "s");
      }

      /* suck in data from the network */
      pkg_result = pkg_suckin(currentClient);
      if (pkg_result < 0) {
          bu_log("Seemed to have trouble sucking in packets.\n");
          break;
      } else if (pkg_result == 0) {
          bu_log("Client closed the connection.\n");
          break;
      }

      /* process new packets received */
      pkg_result = pkg_process(currentClient);
      if (pkg_result < 0) {
          bu_log("Unable to process packets? Weird.\n");
      } else {
          bu_log("Processed %d packet%s\n", pkg_result, pkg_result == 1 ? "" : "s");
      }
  } while (currentClient != NULL);
  return 0;
}

int
runClient(std::string ipOrHostname, int port)
{
  struct pkg_switch callbacks[] = {
      {0, 0, (char* )0}
  };

  char portCStr[7] = {0};
  snprintf(portCStr, 6, "%d", port);
  pkg_conn* clientPkgConn = pkg_open(ipOrHostname.c_str(), portCStr, ENET_PROTO, NULL, NULL, NULL, NULL);

  PkgClient client;



  return 0;
}


/**
 * callback when a HELO message packet is received.
 *
 * We should not encounter this packet specifically since we listened
 * for it before beginning processing of packets as part of a simple
 * handshake setup.
 */
void
server_helo(struct pkg_conn* connection, char* buf)
{
    connection=connection; /* quell */
    bu_log("Unexpected HELO encountered\n");
    free(buf);
}


/**
 * callback when a DATA message packet is received
 */
void
server_data(struct pkg_conn* connection, char* buf)
{
    connection=connection; /* quell */
    bu_log("Received file data\n");
    free(buf);
}


/**
 * callback when a CIAO message packet is received
 */
void
server_ciao(struct pkg_conn* connection, char* buf)
{
    connection=connection; /* quell */
    bu_log("CIAO encountered\n");
    free(buf);
}

/**
 * Prints the 'usage' statement to the console along with an optional message
 */
void
printUsage(std::string customMsg)
{

  if (customMsg.length() > 0) {
    std::cout << customMsg << std::endl;
  }

  std::cout << "Usage for Client: pkgcppTest client ipAddress port." << std::endl;
  std::cout << "Usage for Server: pkgcppTest server port." << std::endl;
  return;
}



// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
