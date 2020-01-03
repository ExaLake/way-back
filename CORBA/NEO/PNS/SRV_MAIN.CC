/********************************************************
 FILE: neo/PNS/Srv_Main.cc

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
#include "odf_output/OdfpnameImpl.hh"
#include <stream.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  ODF::init( argv[0] );
  CORBA::ORB_var orb = ODF::orb();

  PseudoNameService_var PNS1;
  
  try {
    PNS1 = Odfpname_i::new_pname(orb);
  }
  catch(...) {
    cerr << "Error Starting Pseudo Nameserver" << endl;
    return 1;
  }

  // wait some input to terminate
  cout << "Pseudo Name Server running. Press <Return> to terminate." << endl;
  getchar();
  PNS1->_release();
  return 0;
}
