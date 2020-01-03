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
#ifndef POS_TER_H
#define POS_TER_H

#include <### PNS interface header file>
#include <### Store interface header file>
#include <### POS interface header file>

    class POSTerminal_i : <### ORB specific base class>
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
