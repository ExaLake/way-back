/*

Copyright (c) 1995 Expersoft Corporation.  All Rights Reserved.  

Unlimited use, reproduction, and distribution of this software is
permitted.  Any copy of this software must include both the above
copyright notice of Expersoft Corporation and this paragraph.  Any
distribution of this software must comply with all applicable United
States export control laws.  This software is made available AS IS,
and EXPERSOFT CORPORATION DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE, AND NOTWITHSTANDING ANY OTHER
PROVISION CONTAINED HEREIN, ANY LIABILITY FOR DAMAGES RESULTING FROM
THE SOFTWARE OR ITS USE IS EXPRESSLY DISCLAIMED, WHETHER ARISING IN
CONTRACT, TORT (INCLUDING NEGLIGENCE) OR STRICT LIABILITY, EVEN IF
EXPERSOFT CORPORATION IS ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

*/

#include "store_i.h"
#include <FindPNS.h>
#include <fstream.h>
#include <stdio.h>

#define EMPTY      -1
const CORBA::Float region_rate = 0.05;

Tax_i::Tax_i(PseudoNameService_ptr pns,
             AStore::AStoreId storeID)
{
   // set tax rate applied to taxable goods
   m_regionRate = region_rate;

   // Register the object with the name server
   char regstr[255];
   sprintf(regstr,"Tax_%ld",storeID);
   try {
      pns->BindName(regstr,_this());
   }
   catch(...) {
      cerr << "Trouble Binding Tax server" << endl;
   }
}

CORBA::Float Tax_i::CalculateTax(CORBA::Float          TaxableAmount)
{
   return TaxableAmount*m_regionRate;
}

CORBA::Float Tax_i::FindTaxablePrice(
                      CORBA::Float             ItemPrice,
                      AStore::ItemTypes        Itemtype)
{
   CORBA::Float taxprice;

   if (Itemtype == AStore::other)
      taxprice = ItemPrice;
   else
      taxprice = 0.0;
   return taxprice;
}

Store_i::Store_i(PseudoNameService_ptr pns,
                 AStore::AStoreId storeID,
				     CORBA::Float storeMarkup):
  m_POSTerminals(10)                     // start off with space for 10 POSs
{
   // Register the object with the name server
   char refstring[1024];
   sprintf(refstring,"Store_%ld",storeID);
   m_pns = PseudoNameService::_duplicate(pns);
   try {
      m_pns->BindName(refstring,_this());
   }
   catch(...) {
      cerr << "Trouble Binding " << refstring << endl;
   }

   m_storeTotal    = 0;
   m_storeTaxTotal = 0;
   m_storeMarkup   = storeMarkup;
   m_storeID       = storeID;
   // initialize m_POSTerminals to indicate no POS Logins have been received
   CORBA::ULong len      = m_POSTerminals.length();
   for (CORBA::ULong i = 0; i < len; i++)
	{
      m_POSTerminals[i].Id = EMPTY;
	}

}

CORBA::Long Store_i::StoreId()
{
   return m_storeID;
}

AStore::Store::StoreTotals Store_i::Totals()
{
  AStore::Store::StoreTotals ST;
  ST.StoreTotal=m_storeTotal;
  ST.StoreTaxTotal=m_storeTaxTotal;
  return ST;
}

AStore::StoreAccess_ptr Store_i::Login(CORBA::Long Id)
{

   CORBA::ULong loc = LocatePOSEntry(Id);

   m_POSTerminals[loc].Id         = Id;
   m_POSTerminals[loc].TotalSales = 0;
   m_POSTerminals[loc].TotalTaxes = 0;

   // check to see of a StoreAccess object exists for this m_POSTerminal
   // allocate new one if needed.
   if (CORBA::is_nil((AStore::StoreAccess_ptr &)m_POSTerminals[loc].StoreAccessReference))
   {
      // create a local instance of the SToreAccess Object
      m_POSTerminals[loc].StoreAccessReference = new StoreAccess_i(m_pns
                                                                    ,_this()
                                                                    ,m_storeMarkup);
      if (CORBA::is_nil((AStore::StoreAccess_ptr &)m_POSTerminals[loc].StoreAccessReference))
         cerr << "Store_i::Login: Unable to create StoreAccess object for POS Login" << endl;
   }
   return AStore::StoreAccess::_duplicate(m_POSTerminals[loc].StoreAccessReference);
}

void Store_i::GetPOSTotals(AStore::POSList_out POSData)
{
   POSData = new AStore::POSList(m_POSTerminals);
}

void Store_i::UpdateStoreTotals(
                         CORBA::Long  Id,
                         CORBA::Float Price,
                         CORBA::Float Taxes)
{

   CORBA::ULong i = LocatePOSEntry(Id);
   if (i != EMPTY)
   {
      m_POSTerminals[i].TotalSales += Price;
      m_POSTerminals[i].TotalTaxes += Taxes;
      m_storeTotal                 += Price;
      m_storeTaxTotal              += Taxes;
   }

   else
      cerr << "Store_i::UpdateStoreTotals: Could not locate POS Terminal " << Id << endl;
}

CORBA::ULong Store_i::LocatePOSEntry(CORBA::Long Id)
{
   CORBA::ULong loc       = EMPTY;
   CORBA::ULong availloc  = EMPTY;
   CORBA::ULong len       = m_POSTerminals.length();
   int keepgoing          = 1;
   CORBA::ULong i         = 0;

   // locate POSId or first available slot
   while (loc == EMPTY && i < len)
   {
      if (m_POSTerminals[i].Id == Id)
         loc = i;
      else if (availloc == EMPTY && m_POSTerminals[i].Id == EMPTY)
         availloc = i;
      else
         i++;
   }

   // if we did not find POSId then use the available slot or append new
   // slot at end of m_POSTerminals
   if (loc == EMPTY)
   {
      if (availloc != EMPTY)
         loc = availloc;
      else
		{
         m_POSTerminals.length(i+1);
         loc = i;
		}
   }
   return loc;
}

StoreAccess_i::StoreAccess_i(PseudoNameService_ptr pns,
                             AStore::Store_var     store,
                             CORBA::Float          markup)
{
   m_storeMarkup = markup;
   try
	{
      char refstr[255];
      AStore::AStoreId id = store->StoreId();
      sprintf(refstr,"Tax_%ld",id);
      m_tax= AStore::Tax::_narrow(pns->ResolveName(refstr));
      m_depot= CentralOffice::Depot::_narrow(pns->ResolveName("Depot"));
      m_store = AStore::Store::_duplicate(store);
	}
   catch(...) {
      cerr << "Trouble finding tax, store, or depot " << endl;
   }

}

void StoreAccess_i::FindPrice(
                         const char           *Item,
                         CORBA::Long           Quantity,
                         CORBA::Float&         ItemPrice,
                         CORBA::Float&         ItemTaxPrice,
                         AStore::ItemInfo_out  IInfo)
{

	AStore::ItemInfo *i2;
   m_depot->FindItemInfo(m_store->StoreId()
                        ,Item
                        ,Quantity
                        ,i2);
   IInfo      = new AStore::ItemInfo;
   *IInfo     = *i2;
   ItemPrice     = m_storeMarkup * IInfo->Itemcost;
   ItemTaxPrice = m_tax->FindTaxablePrice(
                                 ItemPrice
                                ,((AStore::ItemInfo *) IInfo)->Itemtype);
}
