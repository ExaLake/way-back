/********************************************************
 FILE: neo/PNS/pname_i.cc

 DISCLAIMER: This code associated with this publication is intended to
 server solely as a programming example.  While this code is believed
 to be accurate, none of the Copyright holders makes any warranty of
 any kind for this code including but not limited to the implied
 warranties of merchantability and fitness for a particular purpose.
 None of the Copyright holders shall be liable for errors contained
 herein, or for incidental or consequential damages in connection with
 the furnishing, performance or use of this material at any time.

 Copyright 1995 by
  Object Management Group
  IONA Technologies, Ltd.
  Expersoft Inc.
  SunSoft, Inc.
  IBM Inc.
  Hewlett-Packard Company, Inc.
  International Computers Ltd.
  Digital Equipment Corporation
 All rights are reserved under the applicable copyright laws.

********************************************************/
#include "odf_output/OdfpnameImpl.hh"
#include <stream.h>


void pname_i::_initialize_new_pname(CORBA::ORB_ptr orb) {
  ofstream os("../PNS.dat");
  int argc=0;
  char **argv=0;
  if (os) {
    char *refstring = orb->object_to_string( _servant_objref() );
    os << refstring;
    CORBA::string_free(refstring);
  }
  else {
    cerr << "Error writing Pseudo Name-Service object reference" << endl;
  }
}

void pname_i:: Bind (const char * ObjectName,
		     CORBA::Object_ptr ObjectRef) {
  m_data.insert(ObjectName,ObjectRef->_duplicate());
  cout << "Registering object " << ObjectName << endl;
}

CORBA::Object_ptr pname_i:: Resolve (const char * ObjectName) {
  cout << "Looking for object " << ObjectName << endl;
  CORBA::Object_ptr p;
  if (m_data.locate(ObjectName,p)) {
    return p->_duplicate();
  }
  else return CORBA::Object::_null();
}
