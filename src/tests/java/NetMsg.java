import java.io.DataInputStream;
import java.io.DataOutputStream;


public class NetMsg extends AbstractMsg {

	public NetMsg() {
		super();
	}

	public NetMsg(byte[] data) {
		super(data);
	}

	public NetMsg(DataInputStream dis) {
		super(dis);
	}

	public NetMsg(int type, String muuid, String ruuid) {
		super(type, muuid, ruuid);
	}

	public NetMsg(NetMsg msg, DataInputStream dis) {
		super(msg, dis);
	}

	
	@Override
	protected void _deserialize(DataInputStream dis) {
	}

	@Override
	protected void _serialize(DataOutputStream dos) {
	}

	@Override
	protected String _toString()
	{
		return "";
	}
}
