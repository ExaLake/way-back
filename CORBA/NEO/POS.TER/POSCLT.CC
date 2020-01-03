/********************************************************
 FILE: neo/POS.ter/posclt.cc

 DISCLAIMER: This code associated with this publication is intended to
 server solely as a programming example.  While this code is believed
 to be accurate, none of the Copyright holders makes any warranty of
 any kind for this code including but not limited to the implied
 warranties of merchantability and fitness for a particular purpose.
 None of the Copyright holders shall be liable for errors contained
 herein, or for incidental or consequential damages in connection with
 the furnishing, performance or use of this material at any time.

 Copyright 1995 by
  Object Management Group
  IONA Technologies, Ltd.
  Expersoft Inc.
  SunSoft, Inc.
  IBM Inc.
  Hewlett-Packard Company, Inc.
  International Computers Ltd.
  Digital Equipment Corporation
 All rights are reserved under the applicable copyright laws.

********************************************************/

#include <iostream.h>
#include "odf_output/OdfposcltImpl.hh"
#include "pnsfind.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  ODF::init( argv[0] );
  CORBA::ORB_var orb = ODF::orb();

  if (argc<3) {
    cerr << "usage: " << argv[0] << "<Store Number> <POS Number>" << endl;
    return 1;
  }

  POS::POSTerminal_var Ter;
  PseudoNameService_var pns;

  try {
    pns=FindPNS(orb);
    Ter = OdfPOSTerminal_i::new_POSTerminal(pns,atol(argv[1]),atol(argv[2]));
  }
  catch(...) {
    cerr << "ERROR Starting POS Terminal" << endl;
    return 1;
  }

  POS::InputMedia_var InPut;
  char caBuff[255];
  
  try {
    InPut = OdfInputMedia_i::new_InputMedia( Ter );
  }
  catch(...) {
    cerr << "Error starting InputMedia" << endl;
    return 1;
  }

  cout << "Command Summary :-" << endl;
  cout << "L : Login    P : POS Sales Summary    S : Store Sales Summary" << endl;
  cout << "T : Total    Q : Quantity             X : Exit" << endl << endl;
  do {
    cout << "Enter code, command (L,P,Q,S,T) or X to exit : ";
    try {
      cin.getline(caBuff,250);
      if ((caBuff[0] >= '0') && (caBuff[0] <= '9'))
        InPut->barcode_input(caBuff);
      else
        InPut->keypad_input(caBuff);
    }
    catch(...) {
      cerr << "ERROR using Input Media" << endl;
      return 1;
    }
  }while (caBuff[0] != 'x');

  Ter->_release();
  InPut->_release();
  return 0;
}
