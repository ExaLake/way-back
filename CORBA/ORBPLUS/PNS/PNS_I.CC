//(c) Copyright 1996 HEWLETT-PACKARD COMPANY
//          
//   To anyone who acknowledges that this file is provided "AS IS" 
//   WITH NO EXPRESS OR IMPLIED WARRANTY:
//   permission to use, copy, modify, and distribute this file for any 
//   purpose is hereby granted without fee, provided that the above 
//   copyright notice and this notice appear in all copies, and that 
//   the name of Hewlett-Packard Company not be used in advertising or 
//   publicity pertaining to distribution of the software without 
//   specific, written prior permission.  Hewlett-Packard Company 
//   makes no representations about the suitability of this software 
//   for any purpose.

#include <iostream.h>
#include <fstream.h>
#include "PNS_i.h"

pname_i::pname_i(CORBA::ORB_ptr orb) {
  ofstream os("PNS.dat");
  if (os) {
    PseudoNameService_var PNSObjRef = _this();
    char *refstring = orb->object_to_string(PNSObjRef);
    os << refstring;
    CORBA::string_free(refstring);
  }
  else {
    cerr << "Error writing Pseudo Name-Service object reference" << endl;
  }
}

void pname_i::BindName (const char * ObjectName,
			 CORBA::Object_ptr ObjectRef,
			 CORBA::Environment&) {
  m_data.Insert(ObjectName,CORBA::Object::_duplicate(ObjectRef));
  cout << "Registering object " << ObjectName << endl;
}

CORBA::Object_ptr pname_i::ResolveName (const char * ObjectName,
			 CORBA::Environment&) {
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

