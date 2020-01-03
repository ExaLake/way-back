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
#include "POS_Ter.h"

POSTerminal_i:: POSTerminal_i(PseudoNameService_ptr pns, CORBA::Long StoreId,
                              POS::POSId Id, CORBA::Environment &IT_env)
	: m_itemBarcode(0),m_id(Id),m_POSTaxTotal(0.0),
	  m_POSTotal(0.0),m_saleTaxableSubTotal(0.0),  
	  m_saleSubTotal(0.0),
	  m_storeAccessRef(AStore::StoreAccess::_nil())   {

   // Load in the stringified object references from the files and
  // construct references to these objects
   char caStr[255];

   // Find Tax or Store Object ref
   sprintf(caStr,"Tax_%ld",StoreId);
   CORBA::Object_ptr taxobj = pns->ResolveName(caStr, IT_env);
   sprintf(caStr,"Store_%ld",StoreId);
   CORBA::Object_ptr storeobj = pns->ResolveName(caStr, IT_env);
   sprintf(caStr,"OutputMedia_%ld",Id);
   CORBA::Object_ptr omobj = pns->ResolveName(caStr, IT_env);
   if
      (CORBA::is_nil(storeobj)||CORBA::is_nil(taxobj)||CORBA::is_nil(omobj)){
      cerr << "Trouble finding tax, store, or outputmedia " << endl;
      return ;
   }
                                   
   m_taxRef = AStore::Tax::_narrow(taxobj, IT_env);
   if (IT_env.exception()){
       cerr << "Trouble finding tax, store, or outputmedia " << endl;
       return;
   }
   
   m_storeRef = AStore::Store::_narrow(storeobj, IT_env);
   if (IT_env.exception()){
       cerr << "Trouble finding tax, store, or outputmedia " << endl;
       return;
   }


   m_outputMediaRef = POS::OutputMedia::_narrow(omobj, IT_env);
   if (IT_env.exception()){
       cerr << "Trouble finding tax, store, or outputmedia " << endl;
       return;
   }

}

void  POSTerminal_i:: Login (CORBA::Environment &IT_env) {
   if (!CORBA::is_nil(m_storeAccessRef)) {
      cerr << "Can't log in twice" << endl;
      return;
   }
   // Get a reference to the StoreAccess object for this POS
   m_storeAccessRef = m_storeRef->Login(m_id , IT_env);
   if (IT_env.exception()){
       cerr << "Error in Login" << endl;
       return;
   }
   m_saleSubTotal = m_POSTotal = m_POSTaxTotal = 0.0;
   m_itemQuantity = 1;
}

void  POSTerminal_i:: PrintPOSSalesSummary (CORBA::Environment& IT_env) {
   if (!LoggedIn())
      return;
   if ((m_itemBarcode != 0) || (m_saleSubTotal != 0.0))
      return;
   char caOpStr[255];
   sprintf(caOpStr,"%25s %8.2f\n%25s %8.2f\n","Point of Sale Total := ",
           m_POSTotal, "Tax Total := ",m_POSTaxTotal);
   m_outputMediaRef->OutputText(caOpStr, IT_env);
}


void  POSTerminal_i:: PrintStoreSalesSummary (CORBA::Environment& IT_env) {
   if (!LoggedIn())
      return;
   if ((m_itemBarcode != 0) || (m_saleSubTotal != 0.0))
      return;
   char caOpStr[255];

   // Find and output the total sales and tax for the store

   AStore::Store::StoreTotals tots;

   tots = m_storeRef->Totals(IT_env);
   sprintf(caOpStr,"%s %7.2f\n%s %7.2f\n","Total Sales :=",tots.StoreTotal,
           "Total Tax   :=",tots.StoreTaxTotal);
   m_outputMediaRef->OutputText("STORE TOTALS", IT_env);
   m_outputMediaRef->OutputText(caOpStr, IT_env);

   // Output the totals for each POS in turn

   AStore::POSList_var PL;

   m_storeRef->GetPOSTotals(PL, IT_env);

   for (CORBA::ULong i = 0; i < PL->length(); i++) { 
      if (PL[i].Id>0) {
         sprintf(caOpStr,"%15s %ld\n%15s %9.2f\n%15s %9.2f\n","POS   I.D. : ",
                 PL[i].Id,"Total Sales : ",PL[i].TotalSales,"Total Tax : ",
                 PL[i].TotalTaxes);

         m_outputMediaRef->OutputText(caOpStr, IT_env);
      }
   }
}

void  POSTerminal_i:: SendBarcode (const char* item, 
                                    CORBA::Environment &IT_env) {
   if (!LoggedIn())
      return;
   AStore::ItemInfo_var ItemInf;
   CORBA::Float price;
   CORBA::Float taxablePrice;
   delete[] m_itemBarcode;
   m_itemBarcode = new char[strlen(item) + 1];
   strcpy(m_itemBarcode,item);

   m_storeAccessRef->FindPrice(m_itemBarcode,m_itemQuantity,
				 price,taxablePrice,ItemInf, IT_env);

   if (IT_env.exception() != NULL)
      if (AStore::BarcodeNotFound::_narrow(IT_env.exception()) != NULL)
         {
            m_itemQuantity = 1;    
            cout << "Invalid Barcode Found" << endl;
            IT_env.clear();
            return;
         }
      else 
         {
            cout << "Error in find Price" << endl;
            return;
         }        



   CORBA::Float itemExt = (CORBA::Float)m_itemQuantity * price;
   m_saleSubTotal += itemExt;

  char caOpStr[255];
  char* szFmtStr = "%3d %10s %20s %7.2f %7.2f %s";
  sprintf(caOpStr,szFmtStr,m_itemQuantity,m_itemBarcode,ItemInf->Name,
	  ItemInf->Itemcost,itemExt,
	  ((taxablePrice > 0.0) ? " *" : "") );

   m_outputMediaRef->OutputText(caOpStr, IT_env);
   m_saleTaxableSubTotal += taxablePrice * (CORBA::Float)m_itemQuantity;
   m_itemQuantity = 1;
}

void  POSTerminal_i:: ItemQuantity (CORBA::Long Quantity,
				    CORBA::Environment&) {
   if (!LoggedIn())
      return;
   if (Quantity > 0)
      m_itemQuantity = Quantity;
}


void  POSTerminal_i:: EndOfSale (CORBA::Environment& IT_env) {
   char caOpStr[255];
   if (!LoggedIn())
      return;

   sprintf(caOpStr,"Taxable Sub-Total := %8.2f",m_saleTaxableSubTotal);
   m_outputMediaRef->OutputText(caOpStr, IT_env);
   CORBA::Float saleTax = m_taxRef->CalculateTax(m_saleTaxableSubTotal,IT_env);
   sprintf(caOpStr,"Taxes             := %8.2f",saleTax);
   m_outputMediaRef->OutputText(caOpStr, IT_env);

   CORBA::Float saleTotal = saleTax + m_saleSubTotal;
   sprintf(caOpStr,"Total             := %8.2f",saleTotal);
   m_outputMediaRef->OutputText(caOpStr, IT_env);

   m_outputMediaRef->OutputText("\nGo raibh maith agat\n", IT_env);
   m_POSTotal += saleTotal;
   m_POSTaxTotal += saleTax;

   m_storeRef->UpdateStoreTotals(m_id,saleTotal,saleTax, IT_env);

   m_saleSubTotal = m_saleTaxableSubTotal = 0;
   m_itemQuantity = 1;
   if (m_itemBarcode) {
      delete[] m_itemBarcode;
      m_itemBarcode = 0;
   }
   return;
}

unsigned char POSTerminal_i::LoggedIn() {
   if (CORBA::is_nil(m_storeAccessRef)) {
      cerr << "Need to log in first" << endl;
      return 0;
   }
   else
      return 1;
}
