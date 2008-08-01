package stractNet.messaging.msgs;

import stractNet.messaging.MsgStop;
import stractNet.messaging.NetID;
import stractNet.messaging.WayPoint;
import stractNet.messaging.msgs.frags.*;
import stractNet.SNRoot;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.util.ArrayList;

public class StdMsg extends SNRoot {

	/*
	 * Header Fields
	 */
	private NetID MsgID;
	private IntegerFrag MsgType;
	private StringFrag toHost;
	private StringFrag fromHost;
	private ArrayList<MsgFrag<?>> elements = new ArrayList<MsgFrag<?>>();
	private MsgStop LocalFrom;

	// private ArrayList<Integer> elementMap = new ArrayList<Integer>();

	/*
	 * Copy Constructor
	 */

	public StdMsg(StdMsg sm) {
		super("StdMsg");
		this.MsgID = new NetID(sm.getMsgID());
		this.MsgType = new IntegerFrag(sm.getMsgType());
		this.toHost = new StringFrag(sm.getToHost());
		this.elements = new ArrayList<MsgFrag<?>>(sm.GetElements());
		// Don't need a Deep Copy ... I think.
		this.LocalFrom = sm.LocalFrom;
		this.fromHost = sm.fromHost;
	}

	/*
	 * Manual Constructors
	 */

	public StdMsg(int msgType) {
		this(msgType, null);
	}

	public StdMsg(int msgType, String to) {
		super("StdMsg");
		this.MsgType = new IntegerFrag(msgType);
		this.MsgID = new NetID(-1, "DEFAULT");
		this.toHost = new StringFrag(to);
	}

	/*
	 * Deserializing Constructors
	 */
	public StdMsg(byte[] inData) {
		this(new DataInputStream(new ByteArrayInputStream(inData)));
	}

	public StdMsg(DataInputStream in) {
		super("StdMsg");

		// Get the total number of bytes for this message.
		int totalBytes;
		byte[] b;
		try {
			totalBytes = in.readInt();
			b = new byte[totalBytes]; // make a buffer
			in.readFully(b); // read in till the buffer's full.

			// make an input stream out of the buffer
			DataInputStream dis = new DataInputStream(new ByteArrayInputStream(
					b));

			try {
				this.DeserializeHeader(dis);
			} catch (IOException e) {
				System.err.println("Failed in Header Gen.");
			}
			try {
				this.DeserializeElements(dis);
			} catch (IOException e) {
				System.err.println("Failed in Element Gen.");
			}
		} catch (IOException e1) {
			System.err.println("MessageLen to Actual Data Read mismatch.");
		}

	}

	private void DeserializeHeader(DataInputStream in) throws IOException {
		// Read MsgID
		this.MsgID = new NetID(in);

		// Read Type
		in.readInt();
		this.MsgType = new IntegerFrag(in);

		// Read TO
		in.readInt();
		this.toHost = new StringFrag(in);

		// Read FROM
		in.readInt();
		this.fromHost = new StringFrag(in);
		return;
	}

	private void DeserializeElements(DataInputStream in) throws IOException {

		try {
			// try to read what type of Frag is next:
			int nextFrag = in.readInt();

			// loop till there arent anymore Elements
			while (nextFrag != -1) {

				switch (nextFrag) {
				case (MsgFrag.mftBoolean):
					this.elements.add(new BooleanFrag(in));
					break;
				case (MsgFrag.mftDouble):
					this.elements.add(new DoubleFrag(in));
					break;
				case (MsgFrag.mftFloat):
					this.elements.add(new FloatFrag(in));
					break;
				case (MsgFrag.mftInteger):
					this.elements.add(new IntegerFrag(in));
					break;
				case (MsgFrag.mftLong):
					this.elements.add(new LongFrag(in));
					break;
				case (MsgFrag.mftShort):
					this.elements.add(new ShortFrag(in));
					break;
				case (MsgFrag.mftString):
					this.elements.add(new StringFrag(in));
					break;
				case (MsgFrag.mftWaypoint):
					this.elements.add(new WayPointFrag(in));
					break;
				case (MsgFrag.mftByteArray):
					this.elements.add(new ByteArrayFrag(in));
					break;
				default:
					this.err("Unknown Message Fragment: " + nextFrag, 0);
					break;

				}

				// try to read what type of Frag is next:
				nextFrag = in.readInt();

			}
		} catch (EOFException eof) {
			// We read till the end of the stream

		}
	}

	/*
	 * Serializer
	 */

	public byte[] Serialize() {

		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		try {
			if (!this.Serialize(out)) {
				return null;
			}

			// get the message data
			byte[] b1 = baos.toByteArray();

			// reset baos.
			ByteArrayOutputStream baos2 = new ByteArrayOutputStream();
			DataOutputStream out2 = new DataOutputStream(baos2);

			// Write the length of all the data in the message.
			out2.writeInt(b1.length);

			// Write in all the data
			baos2.write(b1);

			return baos2.toByteArray();
		} catch (IOException e) {
			this.err("IOException in Serialize(}", 0);
			return null;
		}

	}

	private boolean Serialize(DataOutputStream out) throws IOException {

		// validate data:
		if (this.toHost.getField() == null || this.toHost.getField().equals("")) {
			this.err(
					"MsgID: " + this.MsgID.toString() + ": 'To' Field is Null",
					0);
			return false;
		}

		if (out == null) {
			System.err.println("OUT IS NULL");
		}

		this.SerializeHeader(out);
		this.SerializeElements(out);

		return true;
	}

	private void SerializeHeader(DataOutputStream out) throws IOException {
		// Write MsgID
		this.MsgID.Serialize(out);

		// Write Type
		this.MsgType.Serialize(out);

		// Write To
		this.toHost.Serialize(out);

		// Write To
		this.fromHost.Serialize(out);

	}

	private void SerializeElements(DataOutputStream out) throws IOException {
		// Write in All Frags.
		for (MsgFrag<?> mf : this.elements) {
			mf.Serialize(out);
		}

	}

	/*
	 * Utilities
	 */
	public void StampWayPoint(WayPoint wp) {
		this.elements.add(new WayPointFrag(wp));
	}

	public void StampWayPoint(String Host) {
		this.elements.add(new WayPointFrag(new WayPoint(Host)));
	}

	public void AddElement(MsgFrag<?> element) {
		this.elements.add(element);
	}

	public boolean RemoveElement(MsgFrag<?> element) {
		return this.elements.remove(element);
	}

	public boolean HasElement(MsgFrag<?> element) {
		return this.elements.contains(element);
	}

	public int IndexOfElement(MsgFrag<?> element) {
		return this.elements.indexOf(element);
	}

	public ArrayList<MsgFrag<?>> GetElements() {
		return this.elements;
	}

	public MsgFrag<?> GetElement(int index) {
		return this.elements.get(index);
	}

	public String toString() {
		return "StdMsg" + "(ID: " + this.MsgID.toString() + "): \tType: "
				+ this.MsgType + " \tTo: " + this.toHost.toString()
				+ " \tFrom: " + this.fromHost.toString() + " \tElements: "
				+ this.elements.size();
	}

	public String WaypointsToString() {
		String out = "";
		for (WayPoint wp : this.getWayPoints()) {
			out = out.concat("\t" + wp.toString()) + "\n";
		}
		return out;
	}

	public String ElementsToString() {
		String out = "";
		for (MsgFrag<?> mf : this.elements) {
			out = out.concat("\t".concat(mf.toString())).concat("\n");
		}
		return out;
	}

	/*
	 * Getters & Setters
	 */
	public ArrayList<WayPoint> getWayPoints() {
		ArrayList<WayPoint> wps = new ArrayList<WayPoint>();

		for (MsgFrag<?> mf : this.elements) {
			if (mf.getMFType() == MsgFrag.mftWaypoint) {
				wps.add((WayPoint) mf.getField());
			}
		}
		return wps;
	}

	public NetID getMsgID() {
		return MsgID;
	}

	public void setMsgID(NetID msgID) {
		MsgID = msgID;
	}

	public int getMsgType() {
		return MsgType.getField();
	}

	public void setMsgType(int msgType) {
		this.MsgType.setField(msgType);
	}

	public String getToHost() {
		return toHost.getField();
	}

	public StringFrag getToHostFrag() {
		return toHost;
	}

	public void setToHost(String toHost) {
		this.toHost = new StringFrag(toHost);
	}

	public void setToHostFrag(StringFrag toHostFrag) {
		this.toHost = toHostFrag;
	}

	public String getFromHost() {
		return fromHost.getField();
	}

	public StringFrag getFromHostFrag() {
		return fromHost;
	}

	public void setFromHost(String fromHost) {
		this.fromHost = new StringFrag(fromHost);
	}

	public void setFromHostFrag(StringFrag fromHostFrag) {
		this.fromHost = fromHostFrag;
	}

	public MsgStop getLocalFrom() {
		return LocalFrom;
	}

	public void setLocalFrom(MsgStop localFrom) {
		LocalFrom = localFrom;
	}

}
