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
#include "PNS_i.h"

pname_i::pname_i(CORBA::ORB_ptr orb) {
  ofstream os("PNS.dat");
  if (os) {
    char* refstring = orb->object_to_string(this);
    os << refstring;
    CORBA::string_free(refstring);
  }
  else {
    cerr << "Error writing Pseudo Name-Service object reference" << endl;
  }
}

void pname_i:: BindName (const char* ObjectName,
		     CORBA::Object_ptr ObjectRef,
		     CORBA::Environment &IT_env) {
  m_data.Insert(ObjectName,CORBA::Object::_duplicate(ObjectRef));
  cout << "Registering object " << ObjectName << endl;
}

CORBA::Object_ptr pname_i:: ResolveName (const char* ObjectName,
		     CORBA::Environment &IT_env) {
  cout << "Looking for object " << ObjectName << endl;
  CORBA::Object_ptr p;
  if (m_data.Locate(ObjectName,p)) {
   cout << "found it" << endl;
   return CORBA::Object::_duplicate(p);
  }
  else
  {
    cout << "failed to find object" << endl;
    return CORBA::Object::_nil();
    }
}
