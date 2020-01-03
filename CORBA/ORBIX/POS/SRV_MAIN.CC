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
#include <stdio.h>
#include "POS_OM.h"
#include "../PNS/FindPNS.h"

int main(int argc, char* argv[]) {
  if (argc<2) { // ###
    cerr << "usage: " << argv[0] << "<POS Number>" << endl;
    return 1;
  }

  CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"Orbix");
  CORBA::BOA_ptr boa = orb->BOA_init(argc,argv,"Orbix_BOA");

  POS::OutputMedia_var OutPut;
  PseudoNameService_var pns;
  
  try {
    pns=FindPNS(orb);
    OutPut = new OutputMedia_i(pns,atol(argv[1]));
    boa->impl_is_ready("OutputSrv");
  } // ###
  catch(...) {
    cerr << "ERROR Starting OutputMedia Server" << endl;
    return 1;
  }
  
  return 0;
}
