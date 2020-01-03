/*

Copyright (c) 1995 Expersoft Corporation.  All Rights Reserved.  

Unlimited use, reproduction, and distribution of this software is
permitted.  Any copy of this software must include both the above
copyright notice of Expersoft Corporation and this paragraph.  Any
distribution of this software must comply with all applicable United
States export control laws.  This software is made available AS IS,
and EXPERSOFT CORPORATION DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE, AND NOTWITHSTANDING ANY OTHER
PROVISION CONTAINED HEREIN, ANY LIABILITY FOR DAMAGES RESULTING FROM
THE SOFTWARE OR ITS USE IS EXPRESSLY DISCLAIMED, WHETHER ARISING IN
CONTRACT, TORT (INCLUDING NEGLIGENCE) OR STRICT LIABILITY, EVEN IF
EXPERSOFT CORPORATION IS ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

*/

#include <iostream.h>
#include <stdlib.h>
#include <ctype.h>
#include <Store.h>
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
