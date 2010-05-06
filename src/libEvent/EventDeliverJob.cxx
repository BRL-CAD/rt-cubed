/*             E V E N T D E L I V E R J O B . C X X
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
/** @file EventDeliverJob.cxx
 *
 * Brief description
 *
 */

#include "EventDeliverJob.h"

EventDeliverJob::EventDeliverJob(EventSubscriber* sub, Event* e) :
    _sub(sub), _e(e)
{
}

EventDeliverJob::~EventDeliverJob()
{
}

JobResult EventDeliverJob::_doJob()
{
    this->_sub->handleEvent(this->_e);
}

EventSubscriber* EventDeliverJob::getEventSubscriber()
{
    return this->_sub;
}

Event* EventDeliverJob::getEvent()
{
    return this->_e;
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
