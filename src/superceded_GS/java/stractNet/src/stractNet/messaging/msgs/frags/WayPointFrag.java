package stractNet.messaging.msgs.frags;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import stractNet.messaging.WayPoint;

public class WayPointFrag extends MsgFrag<WayPoint> {

	public WayPointFrag(WayPoint wp) {
		super("WayPointFrag", wp, MsgFrag.mftWaypoint);
	}
	
	
	public WayPointFrag(DataInputStream in) {
		super("WayPointFrag", in, MsgFrag.mftWaypoint);
	}

	@Override
	protected void Deserialize(DataInputStream in) {
		try {
			//Read WayPoint
			this.field = new WayPoint(in);
		} catch (IOException ioe) {
			this.err("IOException in Deserialize()", 0);
		}
		return;
	}

	@Override
	protected void Serialize_Specific(DataOutputStream out) {
		try {
			// write in new data
			out.write(this.field.Serialize());
		} catch (IOException ioe) {
			this.err("IOException in Serialize()", 0);
		}

		return;
	}


	//Custom Getter
	public WayPoint getWayPoint() {
		return (WayPoint)this.getField();
	}
	
}
