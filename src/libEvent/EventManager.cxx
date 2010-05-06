/*                E V E N T M A N A G E R . C X X
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
/** @file EventManager.cxx
 *
 * Brief description
 *
 */

#include "EventManager.h"

EventManager* EventManager::pInstance = NULL;

EventManager::EventManager()
{
    this->subscriptions = new QList<EventSubscription*>();
}

EventManager::~EventManager()
{
    for (quint32 i = 0; i < subscriptions->size(); ++i) {
	EventSubscription* es = subscriptions->at(i);
	delete es;
    }
    delete subscriptions;
}

EventManager* EventManager::getInstance()
{
    if (!EventManager::pInstance) {
	pInstance = new EventManager();
    }
    return EventManager::pInstance;
}

void EventManager::submitEvent(Event* e)
{
    SubmitEventJob* j = new SubmitEventJob(e);
    JobManager::getInstance()->submitJob(j);
}

void EventManager::processEvent(Event* e)
{

}

QList<EventSubscriber*>* EventManager::buildSubscriberList(Event* e)
{

    QList<EventSubscriber*>* subscribers = new QList<EventSubscriber*> ();

    //First Check for
    for (quint32 i = 0; i < subscriptions->size(); ++i) {
	EventSubscription* es = subscriptions->at(i);



    }


}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
