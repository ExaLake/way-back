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

#include "POS_IM.h"
#include "POS_Ter.h"
#include "../PNS/FindPNS.h"
#include <iostream.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
   if (argc<3) {
      cerr << "usage: " << argv[0] << "<Store Number> <POS Number>" << endl;
      return 1;
   }
   
   CORBA::Environment IT_env;
   CORBA::ORB_var orb = CORBA::ORB_init(argc,argv,CORBA::HPORBid,
                                        IT_env);
   if (IT_env.exception()) {
      cerr << "ERROR Initializing ORB" << endl;
      exit(EXIT_FAILURE);
   }

   CORBA::HPSOA_var soa = orb->HPSOA_init(argc,argv,CORBA::HPSOAid,
                                          IT_env);
   if (IT_env.exception()) {
      cerr << "ERROR Initializing HPSOA" << endl;
      exit(EXIT_FAILURE);
   }


   PseudoNameService_var pns=FindPNS(orb, IT_env);
   POSTerminal_i* Ter = new POSTerminal_i(pns,atol(argv[1]),
                                          atol(argv[2]), IT_env);
   POS::POSTerminal_var TerObj = Ter->_this();
   char caBuff[255];
   InputMedia_i* InPut = new InputMedia_i(TerObj);


   cout << "Command Summary :-" << endl;
   cout << "L : Login    P : POS Sales Summary    S : Store Sales Summary" << endl;
   cout << "T : Total    Q : Quantity             X : Exit" << endl << endl;
   do {
      cout << "Enter code, command (L,P,Q,S,T) or X to exit : ";

      cin.getline(caBuff,250);
      if ((caBuff[0] >= '0') && (caBuff[0] <= '9'))
         InPut->BarcodeInput(caBuff, IT_env);
      else
         InPut->KeypadInput(caBuff, IT_env);

   }while (caBuff[0] != 'x' && caBuff[0] != 'X');

   return 0;
}


