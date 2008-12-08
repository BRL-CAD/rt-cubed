package stractNet.util.tests;

import stractNet.util.SNUtilities;

public class ByteConverterTests {


	public static void main(String[] args) {


		int i = 100330;
		System.out.println(i);	
		byte[] by1 = SNUtilities.intToByteArray(i);
		System.out.println(by1.toString());	
		int io = SNUtilities.byteArrayToInt(by1);
		System.out.println(io);
		
		System.out.println();
		
		
		int[] ia = {14356,21234,39865};
		for (int it : ia) {System.out.print(it);System.out.print(", ");}	
		System.out.println();
		byte[] by2 = SNUtilities.intArrayToByteArray(ia);
		System.out.println(by2.toString());	
		int[] iao = SNUtilities.byteArrayToIntArray(by2);
		for (int it : iao) {System.out.print(it);System.out.print(", ");}			
		System.out.println();
		
		System.out.println();
		System.out.println();
		
		
		long l = 1003309345987323245L;
		System.out.println(i);	
		byte[] by3 = SNUtilities.longToByteArray(l);
		System.out.println(by3.toString());	
		io = SNUtilities.byteArrayToInt(by3);
		System.out.println(io);
		
		System.out.println();
		
		
		long[] la = {1435622356346L,2123332455353544L,3323245234532455L};
		for (long lt : la) {System.out.print(lt);System.out.print(", ");}	
		System.out.println();
		byte[] by4 = SNUtilities.longArrayToByteArray(la);
		System.out.println(by4.toString());	
		long[] lao = SNUtilities.byteArrayToLongArray(by4);
		for (long lt : lao) {System.out.print(lt);System.out.print(", ");}	
		System.out.println();
		
		
		
		
	}

}
