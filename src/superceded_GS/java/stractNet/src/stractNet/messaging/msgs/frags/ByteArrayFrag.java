package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class ByteArrayFrag extends MsgFrag<byte[]> {
	public ByteArrayFrag(byte[] b) {
		super("ByteArrayFrag", b, MsgFrag.mftByteArray);
	}

	public ByteArrayFrag(DataInputStream in) {
		super("ByteArrayFrag", in, MsgFrag.mftByteArray);
	}

	@Override
	public void Deserialize(DataInputStream in) {
		try {
			//Read length of array
			int len = in.readInt();
			
			//Assign array
			this.field = new byte[len];
			
			//Read byte[]
			in.read(this.field );

		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return ;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			//Write length of array
			out.writeInt(this.field.length);
						
			//Write byte[]
			out.write(this.field);
			
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}

}
