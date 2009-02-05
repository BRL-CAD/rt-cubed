import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class RemHostNameSetMsg extends AbstractMsg {
	private String hostname;

	public RemHostNameSetMsg(int type, String muuid, String ruuid, String hostname) {
		super(type, muuid, ruuid);
		this.hostname = hostname;
	}

	public RemHostNameSetMsg() {
		super();
	}

	public RemHostNameSetMsg(byte[] data) {
		super(data);
	}

	public RemHostNameSetMsg(DataInputStream dis) {
		super(dis);
	}

	public RemHostNameSetMsg(NetMsg msg, DataInputStream dis) {
		super(msg, dis);
	}

	@Override
	protected void _deserialize(DataInputStream dis) {
		try {
			int hnLen;
			hnLen = dis.readInt();
			byte[] baHN = new byte[hnLen];
			dis.read(baHN, 0, hnLen);
			this.hostname = new String(baHN);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void _serialize(DataOutputStream dos) {
		try {
			// Hostname
			dos.writeInt(this.hostname.length());
			// Gotta do this since java Chars are Unicode
			dos.write(this.hostname.getBytes("US-ASCII"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected String _toString()
	{
		return "Hostname: " + this.hostname + "\t ";
	}

	/*
	 * Getters n Setters
	 */

	public String getHostname() {
		return hostname;
	}

	public void setHostname(String hostname) {
		this.hostname = hostname;
	}

}
