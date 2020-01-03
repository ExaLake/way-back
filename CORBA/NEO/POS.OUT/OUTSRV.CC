/********************************************************
 FILE: neo/POS.out/outsrv.cc

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
#include "odf_output/OdfoutsrvImpl.hh"
#include <stream.h>
#include <stdlib.h>
#include <stdio.h>
#include "pnsfind.h"


int main(int argc, char* argv[]) {
  ODF::init( argv[0] );
  CORBA::ORB_var orb = ODF::orb();

  POS::OutputMedia_var OutPut;
  PseudoNameService_var pns;

  if (argc < 2) {
    cerr << "usage: " << argv[0] << "<POS Id>" << endl;
    return 1;
  }

  try {
    pns=FindPNS(orb);
    
    OutPut = OdfOutputMedia_i::new_OutputMedia(pns,atol(argv[1]));
  }
  catch(...) {
    cerr << "ERROR Starting OutputMedia Server" << endl;
    return 1;
  }

  // wait some input to terminate
  cout << "OutputMedia Server running. Press <Return> to terminate." << endl;
  getchar();
  OutPut->_release();
  return 0;
}

