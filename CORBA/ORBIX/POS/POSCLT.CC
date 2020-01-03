/*

Copyright (C) 1996 by Iona Technologies. All rights reserved.

Permission to use, copy, modify, and distribute this software for any
teaching or instructional purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that both
that copyright notice and this permission notice appear in supporting
documentation, and that the name of Iona Technologies Ltd. not be used in
advertising or publicity pertaining to distribution of the software without
specific, written prior permission.

THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTY OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Iona Technologies
Ltd. assume no liability of any alleged or actual damages arising from the
use of or the inability to use this software.

*/

#include <iostream.h>
#include <stdlib.h>
#include "POS_IM.h"
#include "POS_Ter.h"
#include "../PNS/FindPNS.h"

int main(int argc, char **argv)
{
  if (argc<3) {
    cerr << "usage: " << argv[0] << "<Store Number> <POS Number>" << endl;
    return 1;
  }
  CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"Orbix");
  CORBA::BOA_ptr boa = orb->BOA_init(argc,argv,"Orbix_BOA");
  
  POS::POSTerminal_var Ter;
  PseudoNameService_var pns;

//  CORBA::Orbix.setDiagnostics(2);
  try {
    pns=FindPNS(orb);
    Ter = new POSTerminal_i(pns,atol(argv[1]),atol(argv[2]));
  }
  catch(...) {
    cerr << "ERROR Starting POS Terminal" << endl;
    return 1;
  }

  POS::InputMedia_var InPut;
  char caBuff[255];
  
  try {
    InPut = new InputMedia_i(Ter);
  }
  catch(...) {
    cerr << "Error starting InputMedia" << endl;
    return 1;
  }

  cout << "Command Summary :-" << endl;
  cout << "L : Login   P : POS Sales Summary   S : Store Sales Summary" << endl;
  cout << "T : Total   Q : Quantity            X : Exit" <<  endl;
  cout << "<barcode> : Item " << endl << endl;
  do {
    cout << "Enter barcode, command (L,P,Q,S,T) or X to exit : ";
    try {
      cin.getline(caBuff,250);
      if ((caBuff[0] >= '0') && (caBuff[0] <= '9'))
        InPut->BarcodeInput(caBuff);
      else
        InPut->KeypadInput(caBuff);
    }
    catch(...) {
      cerr << "ERROR using Input Media" << endl;
      return 1;
    }
  }while (caBuff[0] != 'x' && caBuff[0] != 'X');

  return 0;
}
