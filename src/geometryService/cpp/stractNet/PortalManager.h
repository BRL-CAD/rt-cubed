///////////////////////////////////////////////////////////
//  PortalManager.h
//  Implementation of the Class PortalManager
//  Created on:      06-Aug-2008 7:38:20 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_FBFDF021_F395_4845_8DA4_440EE305E483__INCLUDED_)
#define EA_FBFDF021_F395_4845_8DA4_440EE305E483__INCLUDED_

#include "Portal.h"
#include "MessagingSystem.h"
#include "SNRoot.h"

class PortalManager : public SNRoot
{

public:
	PortalManager();
	virtual ~PortalManager();

	PortalManager(String Name, InetAddress hostAddress, int port) throw IOException;
	PortalManager(String Name, InetAddress hostAddress, int port, MessagingSystem ms) throw IOException;
	SocketChannel ConnectTo(InetAddress host, int port);
	boolean disconnectFrom(String host) throw IOException;
	boolean disconnectFrom(Portal p) throw IOException;
	boolean disconnectFrom(InetAddress ip, int Port) throw IOException;
	boolean getRunCmd();
	boolean getRunStatus();
	Thread getThread();
	void run();
	void send(SocketChannel sockChan, byte[] data);
	void start();
	void stop();

private:
	/**
	 * The host:port combination to listen on
	 */
	InetAddress hostAddress;
	Thread myThread;
	/**
	 * A list of PendingChange instances
	 */
	List<PortalChangeRequest> pendingChanges;
	/**
	 * Maps a SocketChannel to a list of ByteBuffer instances
	 */
	Map<SocketChannel, List<ByteBuffer>> pendingData;
	int port;
	int portalCnt;
	/**
	 * Maps a SocketChannel to a Portal
	 */
	Map<SocketChannel, Portal> portals;
	/**
	 * The buffer into which we'll read data when it's available
	 */
	ByteBuffer readBuffer;
	boolean runCmd;
	boolean runStatus;
	/**
	 * The selector we'll be monitoring
	 */
	Selector selector;
	/**
	 * The channel on which we'll accept connections
	 */
	ServerSocketChannel serverChannel;

	void accept(SelectionKey key) throw IOException;
	Portal CreateNewPortal(SocketChannel sockChan);
	boolean disconnect(SelectionKey key) throw IOException;
	boolean disconnect(SocketChannel sockChan) throw IOException;
	void finishConnection(SelectionKey key) throw IOException;
	int getNewPortalNumber();
	SocketChannel initiateConnection(InetAddress host, int port) throw IOException;
	Selector initSelector() throw IOException;
	void read(SelectionKey key) throw IOException;
	void write(SelectionKey key) throw IOException;

};
#endif // !defined(EA_FBFDF021_F395_4845_8DA4_440EE305E483__INCLUDED_)
