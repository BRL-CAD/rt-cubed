/*                E V E N T P U B L I S H E R . H
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
/** @file EventPublisher.h
 *
 * Brief description
 *
 */

#ifndef __EVENTPUBLISHER_H__
#define __EVENTPUBLISHER_H__

#include "Event.h"
#include "EventManager.h"
#include <QString>

class EventPublisher
{
    void generateEvent(quint32 type, QString message = "")
    {
	Event* e = new Event(this, type, message);
	EventManager::getInstance()->submitEvent(e);
    }

};

#endif /* __EVENTPUBLISHER_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
