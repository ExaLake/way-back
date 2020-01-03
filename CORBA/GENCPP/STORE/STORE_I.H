/*

Copyright (C) 1996 by the Object Management Group, Inc.  All  
rights reserved.  

Permission to use, copy, modify, and distribute this software for
any teaching or instructional purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that copyright notice and this permission
notice appear in supporting documentation, and that the names of
Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
(Wiley) not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
assume any liability of any alleged or actual damages arising
from the use of or the inability to use this software.  (Some
states do not allow the exclusion of implied warranties, so the
exclusion may not apply to you.)

*/
#ifndef STORE_I_H
#define STORE_I_H

#include <### PNS interface header file>
#include <### Store interface header file>
#include <### Central interface header file>

class Tax_i : <### ORB specific base class>
{
private:
	CORBA::Float       m_regionRate;
public:
   Tax_i(PseudoNameService_ptr pns,AStore::AStoreId StoreID);
   virtual CORBA::Float CalculateTax(CORBA::Float TaxableAmount);

	virtual CORBA::Float FindTaxablePrice(
                      CORBA::Float      ItemPrice,
                      AStore::ItemTypes Itemtype);

};

class Store_i : ORB specific base class
{
private:
	CORBA::ULong              LocatePOSEntry(CORBA::Long);
   AStore::AStoreId          m_storeID;
   CORBA::Float              m_storeTotal;
   CORBA::Float              m_storeTaxTotal;
   CORBA::Float              m_storeMarkup;
   AStore::POSList           m_POSTerminals;
   PseudoNameService_var     m_pns;
public:
   Store_i(PseudoNameService_ptr pns,
           AStore::AStoreId storeID,
           CORBA::Float storeMarkup);

   virtual AStore::AStoreId           StoreId();

   virtual AStore::Store::StoreTotals Totals();

   virtual AStore::StoreAccess_ptr    Login(
                     CORBA::Long         Id);

   virtual void                       GetPOSTotals(
                     AStore::POSList_out  POSData);

   virtual void                       UpdateStoreTotals(
							CORBA::Long          Id,
                     CORBA::Float         Price,
                     CORBA::Float         Taxes);

};

class StoreAccess_i : ORB specific base class
{
private:
   CORBA::Float              m_storeMarkup;
   CentralOffice::Depot_var  m_depot;
   AStore::Tax_var           m_tax;
   AStore::Store_var	        m_store;
public:
   StoreAccess_i(PseudoNameService_ptr pns,
                 AStore::Store_var     pStore,
                 CORBA::Float          markup);

   virtual void FindPrice(
                      const char          *Item,
                      CORBA::Long          Quantity,
                      CORBA::Float&        ItemPrice,
                      CORBA::Float&        ItemTaxPrice,
                      AStore::ItemInfo_out IInfo);

};

#endif
