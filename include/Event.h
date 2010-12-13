/*                         E V E N T . H
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
/** @file Event.h
 *
 * Brief description
 *
 */

#ifndef __EVENT_H__
#define __EVENT_H__

#include <QtCore/QString>

class EventPublisher;

class Event
{
public:
	Event(EventPublisher* pub, quint32 eventType);
	Event(EventPublisher* pub, quint32 eventType, QString message);
	virtual ~Event();

	EventPublisher* getPublisher() const;
	quint32 getEventType() const;
	QString getMessage() const;

private:
	EventPublisher* _pub;
	quint32 _eventType;
	QString _message;

	/* Disable copy cstr and =operator */
	Event(Event const&){};
	Event& operator=(Event const&){};
};

#endif /* __EVENT_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
