import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class GeometryReqMsg extends AbstractMsg {
	private byte reqType;
	private String data;

	public GeometryReqMsg() {
		super();
	}

	public GeometryReqMsg(byte[] data) {
		super(data);
	}

	public GeometryReqMsg(DataInputStream dis) {
		super(dis);
	}

	public GeometryReqMsg(int type, String muuid, String ruuid,byte requestType, String data) {
		super(type, muuid, ruuid);
		this.reqType = requestType;
		this.data = data;
	}

	public GeometryReqMsg(NetMsg msg, DataInputStream dis) {
		super(msg, dis);
	}

	@Override
	protected void _deserialize(DataInputStream dis) {
		try {
			// reqType
			this.reqType = dis.readByte();

			// data
			int dataLen;
			dataLen = dis.readInt();
			byte[] baData = new byte[dataLen];
			dis.read(baData, 0, dataLen);
			this.data = new String(baData);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void _serialize(DataOutputStream dos) {
		try {
			// reqType
			dos.writeByte(this.reqType);

			// data
			dos.writeInt(this.data.length());
			// Gotta do this since java Chars are Unicode
			dos.write(this.data.getBytes("US-ASCII"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected String _toString() {
		return "RequestType: " + this.reqType + "\t Data: " + this.data + "\t ";
	}

	/*
	 * Getters n Setters
	 */
	public byte getReqType() {
		return this.reqType;
	}

	public void setReqType(byte reqType) {
		this.reqType = reqType;
	}

	public String getData() {
		return this.data;
	}

	public void setData(String data) {
		this.data = data;
	}

}
