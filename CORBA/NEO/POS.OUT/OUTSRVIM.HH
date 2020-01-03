/********************************************************
 FILE: neo/posout/posImpl.hh

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
#ifndef _posout_IMPL_HH
#define _posout_IMPL_HH

#include <odf/odf.hh>
#include "pos.hh"
#include "store.hh"


#define InputMedia_ptr InputMediaRef
#define OutputMedia_ptr OutputMediaRef
#define POSTerminal_ptr POSTerminalRef
#define POSList_ptr POSList*

#define Tax_var TaxRef
#define Store_var StoreRef
#define StoreAccess_var StoreAccessRef
#define OutputMedia_var OutputMediaRef

#include "pos_OM.h"

#endif                          // _pos_IMPL_HH

