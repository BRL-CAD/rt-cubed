package stractNet.messaging.msgs;

import stractNet.SNRoot;
import stractNet.util.SNUtilities;
import stractNet.messaging.MessagingSystem;
import stractNet.messaging.msgs.frags.ByteArrayFrag;

public class StdMsgUtil extends SNRoot {

	public StdMsgUtil() {
		super("SNMsgUtil");
	}
	
	
	
	
	public static StdMsg RandGenMsgFactory(MessagingSystem ms) {
		byte[] data = SNUtilities.randomByteArrayGenerator();
		StdMsg gm = ms.generateNewMsg(StdMsgTypes.mtHello);
		
		gm.AddElement(new ByteArrayFrag(data));
		return gm;
	}	
	
	
	
	
	
	
}
