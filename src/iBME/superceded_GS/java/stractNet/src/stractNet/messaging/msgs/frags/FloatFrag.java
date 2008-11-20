package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class FloatFrag extends MsgFrag<Float> {
	public FloatFrag(float fl) {
		super("FloatFrag", fl, MsgFrag.mftFloat);
	}

	public FloatFrag(DataInputStream in) {
		super("FloatFrag", in, MsgFrag.mftFloat);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {
			// Read Float
			this.field = in.readFloat();
		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.writeFloat(this.field);
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
