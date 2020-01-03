/********************************************************
 FILE: neo/POS.out/pos_OM.h

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
#ifndef pos_iom
#define pos_iom

#include "../compat.hh"
#include "pos.hh"
#include "pnamesvc.hh"

//------------------ Output Media ------------------------------------------

    class OutputMedia_i: public virtual ODF::Servant {
      POS::POSId m_id;
    public:
      void _initialize_new_OutputMedia (PseudoNameService_ptr pns, POS::POSId pos_id );

      CORBA::Boolean output_text (char* const string_to_print);
    };


#endif
