import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class RemHostNameSetFailMsg extends AbstractMsg {
	private byte failureCode;

	public RemHostNameSetFailMsg() {
		super();
	}

	public RemHostNameSetFailMsg(byte[] data) {
		super(data);
	}

	public RemHostNameSetFailMsg(DataInputStream dis) {
		super(dis);
	}

	public RemHostNameSetFailMsg(int type, String muuid, String ruuid, byte failcode) {
		super(type, muuid, ruuid);
		this.failureCode = failcode;
	}

	public RemHostNameSetFailMsg(NetMsg msg, DataInputStream dis) {
		super(msg, dis);
	}

	@Override
	protected void _deserialize(DataInputStream dis) {
		try {
			this.failureCode = dis.readByte();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void _serialize(DataOutputStream dos) {
		try {
			dos.write(this.failureCode);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected String _toString() {
		return "FailureCode: " + this.failureCode + "\t ";
	}

	/*
	 * Getters n Setters
	 */

	public byte getHostname() {
		return this.failureCode;
	}

	public void setFailureCode(byte failcode) {
		this.failureCode = failcode;
	}

}
