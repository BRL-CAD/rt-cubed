///////////////////////////////////////////////////////////
//  Portal.h
//  Implementation of the Class Portal
//  Created on:      06-Aug-2008 7:50:30 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_76E3E888_D74B_4ddf_916D_37E9645E5C0A__INCLUDED_)
#define EA_76E3E888_D74B_4ddf_916D_37E9645E5C0A__INCLUDED_

#include "PortalManager.h"
#include "MessagingSystem.h"
#include "StdMsg.h"
#include "SNRoot.h"

class Portal : public SNRoot
{

public:
	Portal();
	virtual ~Portal();

	Portal(String Name, PortalManager pm, SocketChannel sockChan);
	Portal(String Name, PortalManager pm, SocketChannel sockChan, MessagingSystem ms);
	String getRemoteHostName();
	SocketChannel getSockChan();
	void Send(StdMsg sm);
	void SendToMS(StdMsg sm);
	void SendToRemHost(StdMsg sm);

private:
	PortalManager PM;
	String RemoteHostName;
	SocketChannel sockChan;

	void finishDisconnect();
	void PortalSetRemoteHostName(StdMsg sm);
	void SendHostInfo();

};
#endif // !defined(EA_76E3E888_D74B_4ddf_916D_37E9645E5C0A__INCLUDED_)
