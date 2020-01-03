/*

Copyright (C) 1996 by the Object Management Group, Inc.  All  
rights reserved.  

Permission to use, copy, modify, and distribute this software for
any teaching or instructional purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that copyright notice and this permission
notice appear in supporting documentation, and that the names of
Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
(Wiley) not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
assume any liability of any alleged or actual damages arising
from the use of or the inability to use this software.  (Some
states do not allow the exclusion of implied warranties, so the
exclusion may not apply to you.)

*/
#include "PNS_i.h"
#include "### Store interface header file"
#include <fstream.h>

pname_i::pname_i(CORBA::ORB_ptr orb)
{
  ofstream os("PNS.dat");
  if (os) {
    char *refstring = orb->object_to_string( _this());
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
