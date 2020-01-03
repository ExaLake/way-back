//(c) Copyright 1996 HEWLETT-PACKARD COMPANY
//          
//   To anyone who acknowledges that this file is provided "AS IS" 
//   WITH NO EXPRESS OR IMPLIED WARRANTY:
//   permission to use, copy, modify, and distribute this file for any 
//   purpose is hereby granted without fee, provided that the above 
//   copyright notice and this notice appear in all copies, and that 
//   the name of Hewlett-Packard Company not be used in advertising or 
//   publicity pertaining to distribution of the software without 
//   specific, written prior permission.  Hewlett-Packard Company 
//   makes no representations about the suitability of this software 
//   for any purpose.

#include <stdlib.h>
#include <iostream.h>
#include <stdio.h>
#include "Depot_i.h"
#include "../PNS/FindPNS.h"

int main(int argc, char* argv[]) {
   CORBA::Environment IT_env;
   CORBA::ORB_var orb = CORBA::ORB_init(argc,argv,CORBA::HPORBid,
                                        IT_env);
   if (IT_env.exception()) {
      cerr << "ERROR Initializing ORB"<< endl;
      exit(EXIT_FAILURE);
   }

   CORBA::HPSOA_var soa = orb->HPSOA_init(argc,argv,CORBA::HPSOAid,
                                          IT_env);
   if (IT_env.exception()) {
      cerr << "ERROR Initializing HPSOA"<< endl;
      exit(EXIT_FAILURE);
   }

   PseudoNameService_var PNS=FindPNS(orb,IT_env);   

   Depot_i dep1(PNS, IT_env);

   cout <<"central server up "<<endl;
   soa->run();
   return 0;
}
