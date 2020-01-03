/********************************************************
 FILE: neo/POS.ter/pos_Ter.h

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
#ifndef pos_iter
#define pos_iter

#include "../compat.hh"
#include "pos.hh"
#include "store.hh"
#include "pnamesvc.hh"

// --------------------------POS Terminal ---------------------------
    class POSTerminal_i: public virtual ODF::Servant
    {
    private:
      POS::Barcode 		m_itemBarcode;
      CORBA::Long 		m_itemQuantity;
      AStore::Tax_var		m_taxRef;
      AStore::Store_var		m_storeRef;
      AStore::StoreAccess_var	m_storeAccessRef;
      POS::OutputMedia_var	m_outputMediaRef;
      CORBA::Float		m_saleSubTotal;
      CORBA::Float		m_saleTaxableSubTotal;
      CORBA::Float		m_POSTotal;
      CORBA::Float		m_POSTaxTotal;
      CORBA::Long		m_id;
      unsigned char LoggedIn();
      
    public:
      void _initialize_new_POSTerminal(PseudoNameService_ptr pns, CORBA::Long storeid,
                    POS::POSId id);

      void login ();

      void print_POS_sales_summary ();

      void print_store_sales_summary ();

      void send_barcode (const POS::Barcode item);

      void item_quantity (CORBA::Long qty);

      void send_barcode_and_quantity (const POS::Barcode item, 
                                     	      CORBA::Long qty);

      void end_of_sale ();

    };

#endif
