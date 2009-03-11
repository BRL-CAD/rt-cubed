/*             C O M M U N I C A T I O N S M A N A G E R . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
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

/** @file CommunicationsManager.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_COMMUNICATIONSMANAGER_H_)
#define _COMMUNICATIONSMANAGER_H_

#include <iostream>
#include <list>
#include <map>

#include "GeometryService/AbstractPortal.h"
#include "GeometryService/netMsg/NetMsg.h"

    /**
     * CommMan performs the netMsg <-> Job conversion
     */
    class CommunicationsManager
    {

    public:
      CommunicationsManager();
      virtual ~CommunicationsManager();

      void startListening(unsigned int port);

    private:
      std::list<NetMsg> inbox;
      std::list<NetMsg> outbox;
      /**
       * Maps hostnames to AbstractPortals
       *
       * This MAY not be necessary if all outgoing Traffic is handled by the individual
       * Session Objects
       */
      std::map<std::string, AbstractPortal> portals;
    };

#endif // !defined(_COMMUNICATIONSMANAGER_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
