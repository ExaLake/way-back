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

#ifndef store_ih
#define store_ih

#include "StoreServer.hh"
#include "POSServer.hh"
#include "CentralServer.hh"
#include "PNSServer.hh"

class Tax_i: public virtual HPSOA_AStore::Tax {
  CORBA::Float m_regionRate;
public:
   Tax_i(PseudoNameService_ptr pns, AStore::AStoreId StoreId,
         CORBA::Environment&);
   virtual CORBA::Float CalculateTax (CORBA::Float TaxableAmount,
       CORBA::Environment&);
   virtual CORBA::Float FindTaxablePrice (CORBA::Float ItemPrice,
					  AStore::ItemTypes ItemType,
					  CORBA::Environment&);
};

class Store_i : public virtual HPSOA_AStore::Store {
   AStore::AStoreId          m_storeId;
   CORBA::Float              m_storeTotal;
   CORBA::Float              m_storeTaxTotal;
   CORBA::Float              m_storeMarkup;
   AStore::POSList           m_POSTerminals;
   PseudoNameService_var     m_pns;
   virtual CORBA::ULong Store_i::LocatePOSEntry(POS::POSId Id);
public:
    Store_i(PseudoNameService_ptr pns,
            AStore::AStoreId StoreId, CORBA::Float StoreMarkup,
	    CORBA::Environment&);
    virtual AStore::AStoreId StoreId (CORBA::Environment&);
    virtual AStore::Store::StoreTotals Totals (CORBA::Environment&);
    virtual AStore::StoreAccess* Login (POS::POSId id,
   		 CORBA::Environment &IT_env);
    virtual void GetPOSTotals (AStore::POSList* &POSData, CORBA::Environment&);
    virtual void UpdateStoreTotals (POS::POSId Id, CORBA::Float Price,
   		 CORBA::Float Taxes, CORBA::Environment&);
};

class StoreAccess_i : public virtual HPSOA_AStore::StoreAccess {
   CentralOffice::Depot_var  m_depot;
   AStore::Tax_var           m_tax;
   AStore::Store_var	     m_store;
   CORBA::Float              m_storeMarkup;
public:
  StoreAccess_i(PseudoNameService_ptr pns, AStore::Store_ptr pStore,
                CORBA::Float StoreMarkup,
                CORBA::Environment &IT_env);

  ~StoreAccess_i() {}

  virtual void FindPrice (const char* Item, CORBA::Long Quantity,
 		 CORBA::Float& ItemPrice,
		 CORBA::Float& ItemTaxPrice, AStore::ItemInfo*& IInfo,
		 CORBA::Environment &IT_env);
};

#endif
