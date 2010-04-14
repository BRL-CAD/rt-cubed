/*                        N E T M S G F A C T O R Y. H
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
/** @file NetMsg.h
 *
 * Brief description
 *
 */

#ifndef __NETMSGFACTORY_H__
#define __NETMSGFACTORY_H__

#include "utility/Logger.h"

#include "GS/GSCommon.h"
#include "libNetwork/NetMsg.h"

#include <QByteArray>
#include <QQueue>
#include <QBuffer>
#include <QMutex>

class NetMsgFactory
{

public:

	NetMsgFactory();
	virtual ~NetMsgFactory();

	bool addData(QByteArray& data);
	bool hasMsgsAvailable();
	NetMsg* getNextMsg();
	NetMsg* peekNextMsg();
	void attemptToMakeMsgs();

	bool attemptToMakeMsg();
	void printBufferStatus(bool extended);

	quint32 getInboxSize();

private:

	QMutex* lock;

	QQueue<NetMsg*>* inbox;

	QBuffer* intBuffer;
	quint64 limit;


	void compactBuffer();
	static NetMsg* buildMsgByType(quint32 type, QDataStream* qds);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
