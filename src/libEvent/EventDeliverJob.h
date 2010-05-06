/*               E V E N T D E L I V E R J O B . H
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
/** @file EventDeliverJob.h
 *
 * Brief description
 *
 */

#ifndef __EVENTDELIVERJOB_H__
#define __EVENTDELIVERJOB_H__

#include "AbstractJob.h"
#include "EventSubscriber.h"
#include "Event.h"

class EventDeliverJob: public AbstractJob
{
public:
    EventDeliverJob(EventSubscriber* sub, Event* e);
    virtual ~EventDeliverJob();

    EventSubscriber* getEventSubscriber();
    Event* getEvent();

protected:
    JobResult _doJob();

private:
    EventSubscriber* _sub;
    Event* _e;

};

#endif /* __EVENTDELIVERJOB_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
