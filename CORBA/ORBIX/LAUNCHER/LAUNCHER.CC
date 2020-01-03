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

#include <PNS.hh>
#include <POS.hh>
#include <Central.hh>
#include <Store.hh>
#include <iostream.h>
#include <unistd.h>

main() {


  try {
    PseudoNameService::_bind(":PNSSrv","");
    cout << "PNS Started" << endl;
    sleep(8);

    CentralOffice::Depot::_bind(":CentralSrv","");
    cout << "CentralSrv Started" << endl;
    sleep(8);

    AStore::Store::_bind(":StoreSrv","");
    cout << "StoreSrv started" << endl;
    POS::OutputMedia::_bind(":OutputSrv","");
    cout << "All started" << endl;
  }
  catch(...) {
    cerr << "Error starting a server" << endl;
  }

  return 0;
}
