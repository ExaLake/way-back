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

#ifndef pos_iter
#define pos_iter

#include "POSServer.hh"
#include "StoreServer.hh"
#include "PNSServer.hh"

// --------------------------POS Terminal ---------------------------
    class POSTerminal_i : public virtual HPSOA_POS::POSTerminal
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
      CORBA::Long		m_id;
      unsigned char LoggedIn();
      
    public:
      POSTerminal_i(PseudoNameService_ptr pns, CORBA::Long StoreId,
                    POS::POSId id, CORBA::Environment &IT_env);

      virtual void Login (CORBA::Environment &IT_env);

      virtual void PrintPOSSalesSummary (CORBA::Environment &IT_env );

      virtual void PrintStoreSalesSummary (CORBA::Environment &IT_env);

      virtual void SendBarcode (const char* item, CORBA::Environment &IT_env);

      virtual void ItemQuantity (CORBA::Long Quantity,
				 CORBA::Environment &IT_env);

      virtual void EndOfSale (CORBA::Environment &IT_env);
    };


#endif
