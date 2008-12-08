package stractNet.portals;

import java.nio.channels.SocketChannel;

class PortalDataEvent {
  public PortalManager server;
  public SocketChannel socket;
  public byte[] data;
  
  public PortalDataEvent(PortalManager server, SocketChannel socket, byte[] data) {
    this.server = server;
    this.socket = socket;
    this.data = data;
  }
}