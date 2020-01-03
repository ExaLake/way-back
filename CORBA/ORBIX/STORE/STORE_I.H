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

#ifndef store_ih
#define store_ih

#include "Store.hh"
#include "POS.hh"
#include "Central.hh"
#include "PNS.hh"

class Tax_i: public virtual AStore::TaxBOAImpl {
  CORBA::Float m_regionRate;
public:
   Tax_i(PseudoNameService_ptr pns,AStore::AStoreId StoreId);
   virtual CORBA::Float CalculateTax (CORBA::Float TaxableAmount,
  		 CORBA::Environment &IT_env=CORBA::default_environment);
   virtual CORBA::Float FindTaxablePrice (CORBA::Float ItemPrice,
  		 AStore::ItemTypes ItemType,
		 CORBA::Environment &IT_env=CORBA::default_environment);
};

class Store_i : public virtual AStore::StoreBOAImpl {
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
            CORBA::Environment &IT_env=CORBA::default_environment);
    virtual AStore::AStoreId StoreId (CORBA::Environment &IT_env=
		CORBA::default_environment);
    virtual AStore::Store::StoreTotals Totals (CORBA::Environment &IT_env=
						CORBA::default_environment);
    virtual AStore::StoreAccess* Login (POS::POSId Id,
   		 CORBA::Environment &IT_env= CORBA::default_environment);
    virtual void GetPOSTotals (AStore::POSList* &POSData,
   		 CORBA::Environment &IT_env=CORBA::default_environment);
    virtual void UpdateStoreTotals (POS::POSId Id, CORBA::Float Price,
   		 CORBA::Float Taxes,
		 CORBA::Environment &IT_env=CORBA::default_environment);
};

class StoreAccess_i : public virtual AStore::StoreAccessBOAImpl {
   CentralOffice::Depot_var  m_depot;
   AStore::Tax_var           m_tax;
   AStore::Store_var	     m_store;
   CORBA::Float              m_storeMarkup;
public:
  StoreAccess_i(PseudoNameService_ptr pns, AStore::Store_ptr pStore,
                CORBA::Float StoreMarkup,
                CORBA::Environment &IT_env=CORBA::default_environment);

  ~StoreAccess_i() {}   // ###
  
  virtual void FindPrice (const char* Item, CORBA::Long Quantity,  // ###
 		 CORBA::Float& ItemPrice,
		 CORBA::Float& ItemTaxPrice, AStore::ItemInfo*& IInfo,
		 CORBA::Environment &IT_env=CORBA::default_environment);
};

#endif
