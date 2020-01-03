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

#ifndef pos_iter
#define pos_iter

#include "POS.hh"
#include "Store.hh"
#include "PNS.hh"

// --------------------------POS Terminal ---------------------------
    class POSTerminal_i : public virtual POS::POSTerminalBOAImpl
    {
    private:
      POS::Barcode 		m_itemBarcode;
      CORBA::Long 		m_itemQuantity;
      AStore::Tax_var		m_taxRef;
      AStore::Store_var		m_storeRef;
      AStore::StoreAccess_var	m_storeAccessRef;
      POS::OutputMedia_var	m_outputMediaRef;
      CORBA::Float		m_saleSubTotal;
      CORBA::Float		m_saleTaxableSubTotal;
      CORBA::Float		m_POSTotal;
      CORBA::Float		m_POSTaxTotal;
      POS::POSId		m_id;
      unsigned char LoggedIn();   // returns Boolean
      
    public:
      POSTerminal_i(PseudoNameService_ptr pns, CORBA::Long StoreId,
                    POS::POSId id);

      virtual void Login (CORBA::Environment &IT_env=CORBA::default_environment);

      virtual void PrintPOSSalesSummary (CORBA::Environment
      &IT_env=CORBA::default_environment);

      virtual void PrintStoreSalesSummary (CORBA::Environment
      &IT_env=CORBA::default_environment);

      virtual void SendBarcode (const char* Item, CORBA::Environment
      &IT_env=CORBA::default_environment);   // ###

      virtual void ItemQuantity (CORBA::Long Quantity, CORBA::Environment
      &IT_env=CORBA::default_environment);

      virtual void EndOfSale (CORBA::Environment &IT_env=CORBA::default_environment);
    };


#endif
