/********************************************************
 FILE: neo/store/Svr_Main.cc

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
#include "odf_output/OdfstoreImpl.hh"
#include <stream.h>
#include <stdlib.h>
#include <stdio.h>
#include "pnsfind.h"

int main(int argc, char* argv[])
{
  ODF::init( argv[0] );
  CORBA::ORB_var orb = ODF::orb();
  if (argc != 3) {
    cerr << "usage: " << argv[0] << "<Store id> <Markup>" << endl;
    return 1;
  }
  
  AStore::Tax_var tax1;
  AStore::Store_var store1;
  PseudoNameService_var pns;

  try {
    pns=FindPNS(orb);
    tax1 = OdfTax_i::new_Tax(pns);
    store1 = OdfStore_i::new_Store(pns,atof(argv[1]),atol(argv[2]));
  }
  catch(...) {
    cerr << "ERROR Starting Store Server" << endl;
    return 1;
  }

  // wait some input to terminate
  cout << "Store server running. Press <Return> to terminate." << endl;
  getchar();
  store1->_release();
  tax1->_release();
  return 0;
}

