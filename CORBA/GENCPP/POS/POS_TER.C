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
#include <stream.h>
#include "POS_Ter.h"
#include <FindPNS.h>
#include <### PNS interface header file>

POSTerminal_i:: POSTerminal_i(PseudoNameService_ptr   pns
                             ,char                  * storeid
                             ,POS::POSId              id)
{
  // Load in the stringified object references from the files and
  // construct references to these objects
  char caStr[512];
  strcpy(caStr,"Tax_");
  strcat(caStr, storeid);
  CORBA::Object_ptr obj = pns->ResolveName(caStr);
  m_taxRef = AStore::Tax::_narrow(obj);

  strcpy(caStr,"Store_");
  strcat(caStr,storeid);
  obj = pns->ResolveName(caStr);
  m_storeRef = AStore::Store::_narrow(obj);

  sprintf(caStr,"OutputMedia_%ld",id);
  obj = pns->ResolveName(caStr);
  m_outputMediaRef = POS::OutputMedia::_narrow(obj);

  // Initialize the member variables to their appropriate values
  m_itemBarcode = 0;
  m_storeAccessRef = AStore::StoreAccess::_nil();
  m_id = id;
  m_POSTaxTotal = m_POSTotal = 0.0;
  m_saleTaxableSubTotal = m_saleSubTotal = 0.0;
}

void  POSTerminal_i:: Login () 
{
  if (!CORBA::is_nil(m_storeAccessRef)) {
    cerr << "Can't log in twice" << endl;
    return;
  }
  // Get a reference to the StoreAccess object for this POS
  try
  {
     m_storeAccessRef = m_storeRef->Login(m_id);
  }
  catch (...)
  {
    cout << "Error in Login" << endl;
    return;
  }

  m_saleSubTotal = m_POSTotal = m_POSTaxTotal = 0.0;
  m_itemQuantity = 1;
}

//----------------------------------------------------------------------------
void  POSTerminal_i:: PrintPOSSalesSummary () 
{
  if (!LoggedIn())
    return;
  if ((m_itemBarcode != 0) || (m_saleSubTotal != 0.0))
    return;
  char caOpStr[255];
  sprintf(caOpStr,"%25s %8.2f\n%25s %8.2f\n","Point of Sale Total := ", 
          m_POSTotal, "Tax Total := ",m_POSTaxTotal);
  try
  {
     m_outputMediaRef->OutputText(caOpStr);
  }
  catch (...)
  {
     cerr << "Error printing Sales Summary" << endl;
     return;
  }

}

//-----------------------------------------------------------------------------
void  POSTerminal_i:: PrintStoreSalesSummary () 
{
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
    cerr << "Error finding store Totals" << endl;
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

  // Output the Totals for each POS in turn

  AStore::POSList_var PL;
  try {
    m_storeRef->GetPOSTotals(PL);
  }
  catch(...) {
    cerr << "Error Getting Store Totals" << endl;
    return;
  }

  for (CORBA::ULong i = 0; i < PL->length(); i++)
  {
    if (PL[i].Id>0) {
       sprintf(caOpStr,"%15s %ld\n%15s %9.2f\n%15s %9.2f\n","POS   I.D.  :-",
	            PL[i].Id,"Total Sales :-",PL[i].TotalSales,"Total Tax   :-",
	            PL[i].TotalTaxes);
       try {
         m_outputMediaRef->OutputText(caOpStr);
       }
       catch(...) {
          cerr << "Error with Output Media" << endl;
          return;
       }
    }
  }
}

//-----------------------------------------------------------------------------
void  POSTerminal_i:: SendBarcode (const char *Item)
{
  if (!LoggedIn())
    return;
  AStore::ItemInfo_var ItemInf;
  CORBA::Float price;
  CORBA::Float taxablePrice;
  delete[] m_itemBarcode;
  m_itemBarcode = new char[strlen(Item) + 1];
  strcpy(m_itemBarcode,Item);

  try
  {
     m_storeAccessRef->FindPrice(m_itemBarcode,m_itemQuantity,
                                 price,taxablePrice,ItemInf);
  }
  catch (const AStore::BarcodeNotFound &e)
  {
     m_itemQuantity = 1;    
     cerr << "Invalid Barcode Found" << endl;
	  return;
  }
  catch(...) {
    m_itemQuantity = 1;
    cerr << "Error in find Price" << endl;
    return;
  }

  CORBA::Float itemExt = (float)m_itemQuantity * price;
  m_saleSubTotal += itemExt;
  
  char caOpStr[255];
  char * szFmtStr;
  szFmtStr = "%3d %10s %20s %7.2f %7.2f %s";
  sprintf(caOpStr,szFmtStr,m_itemQuantity,m_itemBarcode,
          ItemInf->Name,price,itemExt,
     ((taxablePrice > 0.0) ? " *" : "") );
  try
  {
     m_outputMediaRef->OutputText(caOpStr);
  }
  catch (CORBA::Exception &exc)
  {
    cout << "Error with Output Media" << endl;
    return;
  }
  m_saleTaxableSubTotal += taxablePrice * (CORBA::Float)m_itemQuantity;
  m_itemQuantity = 1;
}

//-----------------------------------------------------------------------------
void  POSTerminal_i:: ItemQuantity (CORBA::Long Quantity) 
{
  if (!LoggedIn())
    return;
  if (Quantity > 0)
    m_itemQuantity = Quantity;
}

//-----------------------------------------------------------------------------
void  POSTerminal_i:: EndOfSale () 
{
  char caOpStr[255];
  if (!LoggedIn())
    return;

  sprintf(caOpStr,"Taxable Sub-Total := %8.2f",m_saleTaxableSubTotal);
  m_outputMediaRef->OutputText(caOpStr);
  CORBA::Float saleTax = m_taxRef->CalculateTax(m_saleTaxableSubTotal);
  sprintf(caOpStr,"Taxes             := %8.2f",saleTax);
  m_outputMediaRef->OutputText(caOpStr);
  CORBA::Float saleTotal = saleTax + m_saleSubTotal;
  sprintf(caOpStr,"Total             := %8.2f",saleTotal);
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
  if (m_itemBarcode)
  {
    delete[] m_itemBarcode;
    m_itemBarcode = 0;
  }
  return;
}

unsigned char POSTerminal_i::LoggedIn()
{
  if (CORBA::is_nil(m_storeAccessRef)) {
    cerr << "Need to log in first" << endl;
    return 0;
  }
  else
    return 1;
}
