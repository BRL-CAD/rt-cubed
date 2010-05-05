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

class EventManager
{
public:
    virtual ~EventManager();
    static EventManager* getInstance();
    void submitEvent(Event* e);

private:
    static EventManager* pInstance;
    EventManager();

    Logger* log;

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
