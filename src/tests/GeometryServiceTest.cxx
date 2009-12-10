/*         G E O M E T R Y S E R V I C E T E S T . C X X
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file GeometryServiceTest.cxx
 *
 * This is a high-level integration test harness for exploring the
 * capabilities of the Geometry Service base functionality.
 *
 */

#include <stdlib.h>
#include <string>
#include <iostream>


static const int DEFAULT_PORT = 7777;


class GeometryServer
{
private:
    int port_;

public:
    GeometryServer(int port = DEFAULT_PORT) :
	port_(port)
    {
    }
    ~GeometryServer()
    {
    }
};


class GeometryClient
{
private:
public:
    GeometryClient()
    {
    }
    ~GeometryClient()
    {
    }

    void connect(const char *host = "localhost", int port = DEFAULT_PORT) const
    {
	if (!host || port < 0) {
	    std::cerr << "Unexpected test harness state" << std::endl;
	    exit(1);
	}
    }
    void disconnect() const
    {
    }
    bool connected(void) const
    {
	return false;
    }
};


int failures = 0; /* used for tracking failures */
#define REQUIREMENT(m) if (failures == 0) { std::string msg = "[ OK ] "; msg += m; Report(msg, true); std::cout << std::endl; } else { std::string msg = "[FAIL] "; msg += m; Report(msg, true); std::cout << std::endl; } failures = 0;
#define GAS(cond, m) if (cond) { std::string msg = "    [ SUCCESS ] "; msg += m; Report(msg); } else { std::string msg = "    [ FAILURE ] "; msg += m; Report(msg); failures++; }
static void
Report(const std::string msg, bool showTitle = false)
{
    static int steps = 0;
    if (showTitle)
	std::cout << steps++ << ": ";
    std::cout << msg << std::endl;
}


static void
Connect(GeometryClient *gc, GeometryClient *gc2 = NULL, GeometryClient *gc3 = NULL)
{
    if (gc && !gc2 && !gc3) {
	gc->connect("localhost", DEFAULT_PORT);
	GAS(gc->connected(), "Connecting client");
    } else if (gc && gc2 && !gc3) {
	gc->connect("localhost", DEFAULT_PORT);
	gc2->connect("localhost", DEFAULT_PORT);
	GAS(gc->connected() && gc2->connected(), "Connecting two clients");
    } else if (gc && gc2 && gc3) {
	gc->connect("localhost", DEFAULT_PORT);
	gc2->connect("localhost", DEFAULT_PORT);
	gc3->connect("localhost", DEFAULT_PORT);
	GAS(gc->connected() && gc2->connected() && gc3->connected(), "Connecting three clients");
    } else {
	std::cerr << "Unexpected test harness state" << std::endl;
	exit(1);
    }
}
static void
Disconnect(GeometryClient *gc, GeometryClient *gc2 = NULL, GeometryClient *gc3 = NULL)
{
    if (gc && !gc2 && !gc3) {
	gc->disconnect();
	GAS(!gc->connected(), "Disconnecting client");
    } else if (gc && gc2 && !gc3) {
	gc->disconnect();
	gc2->disconnect();
	GAS(!gc->connected() && !gc2->connected(), "Disconnecting two clients");
    } else if (gc && gc2 && gc3) {
	gc->disconnect();
	gc2->disconnect();
	gc3->disconnect();
	GAS(!gc->connected() || !gc2->connected() || !gc3->connected(), "Disconnecting three clients");
    } else {
	std::cerr << "Unexpected test harness state" << std::endl;
	exit(1);
    }
}


int
main(int ac, char *av[])
{
    /* don't need no params just yet */
    if (ac > 1) {
	for (int i = 1; i < ac; i++) {
	    std::cerr << "Unexpected test harness parameter: [" << av[i] << "]" << std::endl;
	}
	exit(1);
    }

    GeometryServer *gs = new GeometryServer();
    GAS(gs != NULL, "Starting up a geometry server");

    GeometryClient *gc = new GeometryClient();
    GAS(gc != NULL, "Starting up a geometry client");

    REQUIREMENT("Initialization of server and client");


    /**********************************************/
    /* MAKE SURE A CLIENT CAN CONNECT TO A SERVER */
    /**********************************************/

    Connect(gc);
    Disconnect(gc);

    REQUIREMENT("One client connecting (no action)");


    /*************************************************/
    /* MAKE SURE TWO CLIENTS CAN CONNECT TO A SERVER */
    /*************************************************/

    GeometryClient *gc2 = new GeometryClient();
    GAS(gc2 != NULL, "Starting up a second geometry client");

    Connect(gc, gc2);
    Disconnect(gc, gc2);

    REQUIREMENT("Two client simultaneously connecting (no action)");


    /*********************************/
    /* MAKE SURE ONE CLIENT CAN READ */
    /*********************************/

    Connect(gc);
    // gc->getDirectory();
    Disconnect(gc);

    REQUIREMENT("One client reading");


    /*******************************************/
    /* MAKE SURE ONE CLIENT CAN READ AND WRITE */
    /*******************************************/

    Connect(gc);
    // gc->getDirectory();
    // gc->addObject();
    Disconnect(gc);

    REQUIREMENT("One client reading from and writing");


    /**********************************/
    /* MAKE SURE TWO CLIENTS CAN READ */
    /**********************************/

    Connect(gc, gc2);
    // gc->getDirectory();
    // gc2->getDirectory();
    Disconnect(gc, gc2);

    REQUIREMENT("Two clients reading");


    /****************************************************/
    /* MAKE SURE ONE CLIENT CAN WRITE, ANOTHER CAN READ */
    /****************************************************/

    Connect(gc, gc2);
    // gc->getDirectory();
    // gc->addObject();
    // gc2->getDirectory();
    // gc2->getObject();
    // gc2->addObject(); /* should fail */
    Disconnect(gc, gc2);

    REQUIREMENT("One client writing, one client reading");


    /********************************************************/
    /* MAKE SURE ONE CLIENT CAN WRITE, ANOTHER TWO CAN READ */
    /********************************************************/

    GeometryClient *gc3 = new GeometryClient();
    GAS(gc3 != NULL, "Starting up a third geometry client");

    Connect(gc, gc2, gc3);
    // gc->getDirectory();
    // gc2->getDirectory();
    // gc->addObject();
    // gc3->getDirectory();
    // gc2->getObject();
    // gc2->updateObject();
    // gc2->getObject();
    // gc3->getObject();
    // gc3->deleteObject();
    // gc3->getObject();
    Disconnect(gc, gc2, gc3);

    REQUIREMENT("Three clients connecting, only one writing");


    /*****************************/
    /* CAN READ/WRITE ATTRIBUTES */
    /*****************************/

    Connect(gc);
    // gc->getDirectory();
    // gc->getAttribute();
    // gc->setAttribute();
    // gc->getAttribute();
    Disconnect(gc);

    REQUIREMENT("One client reading from and writing attributes");


    /***************************************/
    /* CAN READ A WIREFRAME REPRESENTATION */
    /***************************************/

    Connect(gc);
    // gc->getDirectory();
    // gc->getRepresentation();
    // gc->setRepresentation();
    // gc->getRepresentation();
    Disconnect(gc);

    REQUIREMENT("One client reading from and writing wireframe representation");


    /*******************************/
    /* CAN GET EVENT NOTIFICATIONS */
    /*******************************/

    Connect(gc, gc2);
    // gc->subscribeEvent();
    // gc2->addObject();
    // gc2->updateObject();
    // gc2->setAttribute();
    // gc->eventsReceived();
    // gc->unsubscribeEvent();
    // gc2->addObject();
    // gc2->updateObject();
    // gc2->setAttribute();
    // gc->eventsReceived();
    Disconnect(gc);

    REQUIREMENT("Client event notification");


    /* cleanup */

    delete gc3;
    delete gc2;
    delete gc;
    delete gs;

    return 0;
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
