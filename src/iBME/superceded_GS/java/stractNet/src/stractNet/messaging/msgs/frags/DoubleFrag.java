package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class DoubleFrag extends MsgFrag<Double> {
	public DoubleFrag(double db) {
		super("DoubleFrag", db, MsgFrag.mftDouble);
	}

	public DoubleFrag(DataInputStream in) {
		super("DoubleFrag", in, MsgFrag.mftDouble);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {
			// Read Double
			this.field = in.readDouble();
		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.writeDouble(this.field);
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
