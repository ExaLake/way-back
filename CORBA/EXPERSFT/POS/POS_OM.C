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

#include <stdio.h>
#include "POS_OM.h"
#include <FindPNS.h>

//----------------------------------------------------------------------------------
// OutputMedia Member Functions
//----------------------------------------------------------------------------------

OutputMedia_i::OutputMedia_i(PseudoNameService_ptr pns
                            ,POS::POSId Id)
{
  // Register the object with the name service
  char refstring[1024];
  sprintf(refstring,"OutputMedia_%ld",Id);
  try
  {
     pns->BindName(refstring,_this());
  }
  catch (...)
  {
     cerr << "Trouble Binding " << refstring << endl;
  }
}

CORBA::Boolean OutputMedia_i:: OutputText (const char * StringToPrint)
{
  // Check if the string passed exists and if so, output it
  if (StringToPrint)
     cout << StringToPrint << endl;
  return CORBA::TRUE;
}
