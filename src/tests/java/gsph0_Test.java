/*                 G S P H 0 _ T E S T . J A V A
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/** @file gsph0_Test.java
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.UUID;

public class gsph0_Test {
	public static void main(String[] args) {
		Socket s;
		DataInputStream dis;
		DataOutputStream dos;

		try {
			s = new Socket("128.63.32.72", 56789);
			dis = new DataInputStream(s.getInputStream());
			dos = new DataOutputStream(s.getOutputStream());

			// Start by sending a RemHostNameSetMsg
			RemHostNameSetMsg msg01 = new RemHostNameSetMsg(MsgTypes.RemHostNameSET, UUID.randomUUID().toString(), UUID.randomUUID()
					.toString(), "Shota");

			// serialize it and send it to the socket
			msg01.serialize(dos);
			System.out.print("Sent:\t");
			msg01.printMe();
			
			gsph0_Test.sendRecvLoop(dis, dos);

			s.close();

		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void sendRecvLoop(DataInputStream sockIn, DataOutputStream sockOut) {
		int loopCnt = 0;
		long waitTime = 100L;
		NetMsg villageMsg;
		
		while (loopCnt++ < 4)
			
		try {
			System.out.println("\n\nSend/Recv Loop pass #" + loopCnt);

			/*
			 * RECV
			 */

			// Wait till there is enough in the input stream
			System.out.print("Have: " + sockIn.available() + " bytes, waiting for 4 bytes... ");
			while (sockIn.available() < 4) {
				Thread.sleep(waitTime);
			}
			System.out.println("Done.");

			
			int msgLen = sockIn.readInt();
			System.out.println("New MsgLen: " + msgLen + ". (" + sockIn.available() +  "/" + msgLen + ")");

			
			// Wait till there is enough in the input stream
			while (sockIn.available() < msgLen) {
				Thread.sleep(waitTime);
				System.out.println("\t\t(" + sockIn.available() +  "/" + msgLen + ")");
			}
			
			villageMsg = new NetMsg(sockIn);
			villageMsg.printMe();
			
			switch (villageMsg.getMsgType()) {
			case MsgTypes.RemHostNameSET:
				
				RemHostNameSetMsg msg1 = new RemHostNameSetMsg(villageMsg, sockIn);
				msg1.printMe();
				
				//Now send an OK
				NetMsg okayMsg = new NetMsg(MsgTypes.RemHostNameSETOK, UUID.randomUUID().toString(), UUID.randomUUID().toString() );
				System.out.print("Sending: ");
				okayMsg.serialize(sockOut);
				okayMsg.printMe();
				
				//Sent the OK, now wait a bit
				System.out.print("\nThis app waits a bit, then requests a new Session.\n");
				Thread.sleep(2500L);
				
				//Now send a NewSessionRequest
				NetMsg newSession = new NetMsg(MsgTypes.NewSessionREQ, UUID.randomUUID().toString(), UUID.randomUUID().toString() );
				System.out.print("Sending: ");
				newSession.serialize(sockOut);
				newSession.printMe();
				
				break;
			case MsgTypes.RemHostNameSETFAIL:
				
				RemHostNameSetFailMsg msg2 = new RemHostNameSetFailMsg(villageMsg, sockIn);
				msg2.printMe();
				return; //Exit loop
				
			case MsgTypes.RemHostNameSETOK:
				//NoReply Needed				
				break;
			case MsgTypes.DisconnectREQ:
				return; //Exit loop
			case MsgTypes.NewHostOnNetINFO:
				break;
			
			case MsgTypes.NewSessionREQ:
				break;
			case MsgTypes.NewSessionREQFAIL:
				break;
			case MsgTypes.NewSessionREQOK:
				RemHostNameSetMsg nsReqOkay = new RemHostNameSetMsg(villageMsg, sockIn);
				nsReqOkay.printMe();
				
				
				//Got a new Session, now wait a bit
				System.out.print("\nThis app waits a bit, then requests a some Geometry.\n");
				Thread.sleep(2500L);
				
				//Now send a NewSessionRequest
				GeometryReqMsg geoReq = new GeometryReqMsg(MsgTypes.GeometryREQ, 
									UUID.randomUUID().toString(), UUID.randomUUID().toString(),
									(byte)1, "testing.g");
				System.out.print("Sending: ");
				geoReq.serialize(sockOut);
				geoReq.printMe();
		
				break;

			case MsgTypes.GeometryREQ:
				break;
			case MsgTypes.GeometryREQFAIL:
				break;
			case MsgTypes.GeometryMANIFEST:
				break;
			case MsgTypes.GeometryCHUNK:
				break;
				
			default:
				System.err.println("Unknown msgType!");
				
				
				break;
			}
			
			
			
			//Clean up the bytes here based on msgLen from above....
			

		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

}
