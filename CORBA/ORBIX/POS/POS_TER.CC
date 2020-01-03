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
#include "POS_Ter.h"
POSTerminal_i:: POSTerminal_i(PseudoNameService_ptr pns, CORBA::Long StoreId,
                              POS::POSId Id)
	: m_itemBarcode(0),m_id(Id),m_POSTaxTotal(0.0),
	  m_POSTotal(0.0),m_saleTaxableSubTotal(0.0),
	  m_saleSubTotal(0.0),
	  m_storeAccessRef(AStore::StoreAccess::_nil())  {
  // use the PNS to find our Tax, Store and OutputMedia objects:
  char caStr[255];
  try {
    sprintf(caStr,"Tax_%ld",StoreId);
    m_taxRef = AStore::Tax::_narrow(pns->ResolveName(caStr));
    sprintf(caStr,"Store_%ld",StoreId);
    m_storeRef = AStore::Store::_narrow(pns->ResolveName(caStr));
    sprintf(caStr,"OutputMedia_%ld",Id);
    m_outputMediaRef = POS::OutputMedia::_narrow(pns->ResolveName(caStr));
  }
  catch(...) {
    cerr << "Trouble finding tax, store, or outputmedia " << endl;
  }
}

void  POSTerminal_i:: Login (CORBA::Environment &IT_env) {
  if (!CORBA::is_nil(m_storeAccessRef)) {
    cerr << "Can't log in twice" << endl;
    return;
  }
  // Get a reference to the StoreAccess object for this POS
  try {
    m_storeAccessRef = m_storeRef->Login(m_id, IT_env);

  }
  catch(...) {
    cerr << "Error in Login" << endl;
    return;
  }
  m_saleSubTotal = m_POSTotal = m_POSTaxTotal = 0.0;
  m_itemQuantity = 1;
}

void  POSTerminal_i:: PrintPOSSalesSummary (CORBA::Environment &IT_env) {

  if (!LoggedIn())
    return;
  if ((m_itemBarcode != 0) || (m_saleSubTotal != 0.0))
    return;
  char caOpStr[255];
  sprintf(caOpStr,"%25s %8.2f\n%25s %8.2f\n","Point of Sale Total := ",
	  m_POSTotal, "Tax Total := ",m_POSTaxTotal);
  try {
    m_outputMediaRef->OutputText(caOpStr);
  }
  catch(...) {
    cerr << "Error in Sales Summary" << endl;
  }
}

void  POSTerminal_i:: PrintStoreSalesSummary (CORBA::Environment &IT_env) {
  if (!LoggedIn())
    return;

  if ((m_itemBarcode != 0) || (m_saleSubTotal != 0.0))
    return;
  char caOpStr[255];

  // Find and output the total sales and tax for the store

  AStore::Store::StoreTotals tots;
  try {
    tots = m_storeRef->Totals();
  }
  catch(...) {
    cerr << "Error finding store totals" << endl;
    return;
  }
  sprintf(caOpStr,"%s %7.2f\n%s %7.2f\n","Total Sales :=",tots.StoreTotal,
				   "Total Tax   :=",tots.StoreTaxTotal);
  try {
    m_outputMediaRef->OutputText("STORE TOTALS");
    m_outputMediaRef->OutputText(caOpStr);
  }
  catch(...) {
    cerr << "Error with Output Media" << endl;
    return;
  }

  // Output the totals for each POS in turn

  AStore::POSList_var PL;
  try {
    m_storeRef->GetPOSTotals(PL);
  }
  catch(...) {
    cerr << "Error Getting Store Totals" << endl;
    return;
  }

  for (CORBA::ULong i = 0; i < PL->length(); i++) {   // ###
    if (PL[i].Id>0) {
      sprintf(caOpStr,"%15s %ld\n%15s %9.2f\n%15s %9.2f\n","POS   I.D. : ",
              PL[i].Id,"Total Sales : ",PL[i].TotalSales,"Total Tax : ",
              PL[i].TotalTaxes);
      try {
        m_outputMediaRef->OutputText(caOpStr);
      }
      catch(...) {
        cerr << "Error with Output Media" << endl;
        return;
      }
    }
  }   // end for
}

void  POSTerminal_i:: SendBarcode (const char* Item, CORBA::Environment &IT_env) {  // ###
  if (!LoggedIn())
    return;
  AStore::ItemInfo_var ItemInf;
  CORBA::Float price;
  CORBA::Float taxablePrice;
  delete[] m_itemBarcode;   // ###
  m_itemBarcode = new char[strlen(Item) + 1];
  strcpy(m_itemBarcode,Item);

  try {
    m_storeAccessRef->FindPrice(m_itemBarcode,m_itemQuantity,
				 price,taxablePrice,ItemInf);
  }
  catch(const AStore::BarcodeNotFound& bcnf) { // ###
    m_itemQuantity = 1;    
    cerr << "Invalid Barcode Found" << endl;
    return;
  }
  catch (...) {
    m_itemQuantity = 1;
    cerr << "Error in find Price" << endl;
    return;
  }

  CORBA::Float itemExt = (CORBA::Float) (m_itemQuantity* price);

  m_saleSubTotal += itemExt;

  char caOpStr[255];
  char* szFmtStr = "%3d %10s %20s %7.2f %7.2f %s";
// ###
  sprintf(caOpStr,szFmtStr,m_itemQuantity,m_itemBarcode,ItemInf->Name,
	  ItemInf->Itemcost,itemExt,
	  ((taxablePrice > 0.0) ? " *" : "") );

  try {
    m_outputMediaRef->OutputText(caOpStr);
  }
  catch(...) {
    cerr << "Error with Output Media" << endl;
    return;
  }
  m_saleTaxableSubTotal += taxablePrice * m_itemQuantity;
  m_itemQuantity = 1;
}

void  POSTerminal_i:: ItemQuantity (CORBA::Long Quantity, CORBA::Environment
&IT_env) {
  if (!LoggedIn())
    return;
  if (Quantity > 0)
    m_itemQuantity = Quantity;
}


void  POSTerminal_i:: EndOfSale (CORBA::Environment &IT_env) {
  char caOpStr[255];
// ###
  if (!LoggedIn())
    return;

  sprintf(caOpStr,"Taxable Sub-Total :  %8.2f",m_saleTaxableSubTotal);
  m_outputMediaRef->OutputText(caOpStr);
  CORBA::Float saleTax = m_taxRef->CalculateTax(m_saleTaxableSubTotal);
  sprintf(caOpStr,"Taxes             :  %8.2f",saleTax);
  m_outputMediaRef->OutputText(caOpStr);

  CORBA::Float saleTotal = saleTax + m_saleSubTotal;
  sprintf(caOpStr,"Total             :  %8.2f",saleTotal);
  m_outputMediaRef->OutputText(caOpStr);

  m_outputMediaRef->OutputText("\nGo raibh maith agat\n");
  m_POSTotal += saleTotal;
  m_POSTaxTotal += saleTax;

  try {
    m_storeRef->UpdateStoreTotals(m_id,saleTotal,saleTax);
  }
  catch(...) {
    cerr << "Error Ending sale" << endl ;
  }

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
