package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class ShortFrag extends MsgFrag<Short> {
	public ShortFrag(Short sh) {
		super("ShortFrag", sh, MsgFrag.mftShort);
	}

	public ShortFrag(DataInputStream in) {
		super("ShortFrag", in, MsgFrag.mftShort);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {
			// Read Short
			this.field = in.readShort();
		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.writeShort(this.field);
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
