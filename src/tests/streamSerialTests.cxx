///////////////////////////////////////////////////////////
//
//        EXE entry point
//
///////////////////////////////////////////////////////////


#include <cstdlib>
#include <iostream>
#include <string>
#include "io/ByteArrayOutputStream.h"
#include "io/DataOutputStream.h"
#include "io/ByteArrayInputStream.h"
#include "io/DataInputStream.h"
#include "common/array.h"

int main(int argc, char* argv[])
{

  std::cout.precision(25);


  ////////////////
  //Serialize 
  ////////////////
 
  ////////////////////////////
  std::cout << "\n----\n\n";
  ////////////////////////////

  ByteArrayOutputStream* baos = new ByteArrayOutputStream();
  DataOutputStream* dos = new DataOutputStream(*baos);
 

  bool boo = false;

  unsigned char ub = 255;
  char b =   127;

  unsigned short ush = 65535;
  short sh =   32767;

  unsigned int ui = 4294967295;
  int i =   2147483647;

  unsigned long ul = 18446744073709551615;
  long l =    9223372036854775807;

  float f =  1234.567890123456789;
  double d = 1234.567890123456789;


  std::string str = "This is a test string for the serialization test!";
  

  dos->writeBoolean(boo);
  dos->writeUChar(ub);
  dos->writeChar(b);
  dos->writeUShort(ush);
  dos->writeShort(sh);
  dos->writeUInt(ui);
  dos->writeInt(i);
  dos->writeULong(ul);
  dos->writeLong(l);
  dos->writeFloat(f);
  dos->writeDouble(d);
  dos->writeString(str);

  delete dos;
  delete baos;

  array<unsigned char>* data = baos->toCharArray();

  /////////////////////////
  std::cout << boo << "\n";
  std::cout << ub << "\n";
  std::cout << b << "\n";
  std::cout << ush << "\n";
  std::cout << sh << "\n";
  std::cout << ui << "\n";
  std::cout << i << "\n";
  std::cout << ul << "\n";
  std::cout << l << "\n";
  std::cout << f << "\n";
  std::cout << d << "\n";
  std::cout << "(" << str.size() << ")" << str << "\n\n";


  std::cout << "Total stream length: " << data->size() << "\n";

  ////////////////////////////
  std::cout << "\n----\n\n";
  ////////////////////////////


  ////////////////
  //De-Serialize 
  ////////////////


  ByteArrayInputStream* bais = new ByteArrayInputStream(*data);
  DataInputStream* dis = new DataInputStream(*bais);

  bool nboo = dis->readBoolean();

  unsigned char nub = dis->readUChar();
  char nb =   dis->readChar();

  unsigned short nush = dis->readUShort();
  short nsh =   dis->readShort();

  unsigned int nui = dis->readUInt();
  int ni =   dis->readInt();

  unsigned long nul = dis->readULong();
  long nl =   dis->readLong();

  float nf = dis->readFloat();
  double nd = dis->readDouble();

  std::string nmyStr = dis->readString();


  ///////////////////////////
  std::cout << nboo << " (error= " << (boo - nboo) << ")\n";
  std::cout << nub << " (error= " << (ub - nub) << ")\n";
  std::cout << nb << " (error= " << (b - nb) << ")\n";
  std::cout << nush << " (error= " << (ush - nush) << ")\n";
  std::cout << nsh << " (error= " << (sh - nsh) << ")\n";
  std::cout << nui << " (error= " << (ui - nui) << ")\n";
  std::cout << ni << " (error= " << (i - ni) << ")\n";
  std::cout << nul << " (error= " << (ul - nul) << ")\n";
  std::cout << nl << " (error= " << (l - nl) << ")\n";
  std::cout << nf << " (error= " << (f - nf) << ")\n";
  std::cout << nd << " (error= " << (d - nd) << ")\n";
  std::cout << "(" << nmyStr.size() << ")" << nmyStr << "\n\n";

  delete data;
  delete bais;
  delete dis;

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
