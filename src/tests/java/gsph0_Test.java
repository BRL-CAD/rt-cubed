import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.UUID;

public class gsph0_Test
{
	public static void main(String[] args) {
		Socket s;
		DataInputStream dis;
		DataOutputStream dos;
		int i = 0;
		
		try {
			s = new Socket("128.63.32.72", 56789);
			dis = new DataInputStream(s.getInputStream());
			dos = new DataOutputStream(s.getOutputStream());
				
			//test sending a msg
			sendRemHostNameSET(dos);
			
			while (++i < 20) {
				
				//Wait till there is enough in the input stream
				while(dis.available() < 4) {
					System.out.println("Have: " + dis.available() + " waiting for 4");
					Thread.sleep(10L);	
				}

				int msgLen = dis.readInt() - 4;
				
				//Wait till there is enough in the input stream
				while(dis.available() < msgLen) {
					System.out.println("Have: " + dis.available() + " waiting for " + msgLen);
					Thread.sleep(10L);			
				}

				System.out.println("Have: " + dis.available() + ", making msg:\n");

				
				int msgType = dis.readInt();
				System.out.println("\tmsgType=" + msgType + "\t\t\tLEN=4");
				System.out.println("\t\t" + dis.available() + " remaining");
				
				int msgUUIDlen = dis.readInt();
				byte[] baMsgUUID = new byte[msgUUIDlen];
				dis.read(baMsgUUID, 0, msgUUIDlen);
				String msgUUID = new String(baMsgUUID);
				System.out.println("\tMsgUUID='" + msgUUID + "'\t LEN=" + msgUUIDlen);
				System.out.println("\t\t" + dis.available() + " remaining");
				
				int reUUIDlen = dis.readInt();
				byte[] baReUUID = new byte[reUUIDlen];
				dis.read(baReUUID, 0, reUUIDlen);
				String reUUID = new String(baReUUID);
				System.out.println("\tReUUID= '" + reUUID + "'\t LEN=" + reUUIDlen);
				System.out.println("\t\t" + dis.available() + " remaining");
				
				byte by= dis.readByte();
				System.out.println("\tErrorCode=" + by + "\t LEN=1");
				System.out.println("\t\t" + dis.available() + " remaining");
				
				System.out.println("Have: " + dis.available() + " leftover.");
				break;
			}
			
			
			
			
			s.close();
			
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}		
	}

	
	public static void sendRemHostNameSET(DataOutputStream dos) {
		
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);
			
		try {
			out.writeInt(0); //msgType
			
//			String MsgUUID = UUID.randomUUID().toString();
			String MsgUUID = "dcae96d9-a1bc-4d0c-bfbe-f3035b4fc7df";
			System.out.println(MsgUUID + " Size=" + MsgUUID.length());
			out.writeInt(MsgUUID.length());
			out.write(MsgUUID.getBytes("US-ASCII"));
			
			
//			String ReUUID = UUID.randomUUID().toString();
			String ReUUID = "b01e3f29-8dd1-4d37-8d77-58a96b9348e9";
			System.out.println(ReUUID + " Size=" + ReUUID.length());
			out.writeInt(ReUUID.length());
			out.write(ReUUID.getBytes("US-ASCII"));
			
			
			String hostname = "Shota";
	
			System.out.println(hostname + " Size=" + hostname.length());
			out.writeInt(hostname.length());
			out.write(hostname.getBytes("US-ASCII"));
			
			byte[] ba = baos.toByteArray();

			
			
			
			// Write the length of all the data in the message.
			dos.writeInt(ba.length);
			System.out.println(ba.length);
			System.out.println(ba);
			
			
			// Write in all the data
			dos.write(ba);
		} catch (IOException e) {
			e.printStackTrace();
		}		
	}
}
