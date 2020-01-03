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

#ifndef pos_iim
#define pos_iim

#include "POSServer.hh"

    class InputMedia_i :public virtual HPSOA_POS::InputMedia {
      POS::POSTerminal_ptr m_POSTerminalRef;
    public:
      InputMedia_i(POS::POSTerminal_ptr pTer);

      virtual void BarcodeInput (const char* Item, 
                                  CORBA::Environment &IT_env);
      virtual void KeypadInput (const char* Cmd, 
                                  CORBA::Environment &IT_env);
    };

#endif
