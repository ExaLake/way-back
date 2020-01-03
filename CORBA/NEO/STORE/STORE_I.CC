/********************************************************
 FILE: neo/store/store_i.cc

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

#include "odf_output/OdfstoreImpl.hh"
#include <stream.h>
#include "pnsfind.h"

#define EMPTY      -1
const CORBA::Float region_rate = 0.05;

void Tax_i::_initialize_new_Tax(PseudoNameService_ptr pns) {
   // Register the object with the name server
  try {
    pns->Bind("Tax",_servant_objref());
  }
  catch(...) {
    cerr << "Trouble Binding Tax server" << endl;
  }
  // set tax rate applied to taxable goods
  m_regionRate = region_rate;
}

CORBA::Float Tax_i::calculate_tax (CORBA::Float taxable_amount) {
   return taxable_amount*m_regionRate;
}

CORBA::Float Tax_i::find_taxable_price (CORBA::Float item_price,
				        AStore::ItemTypes in_itemtype) {
   CORBA::Float taxprice;
   if (in_itemtype == AStore::other)
      taxprice = item_price;
   else
      taxprice = 0.0;
   return taxprice;
}

void Store_i::_initialize_new_Store(PseudoNameService_ptr pns,
                 AStore::AStoreId storeID, CORBA::Float storeMarkup) 
{
  m_POSTerminals.buffer(AStore::POSInfo::_new_bracket(10));
  m_POSTerminals.maximum() = m_POSTerminals.length() = 10;
  // Register the object with the name server
  char refstring[1024];
  sprintf(refstring,"Store_%ld",storeID);
  m_pns            = pns;
  try {
    m_pns->Bind(refstring,_servant_objref());
  }
  catch(...) {
    cerr << "Trouble Binding " << refstring << endl;
  }
  m_storeID        = storeID;
  m_storeMarkup    = storeMarkup;
  m_storeTotal     = 0;
  m_storeTaxTotal  = 0;
  // initialize m_POSTerminals to indicate no POS logins have been received
  CORBA::ULong len = m_POSTerminals.length();
  for (int i = 0; i < len; i++)
     m_POSTerminals[i].id() = EMPTY;
}

AStore::AStoreId Store_i::store_id () {
  return m_storeID;
}

AStore::Store::StoreTotals *Store_i::totals() {
  AStore::Store::StoreTotals* ST = new AStore::Store::StoreTotals;
  ST->store_total()=m_storeTotal;
  ST->store_tax_total()=m_storeTaxTotal;
  return ST;
}

AStore::StoreAccess* Store_i::login (POS::POSId id) {
  CORBA::ULong loc      = locate_POS_entry(id);
  m_POSTerminals[loc].id()          = id;
  m_POSTerminals[loc].total_sales() = 0;
  m_POSTerminals[loc].total_taxes() = 0;
  // check to see if a StoreAccess object exists for this POSTerminal
  // allocate new one if needed.
  if( m_POSTerminals[loc].store_access_reference()->_is_nil() )
  {
     // create a local instance of the StoreAccess Object
     m_POSTerminals[loc].store_access_reference() = 
	OdfStoreAccess_i::new_StoreAccess(m_pns);
     if( m_POSTerminals[loc].store_access_reference()->_is_nil() )
        cerr << "Store_i::login: Unable to create StoreAccess object for POS Login" << endl;
  }
  return m_POSTerminals[loc].store_access_reference()->_duplicate();
}

void Store_i::get_POS_totals (AStore::POSList* &POS_list) {
  POS_list = new AStore::POSList(m_POSTerminals);
}

void Store_i::update_store_totals (POS::POSId id, CORBA::Float price,
				   CORBA::Float taxes) {
   CORBA::ULong i = 0;
   CORBA::ULong len = m_POSTerminals.length();
   int found = 0;
   while (i < len && !found) {
      if (m_POSTerminals[i].id() == id)
         found = 1;
      else
         i++;
   }
   if (found) {
      m_POSTerminals[i].total_sales() += price;
      m_POSTerminals[i].total_taxes() += taxes;
      m_storeTotal +=price;
      m_storeTaxTotal +=taxes;
   }
   else
      cerr << "Store_i::update_store_totals: Could not locate POS Terminal " << id << endl;
}

CORBA::ULong Store_i::locate_POS_entry(POS::POSId id) {
  CORBA::ULong loc      = EMPTY;
  CORBA::ULong availloc = EMPTY;
  CORBA::ULong len      = m_POSTerminals.length();
  int keepgoing         = 1;
  CORBA::ULong i        = 0;

  // locate POSId or first available slot
  while (loc == EMPTY && i < len) {
     if (m_POSTerminals[i].id() == id)
        loc = i;
     else if (availloc == EMPTY && m_POSTerminals[i].id() == EMPTY)
        availloc = i;
     else
        i++;
  }

  // if we did not find POSId then use avail slot or append new
  // slot at end of m_POSTerminals
  if (loc == EMPTY) {
     if (availloc != EMPTY)
        loc = availloc;
     else {
       m_POSTerminals.length(i+1);
       loc = i;
     }
  }
  return loc;
}

void StoreAccess_i::_initialize_new_StoreAccess (PseudoNameService_ptr pns) {
  // Find the tax and depot objects by asking the name service for pointers
  try {
    m_tax= AStore::Tax::_narrow(pns->Resolve("Tax"));
    m_depot= CentralOffice::Depot::_narrow(pns->Resolve("Depot"));
  }
  catch(...) {
    cerr << "Trouble finding tax or depot " << endl;
  }
}

void StoreAccess_i::find_price (const POS::Barcode item,
	CORBA::Long quantity, CORBA::Long store_id,
	CORBA::Float& item_price, CORBA::Float& item_tax_price,
	AStore::ItemInfo*& item_info) {
  AStore::ItemInfo *i2;
  m_depot->find_item_info(store_id,item,quantity,i2);
  item_info      = i2;
  item_price     = item_info->itemcost();
  item_tax_price = m_tax->find_taxable_price(item_price
                                            ,item_info->itemtype()
                                            );
}
