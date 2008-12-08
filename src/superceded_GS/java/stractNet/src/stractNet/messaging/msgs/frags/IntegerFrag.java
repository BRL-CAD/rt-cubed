package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class IntegerFrag extends MsgFrag<Integer> {
	public IntegerFrag(int in) {
		super("IntegerFrag", in, MsgFrag.mftInteger);
	}

	public IntegerFrag(DataInputStream in) {
		super("IntegerFrag", in, MsgFrag.mftInteger);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {
			// Read Integer
			this.field = in.readInt();
		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.writeInt(this.field);
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
