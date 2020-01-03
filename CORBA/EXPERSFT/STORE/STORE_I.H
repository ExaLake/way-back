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

#ifndef STORE_I_H
#define STORE_I_H

#include <PNS.h>
#include <Store_s.h>
#include <Central.h>

class Tax_i : public AStore::Tax_base_impl
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

class Store_i : public AStore::Store_base_impl
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

class StoreAccess_i : public AStore::StoreAccess_base_impl
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
