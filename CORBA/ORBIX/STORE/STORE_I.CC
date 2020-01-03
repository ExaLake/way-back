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

#include <iostream.h>
#include <stdio.h>
#include "Store_i.h"
#include "../PNS/FindPNS.h"

#define EMPTY      -1
const CORBA::Float region_rate = 0.05;

Tax_i::Tax_i(PseudoNameService_ptr pns,AStore::AStoreId StoreId) {
   // Register the object with the name server
  char regstr[255];
  sprintf(regstr,"Tax_%ld",StoreId);
  try {
    pns->BindName(regstr,this);
  }
  catch(...) {
    cerr << "Trouble Binding Tax server" << endl;
  }
  // set tax rate applied to taxable goods
  m_regionRate = region_rate;
}

CORBA::Float Tax_i::CalculateTax (CORBA::Float TaxableAmount,
				   CORBA::Environment &IT_env) {
   return TaxableAmount*m_regionRate;
}

CORBA::Float Tax_i::FindTaxablePrice (CORBA::Float ItemPrice,
				 AStore::ItemTypes ItemType,
				 CORBA::Environment &IT_env) {
   CORBA::Float taxprice;
   if (ItemType == AStore::other)
      taxprice = ItemPrice;
   else
      taxprice = 0.0;
   return taxprice;
}

Store_i::Store_i(PseudoNameService_ptr pns,
                 AStore::AStoreId StoreId, CORBA::Float StoreMarkup,
                 CORBA::Environment &IT_env)
	 : m_POSTerminals(10),m_storeTotal(0), m_storeTaxTotal(0), // ###
	   m_storeMarkup(StoreMarkup),m_storeId(StoreId)           {
  // Register the object with the name server
  char refstring[512];
  sprintf(refstring,"Store_%ld",StoreId);
  m_pns = pns;
  try {
    m_pns->BindName(refstring,this);
  }
  catch(...) {
    cerr << "Trouble Binding " << refstring << endl;
  }
 // ### 
  // initialize m_POSTerminals to indicate no POS Logins have been received
  CORBA::ULong len = m_POSTerminals.length();
  for (int i = 0; i < len; i++) {
     m_POSTerminals[i].Id = EMPTY;
     m_POSTerminals[i].StoreAccessReference = AStore::StoreAccess::_nil();
  }
}

AStore::AStoreId Store_i::StoreId (CORBA::Environment &IT_env) {
  return m_storeId;
}

AStore::Store::StoreTotals Store_i::Totals(CORBA::Environment &IT_env) {
  AStore::Store::StoreTotals ST;
  ST.StoreTotal = m_storeTotal;
  ST.StoreTaxTotal = m_storeTaxTotal;
  return ST;
}

AStore::StoreAccess_ptr Store_i::Login (POS::POSId Id,
				     CORBA::Environment &IT_env) {
  CORBA::ULong loc               = LocatePOSEntry(Id);
  m_POSTerminals[loc].Id         = Id;
  m_POSTerminals[loc].TotalSales = 0;
  m_POSTerminals[loc].TotalTaxes = 0;
  // check to see of a StoreAccess object exists for this POSTerminal
  // allocate new one if needed.
  if (CORBA::is_nil(m_POSTerminals[loc].StoreAccessReference)) {
     // create a local instance of the StoreAccess Object
     m_POSTerminals[loc].StoreAccessReference = // ###
                                    new StoreAccess_i(m_pns,this,m_storeMarkup);
     if (CORBA::is_nil(	m_POSTerminals[loc].StoreAccessReference)) //###
        cerr << "Store_i::Login: Unable to create StoreAccess object for"
	     << " POS Login" << endl;
  }
  return AStore::StoreAccess::_duplicate(
				 m_POSTerminals[loc].StoreAccessReference);
}

void Store_i::GetPOSTotals (AStore::POSList*& POSData,
			      CORBA::Environment &IT_env) {
  POSData = new AStore::POSList(m_POSTerminals);
}


void Store_i::UpdateStoreTotals (POS::POSId Id, CORBA::Float Price,
				   CORBA::Float Taxes,
				   CORBA::Environment &IT_env) {
   CORBA::ULong i = 0;
   CORBA::ULong len = m_POSTerminals.length();
   while (i < len && m_POSTerminals[i].Id != Id) {   // ###
         i++;
   }
   if (m_POSTerminals[i].Id == Id) {
      m_POSTerminals[i].TotalSales += Price;
      m_POSTerminals[i].TotalTaxes += Taxes;
      m_storeTotal +=Price;
      m_storeTaxTotal +=Taxes;
   }
   else
      cerr << "Store_i::UpdateStoreTotals: Could not locate POS Terminal "
           << Id << endl;
}

CORBA::ULong Store_i::LocatePOSEntry(POS::POSId Id) {
  CORBA::ULong loc      = EMPTY;
  CORBA::ULong availloc = EMPTY;
  CORBA::ULong len      = m_POSTerminals.length();  // current length
  CORBA::ULong i        = 0;

  // locate POSId or first EMPTY slot
  while (i<len && m_POSTerminals[i].Id != Id) {
    if ( m_POSTerminals[i].Id == EMPTY)
      availloc = i;
    i++;
  }
  // now test why we exited the loop:
  if (i < len)
    return i;   // found
  else {
    if (availloc != EMPTY)
      return availloc;  //not found but space available
    else {  // not found and no space available; so make more space:
      m_POSTerminals.length(len+1);
      return len;
    }
  }
}

StoreAccess_i::StoreAccess_i (PseudoNameService_ptr pns,
                              AStore::Store_ptr pStore,   // ###
                              CORBA::Float StoreMarkup,
                              CORBA::Environment &IT_env) {
  // Find the tax and depot objects by asking the name service for pointers
  try {
    char refstr[255];
    AStore::AStoreId id = pStore->StoreId();
    sprintf(refstr,"Tax_%ld",id);
    m_tax= AStore::Tax::_narrow(pns->ResolveName(refstr));
    m_depot= CentralOffice::Depot::_narrow(pns->ResolveName("Depot"));
    m_store = AStore::Store::_duplicate(pStore);
  }
  catch(...) {
    cerr << "Trouble finding tax or depot " << endl;
  }
  m_storeMarkup = StoreMarkup;
}

void StoreAccess_i::FindPrice (const char* Item, // ###
	CORBA::Long Quantity,
	CORBA::Float& ItemPrice, CORBA::Float& ItemTaxPrice,
	AStore::ItemInfo*& IInfo, CORBA::Environment &IT_env) {
  IInfo = new AStore::ItemInfo;
  m_depot->FindItemInfo(m_store->StoreId(),Item,Quantity,IInfo,IT_env);
  ItemPrice  = m_storeMarkup * IInfo->Itemcost;
  ItemTaxPrice = m_tax->FindTaxablePrice(ItemPrice, IInfo->Itemtype,IT_env);
}
