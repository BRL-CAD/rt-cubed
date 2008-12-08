package stractNet.messaging.msgs.tests;

import stractNet.messaging.MessagingSystem;
import stractNet.messaging.msgs.*;
import stractNet.messaging.msgs.frags.*;
import java.io.*;

public class MsgSerializationTest01 {

	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws InterruptedException {
		printBar();
		TestWayPoints();
		}


	private static void TestWayPoints() throws InterruptedException {
		
		MessagingSystem myMS = new MessagingSystem("MyMS");
		
		System.out.println("\n\nTesting Waypoints:\n");
		StdMsg smA = StdMsgUtil.RandGenMsgFactory(myMS);
		smA.StampWayPoint("Kentshire");
		smA.setToHost("Sahara");
		smA.StampWayPoint("MrBrown");
		smA.StampWayPoint("MrsGreen");
		smA.StampWayPoint("Halifax");
		smA.AddElement(new BooleanFrag(false));
		smA.AddElement(new BooleanFrag(true));
		smA.AddElement(new DoubleFrag(654.654654654987987654216123546645));
		smA.AddElement(new FloatFrag(12345.678910f));
		smA.AddElement(new ShortFrag((short) 124));
		smA.AddElement(new IntegerFrag(Integer.MAX_VALUE));
		smA.AddElement(new LongFrag(Long.MAX_VALUE));
		smA.AddElement(new StringFrag("This is a test of the String Fragment"));

		
		
		System.out.println("\nInitial Msg: \t" + smA.toString());
		System.out.println(smA.ElementsToString());
		
		
		byte[] byteData = smA.Serialize();
		
		
		System.out.println("\nSerialized Data: " + new String(byteData));
		System.out.println("\n\n\n\n\nDeserializing Data:\n\n");
		try {
			StdMsg smB = myMS.generateNewMsg(byteData);
			System.out.println("\nFinal Msg: \t" + smB.toString());
			System.out.println(smA.ElementsToString());

		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	private static void printBar() {

		System.out.println("\n\n");

		for (int a = 0; a < 3; a++) {
			for (int i = 0; i < 90; i++) {
				System.out.print("*");
			}
			System.out.println();
		}

	}

}
