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

#include <fstream.h>

#include "FindPNS.h"

PseudoNameService_ptr FindPNS(CORBA::ORB_ptr orb)
{
   char refstring[1024];
   ifstream is("PNS.dat");
   if (is) {
      is.get(refstring,1023);
      PseudoNameService_ptr pns = PseudoNameService::_narrow(orb->string_to_object(refstring));
      return pns;
   }
   else {
      cerr << "Error finding pseudo nameservice reference" << endl;
      return PseudoNameService::_nil();
   }
}
