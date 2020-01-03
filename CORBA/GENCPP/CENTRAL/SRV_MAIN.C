/*

Copyright (C) 1996 by the Object Management Group, Inc.  All  
rights reserved.  

Permission to use, copy, modify, and distribute this software for
any teaching or instructional purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that copyright notice and this permission
notice appear in supporting documentation, and that the names of
Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
(Wiley) not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
assume any liability of any alleged or actual damages arising
from the use of or the inability to use this software.  (Some
states do not allow the exclusion of implied warranties, so the
exclusion may not apply to you.)

*/
#include <FindPNS.h>
#include <Depot_i.h>

int
main(int argc, char** argv)
{
  CORBA::ORB_ptr orb  = CORBA::ORB_init(argc, argv);
  CORBA::BOA_ptr boa  = orb->BOA_init(argc, argv,"");

  CentralOffice::Depot_var dep1;
  PseudoNameService_var pns;
  
  try
  {
    pns=FindPNS(orb);
    dep1 = new Depot_i(pns);
    boa->obj_is_ready(dep1,nil);
  }
  catch(...) {
     cerr << "ERROR Starting Depot Server" << endl;
     return 1;
  }

  return 0;
}
