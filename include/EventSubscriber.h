/*              I E V E N T S U B S C R I B E R . H
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
/** @file EventSubscriber.h
 *
 * Brief description
 *
 */

#ifndef __EVENTSUBSCRIBER_H__
#define __EVENTSUBSCRIBER_H__

#include "Event.h"
#include "EventManager.h"
#include <Qt>

class EventPublisher;

class EventSubscriber
{
public:
    virtual void handleEvent(Event* e) = 0;

protected:
    void subscribeMeToAllEventsOfType(quint32 eventType);
    void subscribeMeToAllEventsByPublisher(EventPublisher* pub);
    void subscribeMeToEventOfTypeByPublisher(quint32 eventType, EventPublisher* pub);

};

#endif /* __EVENTSUBSCRIBER_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
