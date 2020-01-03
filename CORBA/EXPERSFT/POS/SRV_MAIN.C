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

#include <pbroker/corba/orb.h>
#include <pbroker/corba/xpsboa.h>
#include <pbroker/unixsvc/unixsvc.h>

#include "POS_OM.h"
#include <stdio.h>
#include <stdlib.h>
#include <FindPNS.h>

int main(int argc, char* argv[])
{
  if (argc<2) {
     cerr << "usage: " << argv[0] << "<POS Number>" << endl;
     return 1;
  }

  CORBA::ORB_ptr orb   = CORBA::ORB_init(argc,argv);
  CORBA::BOA_ptr boa   = orb->BOA_init(argc,argv,"");
  XpsBOA*        pboa  = XpsBOA::_narrow(boa);

  POS::OutputMedia_var OutPut;
  PseudoNameService_var pns;

  try
  {
     pns=FindPNS(orb);
     OutPut = new OutputMedia_i(pns, atol(argv[1]));
     pboa->obj_is_ready(OutPut, nil);
  }
  catch (...)
  {
    cout << "ERROR Starting OutputMedia Server" << endl;
  }

  XpsEventService eventService;
  eventService.mainloop();

  return 0;
}
