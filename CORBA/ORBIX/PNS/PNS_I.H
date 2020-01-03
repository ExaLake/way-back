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


#ifndef pname_ih
#define pname_ih

#include "PNS.hh"
#include "PNSData.h"

class pname_i : public virtual PseudoNameServiceBOAImpl {
  PNData m_data;
public:
  pname_i(CORBA::ORB_ptr orb);
  virtual void BindName (const char* ObjectName, CORBA::Object_ptr ObjectRef,
  CORBA::Environment &IT_env= CORBA::default_environment);
  virtual CORBA::Object_ptr ResolveName (const char* ObjectName, CORBA::Environment
  &IT_env= CORBA::default_environment);
};


#endif
