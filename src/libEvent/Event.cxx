/*                       E V E N T . C X X
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
/** @file Event.cxx
 *
 * Brief description
 *
 */

#include "Event.h"

Event::Event(IEventPublisher* pub, quint32 eventType) :
    _pub(pub), _eventType(eventType), _message("")
{
}

Event::Event(IEventPublisher* pub, quint32 eventType, QString message) :
    _pub(pub), _eventType(eventType), _message(message)
{
}

Event::~Event()
{
}

IEventPublisher* Event::getPublisher() const
{
    return this->_pub;
}
quint32 Event::getEventType() const
{
    return this->_eventType;
}
QString Event::getMessage() const
{
    return this->_message;
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
