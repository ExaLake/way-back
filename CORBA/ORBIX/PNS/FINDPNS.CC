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
#include <fstream.h>
#include "FindPNS.h"

PseudoNameService_ptr FindPNS(CORBA::ORB_ptr orb) {
  char refstring[1024];
  ifstream is("PNS.dat");
  if (is) {
    is.get(refstring,1023);
    return PseudoNameService::_narrow(orb->string_to_object(refstring));
  }
  else {
    cerr << "Error finding pseudo nameservice reference" << endl;
    return PseudoNameService::_nil();
  }
}
