/*              B A S I C E V E N T T E S T . C X X
 * BRLCAD
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
/** @file BasicEventTest.cxx
 *
 * Brief description
 *
 */

#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "libutility.h"
#include "libjob.h"
#include "commonDefines.h"

#include <Qt>

class TestSubscriber: public EventSubscriber
{
public:
    TestSubscriber(QString name) :
	_name(name)
    {
    }
    ;

    void handleEvent(Event* e)
    {
	Logger::getInstance()->logINFO(_name, "Recv Event of type: "
		+ QString::number(e->getEventType()) + " with msg: "
		+ e->getMessage());
    }
    ;

private:
    QString _name;
};

class TestPublisher: public EventPublisher
{
public:
    TestPublisher(QString name) :
	_name(name)
    {
    }
    ;

    void generateEvent(quint32 type, QString message = "")
    {
	Logger::getInstance()->logINFO(_name, "Generating Event of type: "
		+ QString::number(type) + " with msg: " + message);
	EventPublisher::generateEvent(type, message);
    }

private:
    QString _name;
};

int main(int argc, char* argv[])
{
    JobManager* jMan = JobManager::getInstance();
    EventManager* eMan = EventManager::getInstance();
    Logger* log = Logger::getInstance();

    log->logBANNER("BasicEventTest", "Basic Event Test");

    TestSubscriber tSub01("Sub01");
    TestSubscriber tSub02("Sub02");
    TestSubscriber tSub03("Sub03");
    TestPublisher tPubA("Pub-A");
    TestPublisher tPubB("Pub-B");
    TestPublisher tPubC("Pub-C");

    log->logBANNER("BasicEventTest", "All Publishers, Subscriber 01(Event #100)");
    eMan->subscribe(&tSub01, 100, ALL_EVENT_PUBLISHERS);

    tPubA.generateEvent(99, "Msg a99");
    tPubA.generateEvent(100, "Msg a100");
    tPubA.generateEvent(101, "Msg a101");

    ThreadUtils::sleep(1);

    log->logBANNER("BasicEventTest", "All Publishers, Subscriber 02(Event #100)");
    eMan->subscribe(&tSub02, 100, ALL_EVENT_PUBLISHERS);

    tPubA.generateEvent(99, "Msg a99");
    tPubA.generateEvent(100, "Msg a100");
    tPubA.generateEvent(101, "Msg a101");

    ThreadUtils::sleep(1);

    log->logBANNER("BasicEventTest", "Publisher A, Subscriber 02(Event# 101)");
    eMan->subscribe(&tSub02, 101, &tPubA);
    tPubA.generateEvent(99, "Msg a99");
    tPubA.generateEvent(100, "Msg a100");
    tPubA.generateEvent(101, "Msg a101");

    tPubB.generateEvent(99, "Msg b99");
    tPubB.generateEvent(100, "Msg b100");
    tPubB.generateEvent(101, "Msg b101");

    ThreadUtils::sleep(1);

    log->logBANNER("BasicEventTest", "Publisher B, Subscriber 03(All Events)");
    eMan->subscribe(&tSub03, ALL_EVENT_TYPES, &tPubB);

    tPubA.generateEvent(99, "Msg a99");
    tPubA.generateEvent(100, "Msg a100");
    tPubA.generateEvent(101, "Msg a101");

    tPubB.generateEvent(99, "Msg b99");
    tPubB.generateEvent(100, "Msg b100");
    tPubB.generateEvent(101, "Msg b101");

    ThreadUtils::sleep(1);

    log->logBANNER("BasicEventTest", "DONE");

    log->logINFO("JobManager", "Job Queue len: " + QString::number(
	    jMan->getWorkQueueLen()));

    ThreadUtils::sleep(1);
    log->logINFO("JobManager", "Job Queue len: " + QString::number(
	    jMan->getWorkQueueLen()));

    return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
