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

#ifndef pname_ih
#define pname_ih

#include <stdlib.h>
#include "PNSServer.hh"
#include "PNSData.h"

class pname_i : public virtual HPSOA_PseudoNameService {
  PNData m_data;
public:
  pname_i(CORBA::ORB_ptr orb);
  virtual void BindName (const char* ObjectName,CORBA::Object_ptr ObjectRef,
			 CORBA::Environment&);
  virtual CORBA::Object_ptr ResolveName (const char * ObjectName,
			 CORBA::Environment&);
};


#endif
