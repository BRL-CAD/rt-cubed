/*                       P O N G M S G . H
 * BRL-CAD
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
/** @file PongMsg.h
 * PongMsg.h
 *
 *  Created on: Dec 20, 2010
 */

#ifndef PONGMSG_H_
#define PONGMSG_H_

#include "PingMsg.h"
#include "GenericFourBytesMsg.h"

class PongMsg: public GenericFourBytesMsg {
public:
	PongMsg(PingMsg* ping);
	virtual ~PongMsg();

	quint32 getStartTime();
};

#endif /* PONGMSG_H_ */
