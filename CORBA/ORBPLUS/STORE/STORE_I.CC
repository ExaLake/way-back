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

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include "Store_i.h"
#include "../PNS/FindPNS.h"

#define EMPTY      -1
const CORBA::Float region_rate = 0.05;

Tax_i::Tax_i(PseudoNameService_ptr pns, AStore::AStoreId StoreId,
	     CORBA::Environment& IT_env) {
   // Register the object with the name server
   char regstr[255];
   sprintf(regstr,"Tax_%ld",StoreId);
   AStore::Tax_var TaxObjRef = _this();
   pns->BindName(regstr, TaxObjRef, IT_env);

   // set tax rate applied to taxable goods
   m_regionRate = region_rate;
}

CORBA::Float Tax_i::CalculateTax (CORBA::Float TaxableAmount,
                                  CORBA::Environment &){
   return TaxableAmount*m_regionRate;
}

CORBA::Float Tax_i::FindTaxablePrice (CORBA::Float ItemPrice,
				 AStore::ItemTypes ItemType,
				 CORBA::Environment &) {
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
	 : m_POSTerminals(10), m_storeTotal(0), m_storeTaxTotal(0),
	   m_storeMarkup(StoreMarkup), m_storeId(StoreId)           {

   // Register the object with the name server
   char refstring[512];
   sprintf(refstring,"Store_%ld",StoreId);
   m_pns            = pns;

   AStore::Store_var StoreObjRef = _this();
   m_pns->BindName(refstring, StoreObjRef, IT_env);

   // initialize m_POSTerminals to indicate no POS logins have been received
   CORBA::ULong len = m_POSTerminals.length();
   for (int i = 0; i < len; i++)
      m_POSTerminals[i].Id = EMPTY;
      m_POSTerminals[i].StoreAccessReference = AStore::StoreAccess::_nil();
}

AStore::AStoreId Store_i::StoreId (CORBA::Environment &) {
  return m_storeId;
}

AStore::Store::StoreTotals Store_i::Totals(CORBA::Environment &) {
  AStore::Store::StoreTotals ST;
  ST.StoreTotal=m_storeTotal;
  ST.StoreTaxTotal=m_storeTaxTotal;
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

      AStore::Store_var StoreObjRef = _this();
      StoreAccess_i* storeAccessInst=new StoreAccess_i(m_pns, StoreObjRef,
                                                        m_storeMarkup, IT_env);
      if (IT_env.exception()) {
        cerr << "Store_i::Login: Unable to create StoreAccess object for"
	     << " POS Login" << endl;
        return 0;
      }

     m_POSTerminals[loc].StoreAccessReference = storeAccessInst->_this();

     if (CORBA::is_nil(	m_POSTerminals[loc].StoreAccessReference))
        cerr << "Store_i::Login: Unable to create StoreAccess object for"
	     << " POS Login" << endl;
  }
  return AStore::StoreAccess::_duplicate(
				 m_POSTerminals[loc].StoreAccessReference);
}


void Store_i::GetPOSTotals (AStore::POSList* &POSData,
			      CORBA::Environment &) {
  POSData = new AStore::POSList(m_POSTerminals);
}

void Store_i::UpdateStoreTotals (POS::POSId Id, CORBA::Float Price,
				   CORBA::Float Taxes,
				   CORBA::Environment &IT_env) {
   CORBA::ULong i = 0;
   CORBA::ULong len = m_POSTerminals.length();
   while (i < len && m_POSTerminals[i].Id != Id) { 
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
                              AStore::Store_ptr pStore,
                              CORBA::Float StoreMarkup,
			      CORBA::Environment &IT_env) {
   // Find the tax and depot objects by asking the name service for pointers
    char refstr[255];
    AStore::AStoreId id = pStore->StoreId(IT_env);
    sprintf(refstr,"Tax_%ld",id);

   CORBA::Object_ptr taxobj = pns->ResolveName(refstr, IT_env);
   CORBA::Object_ptr depotobj = pns->ResolveName("Depot", IT_env);
    if (CORBA::is_nil(taxobj) || CORBA::is_nil(depotobj)){
       cerr << "Trouble finding tax or depot " << endl;
       exit(EXIT_FAILURE);
    }

   m_tax= AStore::Tax::_narrow(taxobj, IT_env);

   if (IT_env.exception()) {
      cerr << "ERROR Initializing Tax Object" << endl;
      exit(EXIT_FAILURE);
   }

   m_depot= CentralOffice::Depot::_narrow(depotobj, IT_env);

   if (IT_env.exception()) {
      cerr << "ERROR Initializing Depot Object" << endl;
      exit(EXIT_FAILURE);
   }

   m_store = AStore::Store::_duplicate(pStore);
   m_storeMarkup = StoreMarkup;
}


void StoreAccess_i::FindPrice (const char* Item,
	CORBA::Long Quantity,
	CORBA::Float& ItemPrice, CORBA::Float& ItemTaxPrice,
	AStore::ItemInfo*& IInfo, CORBA::Environment &IT_env) {
  IInfo = new AStore::ItemInfo;
  m_depot->FindItemInfo(m_store->StoreId(IT_env),Item,Quantity,IInfo,IT_env);
  ItemPrice  = m_storeMarkup * IInfo->Itemcost;
  ItemTaxPrice = m_tax->FindTaxablePrice(ItemPrice,
                                         IInfo->Itemtype,IT_env);
}
