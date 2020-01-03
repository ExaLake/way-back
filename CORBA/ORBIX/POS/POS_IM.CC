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
#include <ctype.h>
#include "POS_IM.h"

InputMedia_i::InputMedia_i(POS::POSTerminal_ptr pTer) {
   // we will communicate with the following terminal
   m_POSTerminalRef = POS::POSTerminal::_duplicate(pTer);
}

void  InputMedia_i:: BarcodeInput (const char* Item, CORBA::Environment &IT_env) {  // ###
  try {
    m_POSTerminalRef->SendBarcode(Item);
  }
  catch(...) {
    cerr << "Error in Sending barcode" << endl;
  }
}

void  InputMedia_i:: KeypadInput (const char* Cmd, CORBA::Environment &IT_env) {  // ###
  char* pStr = Cmd;
  CORBA::Environment env;
  try {
    long lTot = 0;
    switch(toupper(*pStr)) {
      default : cerr << "Invalid entry" << endl;
                break;
      case 'X': break;
      case 'L': 
		m_POSTerminalRef->Login(env);
		break;
      case 'P': m_POSTerminalRef->PrintPOSSalesSummary(env);
		break;
      case 'S': m_POSTerminalRef->PrintStoreSalesSummary(env);
		break;
      case 'T': m_POSTerminalRef->EndOfSale(env);
		break;
      case 'Q': while(*(++pStr) == ' ');
		lTot = atol(pStr);
		m_POSTerminalRef->ItemQuantity(lTot, env);
		break;
      }
  }
  catch(...) {
    cerr << "Error in transmitting command" << endl;
  }
}



