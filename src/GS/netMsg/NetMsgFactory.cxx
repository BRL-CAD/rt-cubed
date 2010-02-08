/*                      N E T M S G F A C T O R Y. C X X
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
/** @file NetMsgFactory.cxx
 *
 * Brief description
 *
 */

#include "GS/GSCommon.h"
#include "GS/netMsg/NetMsgFactory.h"
#include "GS/netMsg/GenericOneStringMsg.h"
#include "GS/netMsg/GenericOneByteMsg.h"
#include "GS/netMsg/GenericTwoBytesMsg.h"
#include "GS/netMsg/GenericFourBytesMsg.h"
#include "GS/netMsg/GenericMultiByteMsg.h"
#include "GS/netMsg/GeometryReqMsg.h"
#include "GS/netMsg/GeometryManifestMsg.h"
#include "GS/netMsg/GeometryChunkMsg.h"

#include <QMutexLocker>

NetMsgFactory::NetMsgFactory()
{
	this->intBuffer = new QBuffer();
	this->intBuffer->open(QIODevice::ReadWrite);
	this->limit = 0;

	this->lock = new QMutex();
	this->inbox = new QQueue<NetMsg*> ();
}

NetMsgFactory::~NetMsgFactory()
{
	//	this->intBuffer->close();
	//	delete this->intBuffer;
	//	delete this->lock ;
}

bool NetMsgFactory::addData(QByteArray& data)
{
	QMutexLocker(this->lock);

	//Copy data into internal buffer
	quint32 retVal = this->intBuffer->write(data);

	if (retVal == -1)
	{
		this->intBuffer->reset();
		return false;
	}
	else
	{
		this->limit += retVal;
		return true;
	}
}

void NetMsgFactory::attemptToMakeMsgs()
{
	quint32 failSafe = 0;
	while (this->attemptToMakeMsg())
	{
		++failSafe;
		if (failSafe > 10)
		{
			return;
		}
	}
}

bool NetMsgFactory::attemptToMakeMsg()
{
	QMutexLocker(this->lock);

	if (this->limit < 8)
	{
		//dont have enough data in the buffer
		//std::cout << "Factory failed: InitialSize < 8\n";
		return false;
	}

	quint32 bufPos = this->intBuffer->pos();

	//First test to see if we have LEN data by PEEKing
	this->intBuffer->reset();
	QByteArray qbaLen = this->intBuffer->peek(8);
	QDataStream qdsLen(qbaLen);

	quint32 len;
	qdsLen >> len;

	quint32 msgType;
	qdsLen >> msgType;

	if (this->limit < (len + 4))
	{
		//dont have enough data in the buffer
		//std::cout << "Factory failed: Size < LEN + 4 (" << (len + 4) << "\n";
		return false;
	}

	//reset
	this->intBuffer->reset();

	//Wrap up the buffer in a DataStream
	QDataStream* qds = new QDataStream(this->intBuffer);
	NetMsg* msg = this->buildMsgByType(msgType, qds);

	if (msg == NULL)
	{
		std::cout << "Factory failed: msgType lookup Failure:" << msgType
				<< "\n";
		return false;
	}
	else
	{
		this->inbox->append(msg);

		this->compactBuffer();

		return true;
	}
}
void NetMsgFactory::printBufferStatus(bool extended)
{
	std::cout << "\n";
	std::cout << "Buffer pos: " << this->intBuffer->pos() << "\n";
	std::cout << "Buffer limit: " << this->limit << "\n";
	std::cout << "Buffer size: " << this->intBuffer->size() << "\n";
	std::cout << "MsgQueue size: " << this->inbox->size() << "\n";

	if (extended)
	{
		quint64 pos = this->intBuffer->pos();
		this->intBuffer->reset();
		QByteArray tData = intBuffer->readAll();

		for (quint32 i = 0; i < this->intBuffer->size(); ++i)
		{
			std::cout << tData[i] << ", ";
		}
		this->intBuffer->seek(pos);
		std::cout << "\n";
	}
	std::cout << "\n";
}

void NetMsgFactory::compactBuffer()
{
	//Keep only the data between buffer.pos() and LIMIT;
	//if we have used ALL of the buffer up:

	//this->printBufferStatus();

	if (this->intBuffer->atEnd())
	{
		this->intBuffer->reset();
		this->limit = 0;
		return;
	}

	//if we are at LIMIT, then reset:
	if (this->intBuffer->pos() == this->limit)
	{
		this->intBuffer->reset();
		this->limit = 0;
		return;
	}

	//if we are past LIMIT, then something is terrabad wrong:
	if (this->intBuffer->pos() > this->limit)
	{
		std::cerr << "Buffer Overrun\n";
		this->intBuffer->reset();
		this->limit = 0;
		return;
	}

	//Copy the good data out
	quint64 dataLen = this->limit - this->intBuffer->pos();
	QByteArray tempData = this->intBuffer->read(dataLen);

	//Rewind & write data back in
	this->intBuffer->reset();
	this->intBuffer->write(tempData);
	this->limit = tempData.size();

	//this->printBufferStatus();


}

NetMsg* NetMsgFactory::buildMsgByType(quint32 type, QDataStream* qds)
{
	switch (type)
	{
	case FAILURE:
		return new GenericOneByteMsg(qds);
	case SUCCESS:
		return new GenericOneByteMsg(qds);
	case REMHOSTNAMESET:
		return new GenericOneStringMsg(qds);
	case DISCONNECTREQ:
		return new NetMsg(qds);
	case NEWHOSTONNET:
		return new GenericOneStringMsg(qds);
	case FULLHOSTLISTREQ:
		return new NetMsg(qds);
	case FULLHOSTLIST:
		//TODO implement MsgType!!
		return new NetMsg(qds);
	case NEWSESSIONREQ:
		return new NetMsg(qds);
	case NEWSESSION:
		return new GenericOneStringMsg(qds);
	case GEOMETRYREQ:
		return new GeometryReqMsg(qds);
	case GEOMETRYMANIFEST:
		return new GeometryManifestMsg(qds);
	case GEOMETRYCHUNK:
		return new GeometryChunkMsg(qds);
	default:
		return NULL;
	}

}

bool NetMsgFactory::hasMsgsAvailable()
{
	return (this->inbox->size() > 0);
}

NetMsg*
NetMsgFactory::getNextMsg()
{
	if (this->inbox->isEmpty())
	{
		std::cout << "Factory.getNextMsg() is returning NULL\n";
		return NULL;
	}

	NetMsg* out = this->inbox->takeFirst();

	return out;
}

quint32 NetMsgFactory::getInboxSize()
{
	return this->inbox->size();
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
