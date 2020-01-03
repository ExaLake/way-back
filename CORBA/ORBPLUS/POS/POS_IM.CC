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
#include <stdlib.h>
#include <ctype.h>
#include "POS_IM.h"

InputMedia_i::InputMedia_i(POS::POSTerminal_ptr pTer) {
   // we will communicate with the following terminal
   m_POSTerminalRef = POS::POSTerminal::_duplicate(pTer);
}

void  InputMedia_i:: BarcodeInput (const char* item,
                                    CORBA::Environment &IT_env) {
   m_POSTerminalRef->SendBarcode(item, IT_env);
}

void  InputMedia_i:: KeypadInput (const char* Cmd, 
                                   CORBA::Environment &IT_env) {
   char * pStr = (char*)Cmd;
   long lTot = 0;
   switch(toupper(*pStr)) {
   default : cerr << "Invalid entry" << endl;
      break;
   case 'X': break;
   case 'L': m_POSTerminalRef->Login(IT_env);
      break;
   case 'P': m_POSTerminalRef->PrintPOSSalesSummary(IT_env);
      break;
   case 'S': m_POSTerminalRef->PrintStoreSalesSummary(IT_env);
      break;
   case 'T': m_POSTerminalRef->EndOfSale(IT_env);
      break;
   case 'Q': while(*(++pStr) == ' ');
      lTot = atol(pStr);
      m_POSTerminalRef->ItemQuantity(lTot, IT_env);
      break;
   }
   if (IT_env.exception())
          cerr << "Error in transmitting command" << endl;
}



