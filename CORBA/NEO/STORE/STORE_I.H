/********************************************************
 FILE: neo/store/store_i.h

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

#ifndef store_ih
#define store_ih

#include "store.hh"
#include "pos.hh"
#include "central.hh"
#include "pnamesvc.hh"

class Tax_i: public virtual ODF::Servant {
  CORBA::Float m_regionRate;
public:
   void _initialize_new_Tax(PseudoNameService_ptr pns);

   CORBA::Float calculate_tax (CORBA::Float taxable_amount);

   CORBA::Float find_taxable_price (CORBA::Float item_price,
  		 AStore::ItemTypes in_itemtype);
};

class Store_i : public virtual ODF::Servant {
   AStore::AStoreId          m_storeID;
   CORBA::Float              m_storeTotal;
   CORBA::Float              m_storeTaxTotal;
   CORBA::Float              m_storeMarkup;
   AStore::POSList           m_POSTerminals;
   PseudoNameService_var     m_pns;
public:
    void _initialize_new_Store(PseudoNameService_ptr pns,
			     AStore::AStoreId storeID, 
			     CORBA::Float storeMarkup);
    AStore::AStoreId store_id ();
    AStore::Store::StoreTotals* totals ();
    AStore::StoreAccess* login (POS::POSId id);
    void get_POS_totals (AStore::POSList*& POS_list);
    void update_store_totals (POS::POSId id, CORBA::Float price,
   		 CORBA::Float taxes);
    virtual CORBA::ULong Store_i::locate_POS_entry(POS::POSId id);
};

class StoreAccess_i : public virtual ODF::Servant {
   CentralOffice::Depot_var  m_depot;
   AStore::Tax_var           m_tax;
public:
  void _initialize_new_StoreAccess(PseudoNameService_ptr pns);
  void StoreAccess_i::find_price (const POS::Barcode item,
	CORBA::Long quantity, CORBA::Long store_id,
	CORBA::Float& item_price, CORBA::Float& item_tax_price,
	AStore::ItemInfo*& item_info);
};

#endif
