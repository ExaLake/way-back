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

#include "PNS_i.h"
#include "Store.h"
#include <fstream.h>

pname_i::pname_i(CORBA::ORB_ptr orb)
{
  ofstream os("PNS.dat");
  if (os) {
    char *refstring = orb->object_to_string( this ); //_this());
    os << refstring;
    CORBA::string_free(refstring);
  }
  else {
    cerr << "Error writing Pseudo Name-Service object reference" << endl;
  }
}

void pname_i:: BindName (const char * ObjectName,
		     CORBA::Object_ptr ObjectRef)
{
  cerr << "pname_i::BindName - registering " << ObjectName << endl;
  m_data.insert(ObjectName,
                CORBA::Object::_duplicate(ObjectRef));
}

CORBA::Object_ptr pname_i:: ResolveName (const char * ObjectName)
{
  cerr << "pname_i::ResolveName - looking up " << ObjectName << endl;
  CORBA::Object_ptr p;
  if (m_data.locate(ObjectName,p))
     return CORBA::Object::_duplicate(p);
  else
     return CORBA::Object::_nil();
}
