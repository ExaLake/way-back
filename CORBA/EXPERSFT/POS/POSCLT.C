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

#include "POS_IM.h"
#include "POS_Ter.h"
#include <FindPNS.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  if (argc<3) {
    cerr << "usage: " << argv[0] << "<Store Number> <POS Number>" << endl;
    return 1;
  }

  CORBA::ORB_ptr orb   = CORBA::ORB_init(argc,argv);
  CORBA::BOA_ptr boa   = orb->BOA_init(argc,argv,"");
  XpsBOA*        pboa  = XpsBOA::_narrow(boa);

  POS::POSTerminal_var  Ter;
  PseudoNameService_var pns;
  try {
    pns = FindPNS(orb);
    Ter = new POSTerminal_i(pns, argv[1], atol(argv[2]));
    pboa->obj_is_ready(Ter, nil);
  }
  catch(...) {
    cerr << "ERROR Starting POS Terminal Media" << endl;
    return 1;
  }


  POS::InputMedia_var InPut;
  char caBuff[255];

  try {
    InPut = new InputMedia_i(Ter);
    pboa->obj_is_ready(InPut, nil);
  }
  catch(...) {
    cerr << "Error starting InputMedia" << endl;
  }


  cout << "Command Summary :-" << endl;
  cout << "L : Login    P : POS Sales Summary    S : Store Sales Summary" << endl;
  cout << "T : Total    Q : Quantity             X : Exit" << endl << endl;
  do {
    cout << "Enter code, command (L,P,Q,S,T) or X to exit : ";
    try {
      cin.getline(caBuff,250);
      if ((caBuff[0] >= '0') && (caBuff[0] <= '9'))
        InPut->BarcodeInput(caBuff);
      else
        InPut->KeypadInput(caBuff);
    }
    catch(...) {
      cerr << "ERROR using Input Media" << endl;
      caBuff[0] = 'x';
    }
  } while (caBuff[0] != 'x' && caBuff[0] != 'X');

   return 0;
}
