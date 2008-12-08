package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class StringFrag extends MsgFrag<String> {
	public StringFrag(String str) {
		super("StringFrag", str, MsgFrag.mftString);
	}

	public StringFrag(DataInputStream in) {
		super("StringFrag", in, MsgFrag.mftString);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {

			// Read LEN then String
			int strLen = in.readInt();
			char[] c = new char[strLen];

			// Convert String
			for (int i = 0; i < strLen; i++) {
				c[i] = in.readChar();
			}
			this.field = new String(c);

		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.writeInt(this.field.length());
			out.writeChars(this.field);
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
