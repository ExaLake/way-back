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

#ifndef POS_TER_H
#define POS_TER_H

#include <PNS.h>
#include <Store.h>
#include <POS_s.h>

    class POSTerminal_i : public POS::POSTerminal_base_impl
    {
    private:
      POS::Barcode   		m_itemBarcode;
      CORBA::Long 	  	   m_itemQuantity;
      AStore::Tax*		   m_taxRef;
      AStore::Store*		   m_storeRef;
      AStore::StoreAccess*	m_storeAccessRef;
      POS::OutputMedia*		m_outputMediaRef;
      CORBA::Float		   m_itemExtension;
      CORBA::Float		   m_saleSubTotal;
      CORBA::Float		   m_saleTaxableSubTotal;
      CORBA::Float		   m_POSTotal;
      CORBA::Float		   m_POSTaxTotal;
      CORBA::Long		      m_id;
      unsigned char        LoggedIn();
       
    public:
      POSTerminal_i(PseudoNameService_ptr   pns
                   ,char                  * storeid
                   ,POS::POSId              id);
      virtual void Login ();
      virtual void PrintPOSSalesSummary ();
      virtual void PrintStoreSalesSummary ();
      virtual void SendBarcode (const char *Item);
      virtual void ItemQuantity (CORBA::Long Quantity);
      virtual void EndOfSale ();

	};
#endif
