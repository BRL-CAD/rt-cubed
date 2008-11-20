package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class LongFrag extends MsgFrag<Long> {
	public LongFrag(Long lo) {
		super("LongFrag", lo, MsgFrag.mftLong);
	}

	public LongFrag(DataInputStream in) {
		super("LongFrag", in, MsgFrag.mftLong);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {
			// Read Integer
			this.field = in.readLong();
		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.writeLong(this.field);
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
