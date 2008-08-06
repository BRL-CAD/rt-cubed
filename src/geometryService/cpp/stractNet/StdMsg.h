///////////////////////////////////////////////////////////
//  StdMsg.h
//  Implementation of the Class StdMsg
//  Created on:      06-Aug-2008 7:50:58 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_C4982F33_F72C_402c_A107_0FDEB933FC89__INCLUDED_)
#define EA_C4982F33_F72C_402c_A107_0FDEB933FC89__INCLUDED_

#include "StringFrag.java"
#include "MsgStop.java"
#include "NetID.h"
#include "IntegerFrag.java"
#include "WayPoint.h"
#include "SNRoot.h"

class StdMsg : public SNRoot
{

public:
	StdMsg();
	virtual ~StdMsg();

	StdMsg(StdMsg sm);
	StdMsg(int msgType);
	StdMsg(int msgType, String to);
	StdMsg(byte[] inData);
	StdMsg(DataInputStream in);
	void AddElement(MsgFrag<?> element);
	String ElementsToString();
	MsgFrag<?> GetElement(int index);
	ArrayList<MsgFrag<?>> GetElements();
	String getFromHost();
	StringFrag getFromHostFrag();
	MsgStop getLocalFrom();
	NetID getMsgID();
	int getMsgType();
	String getToHost();
	StringFrag getToHostFrag();
	ArrayList<WayPoint> getWayPoints();
	boolean HasElement(MsgFrag<?> element);
	int IndexOfElement(MsgFrag<?> element);
	boolean RemoveElement(MsgFrag<?> element);
	byte Serialize();
	void setFromHost(String fromHost);
	void setFromHostFrag(StringFrag fromHostFrag);
	void setLocalFrom(MsgStop localFrom);
	void setMsgID(NetID msgID);
	void setMsgType(int msgType);
	void setToHost(String toHost);
	void setToHostFrag(StringFrag toHostFrag);
	void StampWayPoint(WayPoint wp);
	void StampWayPoint(String Host);
	String toString();
	String WaypointsToString();

private:
	ArrayList<MsgFrag<?>> elements;
	StringFrag fromHost;
	MsgStop LocalFrom;
	/**
	 * Header Fields
	 */
	NetID MsgID;
	IntegerFrag MsgType;
	StringFrag toHost;

	void DeserializeElements(DataInputStream in) throw IOException;
	void DeserializeHeader(DataInputStream in) throw IOException;
	boolean Serialize(DataOutputStream out) throw IOException;
	void SerializeElements(DataOutputStream out) throw IOException;
	void SerializeHeader(DataOutputStream out) throw IOException;

};
#endif // !defined(EA_C4982F33_F72C_402c_A107_0FDEB933FC89__INCLUDED_)
