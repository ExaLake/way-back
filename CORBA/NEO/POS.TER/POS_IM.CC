/********************************************************
 FILE: neo/POS.ter/pos_IM.cc

 DISCLAIMER: This code associated with this publication is intended to
 server solely as a programming example.  While this code is believed
 to be accurate, none of the Copyright holders makes any warranty of
 any kind for this code including but not limited to the implied
 warranties of merchantability and fitness for a particular purpose.
 None of the Copyright holders shall be liable for errors contained
 herein, or for incidental or consequential damages in connection with
 the furnishing, performance or use of this material at any time.

 Copyright 1995 by
  Object Management Group
  IONA Technologies, Ltd.
  Expersoft Inc.
  SunSoft, Inc.
  IBM Inc.
  Hewlett-Packard Company, Inc.
  International Computers Ltd.
  Digital Equipment Corporation
 All rights are reserved under the applicable copyright laws.

********************************************************/
#include "odf_output/OdfposcltImpl.hh"
#include <stream.h>
#include <stdlib.h>
#include <ctype.h>

void
InputMedia_i::_initialize_new_InputMedia(POS::POSTerminal_ptr pTer) {
   // we will communicate with the following terminal
   m_POSTerminalRef = pTer;
}

void  InputMedia_i:: barcode_input (const POS::Barcode item) {
  try {
    m_POSTerminalRef->send_barcode(item);
  }
  catch(...) {
    cerr << "Error in Sending barcode" << endl;
  }
}

void  InputMedia_i:: keypad_input (const POS::InputMedia::OperatorCmd cmd) {
  char * pStr = cmd;
  try {
    long lTot = 0;
    switch(toupper(*pStr)) {
      default : cerr << "Invalid entry" << endl;
                break;
      case 'X': break;
      case 'L': m_POSTerminalRef->login();
		break;
      case 'P': m_POSTerminalRef->print_POS_sales_summary();
		break;
      case 'S': m_POSTerminalRef->print_store_sales_summary();
		break;
      case 'T': m_POSTerminalRef->end_of_sale();
		break;
      case 'Q': while(*(++pStr) == ' ');
		lTot = atol(pStr);
		m_POSTerminalRef->item_quantity(lTot);
		break;
      }
  }
  catch(...) {
    cerr << "Error in transmitting command" << endl;
  }
}



