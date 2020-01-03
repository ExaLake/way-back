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
#include <fstream.h>
#include "FindPNS.h"

PseudoNameService_ptr FindPNS(CORBA::ORB_ptr orb, CORBA::Environment &IT_env) {
   char refstring[1024];
   ifstream is("PNS.dat");
   if (is) {
      is.get(refstring,1023);
      CORBA::Object_ptr objptr;
      objptr = orb->string_to_object(refstring,IT_env);

      if (IT_env.exception()) {
         cerr << "ERROR Initializing PseudoNameService"<< endl;
         exit(EXIT_FAILURE);
      }

      PseudoNameService_ptr obj = PseudoNameService::_narrow(objptr,
                                                             IT_env); 
      if (IT_env.exception()) {
         cerr << "ERROR Initializing PseudoNameService"<< endl;
         exit(EXIT_FAILURE);
      }

      return obj;
   }
   else {
      cerr << "Error finding pseudo nameservice reference" << endl;
      exit(EXIT_FAILURE);
   }
}
