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
#include <iostream.h>
#include <stdlib.h>
#include <ctype.h>
#include <### Store interface header file>
#include "POS_IM.h"

InputMedia_i::InputMedia_i(POS::POSTerminal_ptr pTer)
{
   // we will comunicate with the following terminal
   m_POSTerminalRef = POS::POSTerminal::_duplicate(pTer);
}

void  InputMedia_i:: BarcodeInput (const char * Item)
{
  try
  {
     m_POSTerminalRef->SendBarcode(Item);
  }
  catch (const AStore::BarcodeNotFound &bce)
  {
     cerr << "Error in Sending barcode" << endl;
  }
}

void  InputMedia_i:: KeypadInput (const char *Cmd)
{
   char * pStr = (char *) Cmd;
   try
   {
    long lTot = 0;
    switch(toupper(*pStr)) {
      default : cerr << "Invalid entry" << endl;
                break;
      case 'X': break;
      case 'L': m_POSTerminalRef->Login();
                break;
      case 'P': m_POSTerminalRef->PrintPOSSalesSummary();
                break;
      case 'S': m_POSTerminalRef->PrintStoreSalesSummary();
                break;
      case 'T': m_POSTerminalRef->EndOfSale();
                break;
      case 'Q': while(*(++pStr) == ' ');
                lTot = atol(pStr);
                m_POSTerminalRef->ItemQuantity(lTot);
                break;
      }
  }
  catch(...) {
    cerr << "Error in transmitting command" << endl;
  }
  
}
