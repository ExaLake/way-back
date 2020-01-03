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

#include <iostream.h>
#include <stdio.h>
#include "POS_OM.h"
#include <stdlib.h>

OutputMedia_i::OutputMedia_i(PseudoNameService_ptr pns, POS::POSId Id,
			     CORBA::Environment& IT_env)
{
   m_id=Id;
   // Register the object with the name service
   char refstring[1024];
   sprintf(refstring,"OutputMedia_%ld",m_id);
   POS::OutputMedia_var OMObjRef = _this();
   pns->BindName(refstring, OMObjRef, IT_env);
   if (IT_env.exception()) {
      cerr << "Trouble Binding " << refstring << endl;
      exit(EXIT_FAILURE);
   }
}

CORBA::Boolean  OutputMedia_i:: OutputText (const char * StringToPrint, 
                                            CORBA::Environment &) 
{
   // Check if the string passed exists and if so, output it
   if (StringToPrint)
      cout << StringToPrint << endl;
   return 1;
}
