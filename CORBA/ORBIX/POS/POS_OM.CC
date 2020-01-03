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
#include <stdio.h>
#include "POS_OM.h"

OutputMedia_i::OutputMedia_i(PseudoNameService_ptr pns, POS::POSId Id)
{
  m_id=Id;
  // Register the object with the name service
  char refstring[1024];
  sprintf(refstring,"OutputMedia_%ld",m_id);
  try {
    pns->BindName(refstring,this);
  }
  catch(...) {
    cerr << "Trouble Binding " << refstring << endl;
  }
}

CORBA::Boolean OutputMedia_i:: OutputText (const char* StringToPrint,
CORBA::Environment &IT_env)
{
  // Check if the string passed exists and if so, output it
  if (StringToPrint)
    cout << StringToPrint << endl;
  return 1;
}
