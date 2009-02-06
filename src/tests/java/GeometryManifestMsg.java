import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;

public class GeometryManifestMsg extends AbstractMsg {
	private ArrayList<String> items = new ArrayList<String>();

	public GeometryManifestMsg() {
		super();
	}

	public GeometryManifestMsg(byte[] data) {
		super(data);
	}

	public GeometryManifestMsg(DataInputStream dis) {
		super(dis);
	}

	public GeometryManifestMsg(int type, String muuid, String ruuid) {
		super(type, muuid, ruuid);
	}

	public GeometryManifestMsg(NetMsg msg, DataInputStream dis) {
		super(msg, dis);
	}

	@Override
	protected void _deserialize(DataInputStream dis) {
		try {
			this.items = new ArrayList<String>();
			int itemsInManifest = dis.readInt();
			int len = 0;

			for (int i = 0; i < itemsInManifest; ++i) {
				len = dis.readInt();
				byte[] ba = new byte[len];
				dis.read(ba, 0, len);
				this.items.add(new String(ba));

			}

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void _serialize(DataOutputStream dos) {
		try {

			// Number of Items in Manifest:
			dos.writeInt(this.items.size());

			// Items
			for (String item : this.items) {
				// ItemLEN
				dos.writeInt(item.length());
				// Gotta do this since java Chars are Unicode
				dos.write(item.getBytes("US-ASCII"));
			}

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected String _toString() {
		return "Number of Items: " + this.items.size() + "\t ";
	}

	/*
	 * Getters n Setters
	 */

	public ArrayList<String> getItems() {
		return items;
	}	
}
