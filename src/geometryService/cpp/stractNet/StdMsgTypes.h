///////////////////////////////////////////////////////////
//  StdMsgTypes.h
//  Implementation of the Class StdMsgTypes
//  Created on:      06-Aug-2008 7:51:19 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D158825C_0D19_4a98_AACD_A3F335417F82__INCLUDED_)
#define EA_D158825C_0D19_4a98_AACD_A3F335417F82__INCLUDED_

class StdMsgTypes
{

public:
	StdMsgTypes();
	virtual ~StdMsgTypes();
	/**
	 * Ensure a unique name to avoid collisions with a HostName that someone might
	 * pick.
	 */
	static String AllHosts;
	static const int mtBroadcast = 0;
	static const int mtGoodBye = 2;
	static const int mtHello = 1;
	static const int mtMSCannotAcceptConn = 3;
	static const int mtMSNotMaster = 14;
	static const int mtMyMsgTypes = 4;
	static const int mtPing = 20;
	static const int mtPong = 21;
	static const int mtPortalHostNameAlreadyInUse = 12;
	static const int mtPortalHostNameAlreadyOnNet = 13;
	static const int mtPortalHostNameNotUnique = 11;
	static const int mtPortalSetRemoteHostName = 10;

};
#endif // !defined(EA_D158825C_0D19_4a98_AACD_A3F335417F82__INCLUDED_)
