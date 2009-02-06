import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class GeometryChunkMsg extends AbstractMsg {
	private byte[] data;

	public GeometryChunkMsg() {
		super();
	}

	public GeometryChunkMsg(byte[] data) {
		super(data);
	}

	public GeometryChunkMsg(DataInputStream dis) {
		super(dis);
	}

	public GeometryChunkMsg(int type, String muuid, String ruuid, byte[] data) {
		super(type, muuid, ruuid);
		this.data = data;
	}

	public GeometryChunkMsg(NetMsg msg, DataInputStream dis) {
		super(msg, dis);
	}

	@Override
	protected void _deserialize(DataInputStream dis) {
		try {

			// data
			int dataLen;
			dataLen = dis.readInt();
			this.data = new byte[dataLen];
			dis.read(data, 0, data.length);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void _serialize(DataOutputStream dos) {
		try {
			// data
			dos.writeInt(this.data.length);
			dos.write(this.data);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected String _toString() {
		return "RequestType: " + this.data + "\t Data: " + this.data + "\t ";
	}

	/*
	 * Getters n Setters
	 */
	public byte[] getData() {
		return this.data;
	}

}
