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

#include "Event.h"
#include "utility.h"
#include "job.h"

class EventSubscriber;
class EventSubscription;

class EventManager
{
public:
    virtual ~EventManager();
    static EventManager* getInstance();
    void submitEvent(Event* e);

    void subscribe(EventSubscriber* sub, quint32 eventType,
		    EventPublisher* pub);
    void unsubscribe(EventSubscriber* sub, quint32 eventType,
	    EventPublisher* pub);

private:

    //Private class for handling event submission
    class SubmitEventJob: public AbstractJob
    {
    public:
	SubmitEventJob(Event* e) :
	    e(e){};
	virtual ~SubmitEventJob();
    private:
	JobResult _doJob()
	{
	    EventManager::getInstance()->processEvent(e);
	};
	Event* e;
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
