/********************************************************
 FILE: neo/POS.out/pos_OM.cc

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
#include "odf_output/OdfoutsrvImpl.hh"
#include <stream.h>

void
OutputMedia_i::_initialize_new_OutputMedia(PseudoNameService_ptr pns, POS::POSId Id ) {
  m_id=Id;
  // Register the object with the name service
  char refstring[1024];
  sprintf(refstring,"OutputMedia_%ld",m_id);
  try {
    pns->Bind(refstring,_servant_objref());
  }
  catch(...) {
    cerr << "Trouble Binding " << refstring << endl;
  }
}

boolean_t  OutputMedia_i:: output_text (char * const string_to_print ) {
  // Check if the string passed exists and if so, output it
  if (string_to_print)
    cout << string_to_print << endl;
  return B_TRUE;
}

