package stractNet.portals;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.CancelledKeyException;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.channels.spi.SelectorProvider;
import java.util.List;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Set;

import stractNet.messaging.MessagingSystem;
import stractNet.messaging.msgs.StdMsg;
import stractNet.messaging.msgs.StdMsgTypes;
import stractThread.STRunnable;

public class PortalManager extends stractNet.SNRoot implements STRunnable {
	private Thread myThread;
	private boolean runStatus = true;
	private boolean runCmd = true;

	// The host:port combination to listen on
	private InetAddress hostAddress;
	private int port;

	// The channel on which we'll accept connections
	private ServerSocketChannel serverChannel;

	// The selector we'll be monitoring
	private Selector selector;

	// The buffer into which we'll read data when it's available
	private ByteBuffer readBuffer = ByteBuffer.allocate(8192);

	// A list of PendingChange instances
	private List<PortalChangeRequest> pendingChanges = new LinkedList<PortalChangeRequest>();

	// Maps a SocketChannel to a list of ByteBuffer instances
	private Map<SocketChannel, List<ByteBuffer>> pendingData = new HashMap<SocketChannel, List<ByteBuffer>>();

	// Maps a SocketChannel to a Portal
	private Map<SocketChannel, Portal> portals = new HashMap<SocketChannel, Portal>();
	private int portalCnt = 0;

	public PortalManager(String Name, InetAddress hostAddress, int port)
			throws IOException {
		this(Name, hostAddress, port, null);
	}

	public PortalManager(String Name, InetAddress hostAddress, int port,
			MessagingSystem ms) throws IOException {
		super(Name);
		this.hostAddress = hostAddress;
		this.port = port;
		this.selector = this.initSelector();
		this.setLocalMS(ms);
	}

	public void run() {
		this.runStatus = true;
		this.out("Running.", 1);
		SelectionKey key = null;

		while (this.runCmd) {
			try {

				// Process any pending changes
				synchronized (this.pendingChanges) {

					Iterator<PortalChangeRequest> changes = this.pendingChanges
							.iterator();

					while (changes.hasNext()) {
						PortalChangeRequest change = (PortalChangeRequest) changes
								.next();
						switch (change.type) {
						case PortalChangeRequest.CHANGEOPS:
							// get a ref to the SelectionKey in the
							// SocketChannel in the ChangeRequest
							key = change.socket.keyFor(this.selector);

							if (key == null) {
								System.out.println(change.toString());
								if (!change.socket.isConnected()) {
									this.disconnect(change.socket);
								}
								continue;
							}

							if (!key.isValid()) {
								System.err.println("BAD KEY");
								continue;
							}

							key.interestOps(change.ops);
							break;
						case PortalChangeRequest.REGISTER:
							change.socket.register(this.selector, change.ops);
							break;
						}
					}
					this.pendingChanges.clear();
				}

				// Wait for an event one of the registered channels
				// THIS BLOCKS
				this.runStatus = false;
				this.selector.select();
				this.runStatus = true;

				// Iterate over the set of keys for which events are available
				Iterator<SelectionKey> selectedKeys = this.selector
						.selectedKeys().iterator();
				while (selectedKeys.hasNext()) {
					key = selectedKeys.next();
					selectedKeys.remove();

					if (!key.isValid()) {
						this.disconnect(key);
					}

					// Check what event is available and deal with it
					if (key.isAcceptable()) {
						this.accept(key);
					} else if (key.isReadable()) {
						this.read(key);
					} else if (key.isWritable()) {
						this.write(key);
					} else if (key.isConnectable()) {
						this.finishConnection(key);
					}
				}
			} catch (CancelledKeyException cke) {
				System.err.print(cke.getMessage());
				try {
					this.disconnect(key);
				} catch (IOException e) {
					System.exit(1);
				}
			} catch (Exception e) {
				System.err.println(key.toString());
			}
		}

		this.runStatus = false;

		Set<SocketChannel> ssc = this.portals.keySet();

		for (SocketChannel s : ssc) {
			try {
				s.close();
			} catch (IOException e) {
				this.err("SocketChannel.close() failed.", 0);
			}
		}

		this.out("Shutdown.", 1);
	}

	private void read(SelectionKey key) throws IOException {
		SocketChannel socketChannel = (SocketChannel) key.channel();

		// Clear out our read buffer so it's ready for new data
		this.readBuffer.clear();

		// Attempt to read off the channel
		int numRead;
		try {
			numRead = socketChannel.read(this.readBuffer);
		} catch (IOException e) {
			// The remote forcibly closed the connection, cancel
			// the selection key and close the channel.
			key.cancel();
			socketChannel.close();
			return;
		}

		if (numRead == -1) {
			// Remote entity shut the socket down cleanly. Do the
			// same from our end and cancel the channel.
			this.disconnect(key);
			return;
		}

		Portal p = this.portals.get(key.channel());
		if (p == null) {
			this.err("Null Portal on Lookup.", 0);
			return;
		}

		byte[] readdata = this.readBuffer.array();

		// try {
		// FIXME why are we making the Portal Manager deserialize the Msg? is
		// this effiecient?
		StdMsg gm = this.getLocalMS().generateNewMsg(readdata);
		p.SendToMS(gm);
		// } catch (Exception e) {
		// this
		// .err("Failed to properly create a StdMsg: "
		// + e.getMessage() + "Using this data:\n" + readdata, 0);
		// return;
		// }
		return;
	}

	public void send(SocketChannel sockChan, byte[] data) {
		synchronized (this.pendingChanges) {
			// Indicate we want the interest ops set changed
			this.pendingChanges.add(new PortalChangeRequest(sockChan,
					PortalChangeRequest.CHANGEOPS, SelectionKey.OP_WRITE));

			// And queue the data we want written
			synchronized (this.pendingData) {
				List<ByteBuffer> queue = this.pendingData.get(sockChan);

				// if the retrieved Queue is null, instantiate a new one.
				if (queue == null) {
					queue = new ArrayList<ByteBuffer>();
					this.pendingData.put(sockChan, queue);
				}
				queue.add(ByteBuffer.wrap(data));
			}
		}

		// Finally, wake up our selecting thread so it can make the required
		// changes
		this.selector.wakeup();
	}

	private void write(SelectionKey key) throws IOException {
		SocketChannel socketChannel = (SocketChannel) key.channel();

		synchronized (this.pendingData) {
			List<ByteBuffer> queue = this.pendingData.get(socketChannel);

			// Write until there's not more data ...
			while (!queue.isEmpty()) {
				ByteBuffer buf = (ByteBuffer) queue.get(0);
				socketChannel.write(buf);
				if (buf.remaining() > 0) {
					// ... or the socket's buffer fills up
					break;
				}
				queue.remove(0);
			}

			if (queue.isEmpty()) {
				// We wrote away all data, so we're no longer interested
				// in writing on this socket. Switch back to waiting for
				// data.
				key.interestOps(SelectionKey.OP_READ);
			}
		}
	}

	private Selector initSelector() throws IOException {
		// Create a new selector
		Selector socketSelector = SelectorProvider.provider().openSelector();

		// Create a new non-blocking server socket channel
		this.serverChannel = ServerSocketChannel.open();
		this.serverChannel.configureBlocking(false);

		// Bind the server socket to the specified address and port
		InetSocketAddress isa = new InetSocketAddress(this.hostAddress,
				this.port);
		this.serverChannel.socket().bind(isa);

		// Register the server socket channel, indicating an interest in
		// accepting new connections
		this.serverChannel.register(socketSelector, SelectionKey.OP_ACCEPT);

		return socketSelector;
	}

	public SocketChannel ConnectTo(InetAddress host, int port) {
		SocketChannel sockChan = null;
		try {
			sockChan = this.initiateConnection(host, port);
			this.selector.wakeup();
		} catch (IOException ioe) {
			return null;
		}
		return sockChan;
	}

	private SocketChannel initiateConnection(InetAddress host, int port)
			throws IOException {
		// Create a non-blocking socket channel
		SocketChannel socketChannel = SocketChannel.open();
		socketChannel.configureBlocking(false);

		// Kick off connection establishment
		socketChannel.connect(new InetSocketAddress(host, port));

		// Queue a channel registration since the caller is not the
		// selecting thread. As part of the registration we'll register
		// an interest in connection events. These are raised when a channel
		// is ready to complete connection establishment.
		synchronized (this.pendingChanges) {
			this.pendingChanges.add(new PortalChangeRequest(socketChannel,
					PortalChangeRequest.REGISTER, SelectionKey.OP_CONNECT));
		}
		// Make and register a portal
		// this.CreateNewPortal(socketChannel);

		return socketChannel;
	}

	private void finishConnection(SelectionKey key) throws IOException {
		SocketChannel sockChan = (SocketChannel) key.channel();

		// Finish the connection. If the connection operation failed
		// this will raise an IOException.
		try {
			sockChan.finishConnect();

		} catch (IOException e) {
			// Cancel the channel's registration with our selector
			System.out.println(e);
			key.cancel();
			return;
		}

		// Make and register a portal
		this.CreateNewPortal(sockChan);

		// Register an interest in writing on this channel
		// key.interestOps(SelectionKey.OP_WRITE);
	}

	private void accept(SelectionKey key) throws IOException {

		// For an accept to be pending the channel must be a server socket
		// channel.
		ServerSocketChannel servSockChan = (ServerSocketChannel) key.channel();

		// Accept the connection and make it non-blocking
		SocketChannel sockChan = servSockChan.accept();
		Socket sock = sockChan.socket();
		sockChan.configureBlocking(false);
		sock.toString();

		// Register the new SocketChannel with our Selector, indicating
		// we'd like to be notified when there's data waiting to be read
		sockChan.register(this.selector, SelectionKey.OP_READ);

		// Make and register a portal
		@SuppressWarnings("unused")
		Portal p = this.CreateNewPortal(sockChan);
	}

	public boolean disconnectFrom(String host) throws IOException {
		this.out("Inside DisconnectFrom(Portal)", 2);

		synchronized (this.portals) {
			for (SocketChannel sc : this.portals.keySet()) {
				Portal p = this.portals.get(sc);
				if (p.getRemoteHostName().equals(host)) {
					return this.disconnectFrom(p);
				}
			}
		}

		return false;
	}

	public boolean disconnectFrom(Portal p) throws IOException {

		this.portals.remove(p.getSockChan());
		this.getLocalMS().UnRegisterPortal(p);

		StdMsg smout = this.getLocalMS().generateNewMsg(StdMsgTypes.mtGoodBye,
				"Portal2PortalComms");
		p.SendToRemHost(smout);
		p.getSockChan().close();

		return false;
	}

	public boolean disconnectFrom(InetAddress ip, int Port) throws IOException {

		for (Portal p : this.portals.values()) {
			if (ip.equals(p.getSockChan().socket().getInetAddress())
					&& Port == p.getSockChan().socket().getPort()) {
				return this.disconnectFrom(p);
				
			}
		}

		return false;
	}

	private boolean disconnect(SelectionKey key) throws IOException {
		this.out("Inside Disconnect(SelectionKey)", 2);

		this.disconnect((SocketChannel) key.channel());

		key.channel().close();
		key.cancel();
		return key.isValid();
	}

	private boolean disconnect(SocketChannel sockChan) throws IOException {
		this.out("Inside Disconnect(SocketChannel)", 2);
		System.err.println("Disconnect(SocketChannel)");

		Portal p = this.portals.remove(sockChan);
		this.getLocalMS().UnRegisterPortal(p);

		return sockChan.isConnected();

	}

	private Portal CreateNewPortal(SocketChannel sockChan) {
		// Make and register a portal
		String s = this.gON() + "-Portal:"
				+ Integer.toString(this.getNewPortalNumber());

		this.out("New portal.  Name: " + s, 2);

		Portal p = new Portal(s, this, sockChan, this.getLocalMS());
		this.portals.put(sockChan, p);
		return p;
	}

	private int getNewPortalNumber() {
		if (this.portalCnt == Integer.MAX_VALUE) {
			this.portalCnt = 0;
		}
		return this.portalCnt++;
	}

	@Override
	public Thread getThread() {
		return this.myThread;
	}

	@Override
	public boolean getRunStatus() {
		return this.runStatus;
	}

	public void start() {
		this.out("Received Startup Command.", 1);
		this.runCmd = true;
		this.runStatus = true;
		this.myThread = new Thread(this, this.gON().concat("-Thread"));
		this.myThread.start();
	}

	@Override
	public void stop() {
		this.out("Received Shutdown Command.", 1);
		this.runCmd = false;
		this.selector.wakeup();
	}

	@Override
	public boolean getRunCmd() {
		return this.runCmd;
	}

}
