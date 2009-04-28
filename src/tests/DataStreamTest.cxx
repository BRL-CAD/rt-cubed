///////////////////////////////////////////////////////////
//
//        EXE entry point
//
///////////////////////////////////////////////////////////


#include <cstdlib>
#include <iostream>
#include <string>
#include "GE/io/DataStream.h"

int main(int argc, char* argv[])
{

  std::cout.precision(25);


  ////////////////
  //Serialize 
  ////////////////
 
  ////////////////////////////
  std::cout << "\n----\n\n";
  ////////////////////////////

  DataStream* pds = new DataStream(64);

  DataStream ds = *pds;

  bool boo = false;

  unsigned char ub = 255;
  char b =   127;

  unsigned short ush = 65535;
  short sh =   32767;

  unsigned int ui = 4294967295;
  int i =   2147483647;

  //  uLong ul = 18446744073709551615;
  //  Long l =    9223372036854775807;

  float f =  1234.567890123456789;
  double d = 1234.567890123456789;


  std::string str = "This is a test string for the serialization test!";
  
  try {
  
    ds << ub;
    ds << b;
    ds << ush;
    ds << sh;
    ds << ui;
    ds << i;
    //  ds << ul;
    //  ds << l;
    ds << str;
    ds << f;
    ds << d;


    /////////////////////////
    std::cout << "uByte: \t\t" << ub << "\n";
    std::cout << "Byte: \t\t" << b << "\n";
    std::cout << "uShort: \t"  << ush << "\n";
    std::cout << "Short: \t\t" << sh << "\n";
    std::cout << "uInt: \t\t" << ui << "\n";
    std::cout << "Int: \t\t" << i << "\n";
    //  std::cout << "uLong: \t\t" << ul << "\n";
    //  std::cout << "Long: \t\t" << l << "\n";
    std::cout << "string: \t" << "(" << str.size() << ")" << str << "-\n";
    std::cout << "float: \t\t" << f << "\n";
    std::cout << "double: \t" << d << "\n";

    std::cout << "\n";
    std::cout << "Stream Current Size: " << ds.getCurrentSize() << "\n";
    std::cout << "Stream Bytes Filled: " << ds.getBytesFilled() << "\n";
    std::cout << "Stream Bytes Read: " << ds.getBytesRead() << "\n";

  }

  catch (IOException ioe) {
    std::cerr << ioe.getMessage() << std::endl;
  }

  ////////////////////////////
  std::cout << "\n----\n\n";
  ////////////////////////////

    unsigned int bytes = ds.getBytesAvailToRead();
    unsigned char* myArray;
    myArray = new unsigned char[bytes];
	
    unsigned int bytesRead = ds.peakUCharArray(myArray, bytes);

    std::cout << "ByteStream(" << bytesRead << "): " << myArray << "\n";
    std::cout << "\n";
    std::cout << "Stream Current Size: " << ds.getCurrentSize() << "\n";
    std::cout << "Stream Bytes Filled: " << ds.getBytesFilled() << "\n";
    std::cout << "Stream Bytes Read: " << ds.getBytesRead() << "\n";

  ////////////////////////////
  std::cout << "\n----\n\n";
  ////////////////////////////


  ////////////////
  //De-Serialize 
  ////////////////

  try {
    bool nboo;
  
    unsigned char nub = ds.readUChar();
    char nb;
    ds >> nb;

    unsigned short nush = ds.readUShort();
    short nsh;
    ds >> nsh;

    unsigned int nui = ds.readUInt();
    int ni;
    ds >> ni;
    /*
      uLong nul;
      ds >> nul;
      Long nl;  
      ds >> nl;
    */

    std::string nmyStr;
    ds >> nmyStr;

    float nf; 
    ds >> nf;
    double nd;
    ds >> nd;


    ///////////////////////////
    std::cout << "uByte: \t\t" << nub << " (error= " << (ub - nub) << ")\n";
    std::cout << "Byte: \t\t" << nb << " (error= " << (b - nb) << ")\n";
    std::cout << "uShort: \t" << nush << " (error= " << (ush - nush) << ")\n";
    std::cout << "Short: \t\t" << sh << " (error= " << (sh - nsh) << ")\n";
    std::cout << "uInt: \t\t" << nui << " (error= " << (ui - nui) << ")\n";
    std::cout << "Int: \t\t" << ni << " (error= " << (i - ni) << ")\n";
    //  std::cout << "uLong: \t\t" << nul << " (error= " << (ul - nul) << ")\n";
    //  std::cout << "Long: \t\t" << nl << " (error= " << (l - nl) << ")\n";
    std::cout << "string: \t" << "(" << nmyStr.size() << ")" << nmyStr << "-\n";
    std::cout << "float: \t\t" << nf << " (error= " << (f - nf) << ")\n";
    std::cout << "double: \t" << nd << " (error= " << (d - nd) << ")\n";
	
    std::cout << "\n";
    std::cout << "Stream Current Size: " << ds.getCurrentSize() << "\n";
    std::cout << "Stream Bytes Filled: " << ds.getBytesFilled() << "\n";
    std::cout << "Stream Bytes Read: " << ds.getBytesRead() << "\n";
  }

  catch (IOException ioe) {
    std::cerr << ioe.getMessage() << std::endl;
  }

  delete pds;

  ////////////////////////////
  std::cout << "\n----\n\n";
  ////////////////////////////

  return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
