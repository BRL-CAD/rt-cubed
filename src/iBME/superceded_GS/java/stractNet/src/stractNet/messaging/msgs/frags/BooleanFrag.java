package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class BooleanFrag extends MsgFrag<Boolean> {
	public BooleanFrag(boolean boo) {
		super("BooleanFrag", boo, MsgFrag.mftBoolean);
	}

	public BooleanFrag(DataInputStream in) {
		super("BooleanFrag", in, MsgFrag.mftBoolean);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {
			//Read Boolean
			this.field = in.readBoolean();

		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return ;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.writeBoolean(this.field);
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
