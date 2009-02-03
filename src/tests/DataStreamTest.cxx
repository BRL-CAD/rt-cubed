///////////////////////////////////////////////////////////
//
//        EXE entry point
//
///////////////////////////////////////////////////////////


#include <cstdlib>
#include <iostream>
#include <string>
#include "io/DataStream.h"

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

  uByte ub = 255;
  Byte b =   127;

  uShort ush = 65535;
  Short sh =   32767;

  uInt ui = 4294967295;
  Int i =   2147483647;

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
    ds << f;
    ds << d;
    ds << str;


    /////////////////////////
    std::cout << "uByte: \t\t" << ub << "\n";
    std::cout << "Byte: \t\t" << b << "\n";
    std::cout << "uShort: \t"  << ush << "\n";
    std::cout << "Short: \t\t" << sh << "\n";
    std::cout << "uInt: \t\t" << ui << "\n";
    std::cout << "Int: \t\t" << i << "\n";
    //  std::cout << "uLong: \t\t" << ul << "\n";
    //  std::cout << "Long: \t\t" << l << "\n";
    std::cout << "float: \t\t" << f << "\n";
    std::cout << "double: \t" << d << "\n";
    std::cout << "string: \t" << "(" << str.size() << ")" << str << "\n\n";


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


  ////////////////
  //De-Serialize 
  ////////////////

  try {
    bool nboo;
  
    uByte nub;
    ds >> nub;
    Byte nb;
    ds >> nb;

    uShort nush;
    ds >> nush;
    Short nsh;
    ds >> nsh;

    uInt nui;
    ds >>  nui;
    Int ni;
    ds >> ni;
    /*
      uLong nul;
      ds >> nul;
      Long nl;  
      ds >> nl;
    */
    float nf; 
    ds >> nf;
    double nd;
    ds >> nd;

    String nmyStr;
    ds >> nmyStr;

    ///////////////////////////
    std::cout << "uByte: \t\t" << nub << " (error= " << (ub - nub) << ")\n";
    std::cout << "Byte: \t\t" << nb << " (error= " << (b - nb) << ")\n";
    std::cout << "uShort: \t" << nush << " (error= " << (ush - nush) << ")\n";
    std::cout << "Short: \t\t" << sh << " (error= " << (sh - nsh) << ")\n";
    std::cout << "uInt: \t\t" << nui << " (error= " << (ui - nui) << ")\n";
    std::cout << "Int: \t\t" << ni << " (error= " << (i - ni) << ")\n";
    //  std::cout << "uLong: \t\t" << nul << " (error= " << (ul - nul) << ")\n";
    //  std::cout << "Long: \t\t" << nl << " (error= " << (l - nl) << ")\n";
    std::cout << "float: \t\t" << nf << " (error= " << (f - nf) << ")\n";
    std::cout << "double: \t" << nd << " (error= " << (d - nd) << ")\n";
    std::cout << "string: \t" << "(" << nmyStr.size() << ")" << nmyStr << "\n\n";

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
