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

#ifndef pos_iom
#define pos_iom

#include "POSServer.hh"
#include "PNSServer.hh"

//------------------ Output Media ------------------------------------------

    class OutputMedia_i : public virtual HPSOA_POS::OutputMedia {
      POS::POSId m_id;
    public:
      OutputMedia_i(PseudoNameService_ptr pns, POS::POSId Id,
		    CORBA::Environment&);
      virtual CORBA::Boolean OutputText (const char * StringToPrint,
					 CORBA::Environment&);
    };


#endif
