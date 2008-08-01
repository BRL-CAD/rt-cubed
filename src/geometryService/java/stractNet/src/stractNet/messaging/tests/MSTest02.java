package stractNet.messaging.tests;

import stractNet.*;
import stractNet.messaging.*;
import stractThread.STRunManager;
import stractThread.STUtilities;

import java.util.*;

/*
 * Message Delievery Speed test
 */

public class MSTest02 extends SNRoot {

	public static final int MsgsToSend = 5000;
	public static final long Delay = 0L;
	public static final int ITERATIONS = 25;

	public static MSTest02 test;

	public static void main(String[] args) {

		float[] perfs = new float[ITERATIONS];
		SNRoot.VerbosityLevel = 0;
		long totalMsgs = 0L;
		long totalTime = 0L;

		for (int i = 0; i < ITERATIONS; i++) {
			test = new MSTest02();
			perfs[i] = test.throughput;
			totalMsgs += test.totMsgs;
			totalTime += test.totTime;
			SNRoot.sout("Iteration #".concat(Integer.toString(i)) + " => "
					+ test.throughput + " msgs/sec", 0);
			test = null;
		}

		float total = 0.0f;
		float avg = 0.0f;

		for (int i = 0; i < ITERATIONS; i++) {
			total += perfs[i];
		}

		avg = total / ITERATIONS;
		SNRoot.sout("\n\nOverall:", 0);
		SNRoot.sout("\tTime: " + totalTime, 0);
		SNRoot.sout("\tMessages: " + totalMsgs + "("
				+ (MsgsToSend * ITERATIONS * 4) + ")", 0);
		SNRoot.sout("\tAverage throughput: " + avg + " msgs/sec\n\n\n", 0);

	}

	public float throughput = 0.0f;
	public long totMsgs;
	public long totTime;

	public MSTest02() {
		super("MSTest02");

		STRunManager strm = new STRunManager("MSTest01-RunMan");

		this.setLocalMS(new MessagingSystem("MsgServer"));
		MessageDispatcher md1 = this.getLocalMS().generateNewMD();
		strm.addExecute(md1.gON(), md1);

		this.out("Running.", 1);

		long startT = new Date().getTime();

		int[] set01 = { 1, 2, 3, 4 };
		PlaceboMsgStoppableClass pmsc01 = new PlaceboMsgStoppableClass(
				"pmsc01", MsgsToSend, Delay, this.getLocalMS());
		pmsc01.getMsgStop().addMsgTypes(set01);
		this.getLocalMS().RegisterMsgStop(pmsc01.getMsgStop());

		strm.addExecute("MS01", pmsc01);

		int[] set02 = { 3, 4, 5, 6, 7 };
		PlaceboMsgStoppableClass pmsc02 = new PlaceboMsgStoppableClass(
				"pmsc02", MsgsToSend, Delay, this.getLocalMS());
		pmsc02.getMsgStop().addMsgTypes(set02);
		this.getLocalMS().RegisterMsgStop(pmsc02.getMsgStop());

		strm.addExecute("MS02", pmsc02);

		int[] set03 = { 6, 7, 8, 9, 10 };
		PlaceboMsgStoppableClass pmsc03 = new PlaceboMsgStoppableClass(
				"pmsc03", MsgsToSend, Delay, this.getLocalMS());
		pmsc03.getMsgStop().addMsgTypes(set03);
		this.getLocalMS().RegisterMsgStop(pmsc03.getMsgStop());

		strm.addExecute("MS03", pmsc03);

		// int[] set04 = { 3, 4, 5, 6, 7 };
		// PlaceboMsgStoppableClass pmsc04 = new PlaceboMsgStoppableClass(
		// "pmsc04", MsgsToSend, Delay, this.getLocalMS());
		// pmsc04.getMsgStop().addMsgTypes(set04);
		// this.getLocalMS().RegisterMsgStop(pmsc04.getMsgStop());
		//
		// strm.addExecute("MS04", pmsc04);

		this.out("Waiting...", 1);
		while (strm.areAnyStatusRunning()) {
			STUtilities.pause(25);
		}

		long stopT = new Date().getTime() + 1;

		this.out("Shutting down Runnable(s)...", 11);
		strm.stopAll(true);
		if (strm.areAnyStatusRunning()) {
			this.err("Runnable(s) failed to stop.", 0);
			return;
		}
		this.out("Shutdown.", 1);

		this.totTime = (stopT - startT);
		this.totMsgs = this.getLocalMS().getMsgsRouted();
		this.throughput = (this.getLocalMS().getMsgsRouted() / (float) totTime) * 1000.0f;

		this.out("Time: " + totTime, 1);
		this.out("Messages: " + this.totMsgs, 1);
		this.out("Average throughput: " + this.throughput + " msgs/sec\n\n\n",
				1);

	}

}
