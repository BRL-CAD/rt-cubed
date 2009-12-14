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
#include <vector>
#include <iomanip>


static const int DEFAULT_PORT = 7777;



/**
 * wrapper server class for staring up an object that instantiates and
 * represents a geometry service instance.  this should simply stub
 * into GS API calls or exec a GS process.
 */
class GeometryServer
{
private:
    int port_;

public:
    GeometryServer(int port = DEFAULT_PORT)
    {
	if (port > 0)
	    start(port);
    }
    ~GeometryServer()
    {
    }
    bool stillRunning() const
    {
	return false;
    }
    void start(int port = DEFAULT_PORT)
    {
	port_ = port;
    }
    void stop() const
    {
    }
};


/**
 * wrapper client class for staring up an object that can connect to
 * and communicate with a geometry server.  this should simply stub
 * into GS API calls or direct raw network protocol.
 */
class GeometryClient
{
private:
    bool exists(std::string object) const
    {
	if (object.size() == 0)
	    return false;

	// ask server if object exists

	return false;
    }
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
    bool connected() const
    {
	return false;
    }
    std::vector<std::string> getDirectory() const
    {
	std::vector<std::string> v;
	return v;
    }
    std::string getObject(const std::string object) const
    {
	std::string encoding = "";

	// get encoding from server

	return encoding;
    }
    bool putObject(const std::string encoding) const
    {
	if (encoding.size() == 0)
	    return false;

	// write object encoding to server

	return false;
    }
    bool addObject(const std::string object) const
    {
	if (exists(object))
	    return false;

	// encode object for put
	std::string encoding = object;

	return putObject(encoding);
    }
    bool updateObject(const std::string object) const
    {
	if (!exists(object))
	    return false;

	std::string encoding = getObject(object);
	if (encoding.size() == 0)
	    return false;

	// modify the encoding

	return putObject(object);
    }
    bool deleteObject(const std::string object) const
    {
	if (!exists(object))
	    return false;

	// remove it, return true

	return false;
    }
    bool getAttribute(const std::string object, const std::string name, std::string &value) const
    {
	if (!exists(object))
	    return false;

	// see if object has a name attribute, set value, return true
	
	return false;
    }
    bool setAttribute(const std::string object, const std::string name, std::string value) const
    {
	if (!exists(object))
	    return false;

	// set name=value on object, return true

	return false;
    }

};


/*******************************************/
/* basic scaffolding for reporting results */
/*******************************************/

/* used for keeping track of failures */
int failures = 0;


/* assert that a specific test condition is true */
#define GAS(cond, m) \
    if (cond) { \
	std::string msg = "      [ SUCCESS ] "; \
	msg += m; \
	Report(msg); \
    } else { \
	std::string msg = "      [ FAILURE ] "; \
	msg += m; \
	Report(msg); \
	failures++; \
    }


/* helper function to report each section while keeping count */
static void
Report(const std::string msg, bool showTitle = false)
{
    static int steps = 0;
    if (showTitle)
	std::cout << std::setw(2) << std::setfill(' ') << steps++ << ": ";
    std::cout << msg << std::endl;
}


/* basic end-of-section sanity testing with summary reporting */
#define RESULT() \
    GAS(gs != NULL && gs->stillRunning(), "Server is still running"); \
    if (failures == 0) { \
	std::string msg = "OK :)"; \
	Report(msg, true); \
	std::cout << std::endl; \
    } else { \
	std::string msg = "NO !!"; \
	Report(msg, true);   \
	std::cout << std::endl; \
    } \
    failures = 0;

/* basic beginning of section marker */
#define REQUIREMENT(m) \
    std::cout << std::setw(74) << std::setfill('=') << std::string(" ") + m + std::string(" ") << std::setw(4) << "=" << std::endl;


/**********************************************************/
/* convenience wrappers to simplify the repetive patterns */
/**********************************************************/

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


/************/
/* THE BOSS */
/************/

int
main(int ac, char *av[])
{
    std::vector<std::string> gcdir, gc2dir, gc3dir;

    /* don't need no params just yet */
    if (ac > 1) {
	for (int i = 1; i < ac; i++) {
	    std::cerr << "Unexpected test harness parameter: [" << av[i] << "]" << std::endl;
	}
	exit(1);
    }

    REQUIREMENT("Initialization of server and client");

    GeometryServer *gs = new GeometryServer();
    GAS(gs != NULL, "Starting up a geometry server");

    GeometryClient *gc = new GeometryClient();
    GAS(gc != NULL, "Starting up a geometry client");

    RESULT();


    /*****************************************/
    /* MAKE SURE THE SERVER CAN BE RESTARTED */
    /*****************************************/

    REQUIREMENT("Server restarts");

    gs->stop();
    GAS(!gs->stillRunning(), "Server shutting down");
    gc->connect("localhost", DEFAULT_PORT);
    GAS(!gc->connected(), "Client prevented from connected");
    gs->start();

    RESULT();


    /**********************************************/
    /* MAKE SURE A CLIENT CAN CONNECT TO A SERVER */
    /**********************************************/

    REQUIREMENT("One client connecting (no action)");

    Connect(gc);
    Disconnect(gc);

    RESULT();


    /*************************************************/
    /* MAKE SURE TWO CLIENTS CAN CONNECT TO A SERVER */
    /*************************************************/

    REQUIREMENT("Two clients simultaneously connecting (no action)");

    GeometryClient *gc2 = new GeometryClient();
    GAS(gc2 != NULL, "Starting up a second geometry client");

    Connect(gc, gc2);
    Disconnect(gc, gc2);

    RESULT();


    /*********************************/
    /* MAKE SURE ONE CLIENT CAN READ */
    /*********************************/

    REQUIREMENT("Client reading from server");

    Connect(gc);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    Disconnect(gc);

    RESULT();


    /*******************************************/
    /* MAKE SURE ONE CLIENT CAN READ AND WRITE */
    /*******************************************/

    REQUIREMENT("Client reading and writing objects");

    Connect(gc);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    GAS(gc->addObject("object_1"), "Client adding object");
    Disconnect(gc);

    RESULT();


    /**********************************/
    /* MAKE SURE TWO CLIENTS CAN READ */
    /**********************************/

    REQUIREMENT("Two clients reading");

    Connect(gc, gc2);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    gc2dir = gc2->getDirectory();
    GAS(gc2dir.size() != 0, "Second client getting a directory");
    Disconnect(gc, gc2);

    RESULT();


    /****************************************************/
    /* MAKE SURE ONE CLIENT CAN WRITE, ANOTHER CAN READ */
    /****************************************************/

    REQUIREMENT("One client writing, one client reading");

    Connect(gc, gc2);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    GAS(gc->addObject("object_2"), "Client adding object2");
    gc2dir = gc2->getDirectory();
    GAS(gc2dir.size() != 0, "Second client getting a directory");
    GAS(gcdir.size() != gc2dir.size(), "Comparing two directory sizes for not equal"); // should compare contents
    gcdir = gc->getDirectory();
    GAS(gcdir.size() == gc2dir.size(), "Comparing two directory sizes for equal"); // should compare contents

    GAS(gc2->getObject("object_2").size() != 0, "Second client verifying object_2 exists");
    GAS(gc->addObject("object_3"), "Client adding object_3");
    GAS(!gc2->addObject("object_2"), "Second client prevented from adding object_2");
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    gc2dir = gc2->getDirectory();
    GAS(gc2dir.size() != 0, "Second client getting a directory");
    GAS(gcdir.size() == gc2dir.size(), "Comparing two directory sizes for equal"); // should compare contents
    Disconnect(gc, gc2);

    RESULT();


    /********************************************************/
    /* MAKE SURE ONE CLIENT CAN WRITE, ANOTHER TWO CAN READ */
    /********************************************************/

    REQUIREMENT("One client writing, two clients reading");

    GeometryClient *gc3 = new GeometryClient();
    GAS(gc3 != NULL, "Starting up a third geometry client");

    Connect(gc, gc2, gc3);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    gc2dir = gc2->getDirectory();
    GAS(gc2dir.size() != 0, "Second client getting a directory");
    GAS(gc->addObject("object_4"), "Client adding object_4");
    std::string obj4 = gc2->getObject("object_4");
    GAS(obj4.size() != 0, "Client one verifying object_4 created");
    gc3dir = gc3->getDirectory();
    GAS(gc3dir.size() != 0, "Third client getting a directory");
    std::string obj4_1 = gc2->getObject("object_4");
    GAS(obj4_1.size() != 0, "Client two reading object_4");
    GAS(gc2->updateObject("object_4"), "Client two attempting to modify object_4");
    std::string obj4_2 = gc2->getObject("object_4");
    GAS(obj4_2.size() != 0, "Client two re-reading object_4");
    GAS(obj4.size() > 0 && obj4_1.size() > 0 && obj4 != obj4_1, "Comparing second object_4 to original for not equal");
    GAS(obj4.size() > 0 && obj4_2.size() > 0 && obj4 != obj4_2, "Comparing third object_4 to original for not equal");
    GAS(obj4_1.size() > 0 && obj4_2.size() > 0 && obj4_1 == obj4_2, "Comparing second object_4 to third for equal");
    GAS(gc3->getObject("object_4").size() != 0, "Client three reading object_4");
    GAS(gc3->deleteObject("object_4"), "Client three deleting object_4");
    GAS(gc3->getObject("object_4").size() == 0, "Client three verifying object_4 deleted");
    GAS(gc2->getObject("object_4").size() == 0, "Client two verifying object_4 deleted");
    GAS(gc->getObject("object_4").size() == 0, "Client one verifying object_4 deleted");
    Disconnect(gc, gc2, gc3);

    RESULT();


    /*****************************/
    /* CAN READ/WRITE ATTRIBUTES */
    /*****************************/

    REQUIREMENT("Client reading and writing attributes");

    Connect(gc);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    if (gcdir.size() > 0) {
	std::string attr;
	gc->getAttribute(gcdir[0], "foo", attr);
	GAS(attr.size() == 0, "Client ensuring attribute does not already exist");
	GAS(gc->setAttribute(gcdir[0], "foo", "bar"), "Client setting attribute");
	attr.clear();
	gc->getAttribute(gcdir[0], "foo", attr);
	GAS(attr.size() == 0, "Client ensuring attribute now exists");
    } else {
	GAS(false, "Unable to test attributes");
    }
    Disconnect(gc);

    RESULT();


    /*****************************************/
    /* CAN GET .g REPRESENTATION OF GEOMETRY */
    /*****************************************/

    REQUIREMENT("Retrievable .g representation for client-side ray tracing");

    Connect(gc);
    GAS(gc->addObject("object_5"), "Client adding object5");
    // gc->getRepresentation();
    // gc->updateObject();
    // gc->getRepresentation();
    // GAS different representations
    // write(inmem);
    // rt_dirbuild();
    // rt_prep();
    // rt_shootray();
    Disconnect(gc);

    RESULT();


    /***************************************/
    /* CAN READ A WIREFRAME REPRESENTATION */
    /***************************************/

    REQUIREMENT("Client reading wireframe representation");

    Connect(gc);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    // gc->getRepresentation();
    // gc->updateObject();
    // gc->getRepresentation();
    // GAS different representations
    Disconnect(gc);

    RESULT();


    /*******************************/
    /* CAN GET EVENT NOTIFICATIONS */
    /*******************************/

    REQUIREMENT("Client event notifications");

    Connect(gc, gc2);
    // gc->subscribeEvent();
    GAS(gc2->addObject("object_6"), "Client adding object6");
    // gc2->updateObject();
    // gc2->setAttribute();
    // gc->eventsReceived();
    // gc->unsubscribeEvent();
    GAS(gc2->addObject("object_7"), "Client adding object7");
    // gc2->updateObject();
    // gc2->setAttribute();
    // gc->eventsReceived();
    Disconnect(gc, gc2);

    RESULT();


    /*********************************/
    /* CAN PERSIST GEOMETRY VERSIONS */
    /*********************************/

    REQUIREMENT("Multiple versions of geometry are persisted and retrievable");

    Connect(gc, gc2);
    GAS(gc->addObject("object_8"), "Client adding object8");
    // gc2->getObject();
    // gc->updateObject();
    // gc2->updateObject();
    // gc2->getObject();
    Disconnect(gc, gc2);

    RESULT();


    /******************************/
    /* CAN SHOOT RAYS AT GEOMETRY */
    /******************************/

    REQUIREMENT("Server-side ray tracing");

    Connect(gc);
    GAS(gc->addObject("object_9"), "Client adding object9");
    // gc->subscribeEvent();
    // gc->shootRay();
    // gc->eventsReceived();
    Disconnect(gc);

    RESULT();


    /***************************************/
    /* CAN READ A POLYGONAL REPRESENTATION */
    /***************************************/

    REQUIREMENT("Client retrieving polygonal representation");

    Connect(gc);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    // gc->getRepresentation();
    // gc->updateObject();
    // gc->getRepresentation();
    // GAS different representations
    Disconnect(gc);

    RESULT();


    /*****************************************/
    /* CAN READ A POINT-CLOUD REPRESENTATION */
    /*****************************************/

    REQUIREMENT("Client retrieving point-cloud representation");

    Connect(gc);
    gcdir = gc->getDirectory();
    GAS(gcdir.size() != 0, "Client getting a directory");
    // gc->getRepresentation();
    // gc->subscribeEvent();
    // gc->evaluateRepresentation();
    // gc->eventsReceived();
    Disconnect(gc);

    RESULT();


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
