/*                  E V E N T M A N A G E R . H
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
/** @file EventManager.h
 *
 * Brief description
 *
 */

#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#define ALL_TYPES	0
#define ALL_PUBLISHERS	0

#include "Event.h"
#include "utility.h"
#include "job.h"

class EventSubscriber;

class EventManager
{
public:
    virtual ~EventManager();
    static EventManager* getInstance();
    void submitEvent(Event* e);

    void subscribe(EventSubscriber* sub, quint32 eventType, EventPublisher* pub);

private:

    //Private class for handling event submission
    class SubmitEventJob : public AbstractJob {
    public:
	SubmitEventJob(Event* e):e(e){};
	virtual ~SubmitEventJob();
    private:
	JobResult _doJob(){EventManager::getInstance()->processEvent(e);};
	Event* e;
    };

    //private class for grouping subscription data together
    class EventSubscription
    {
    public:
        EventSubscription(EventSubscriber* sub, quint32 eventType = ALL_TYPES, EventPublisher* pub = ALL_PUBLISHERS):_sub(sub), _eventType(eventType), _pub(pub){};
        virtual ~EventSubscription();

        EventPublisher* getPublisher(){return this->_pub;};
        quint32 getEventType(){return this->_eventType;};
        EventSubscriber* getEventSubscriber(){return this->_sub;};

    private:
        EventPublisher* _pub;
        quint32 _eventType;
        EventSubscriber* _sub;
    };


    static EventManager* pInstance;
    EventManager();
    void processEvent(Event* e);
    QList<EventSubscriber*>* buildSubscriberList(Event* e);

    Logger* log;

    QList<EventSubscription*>* subscriptions;

};

#endif /* __EVENTMANAGER_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
