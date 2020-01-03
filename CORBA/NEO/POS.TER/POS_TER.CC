/********************************************************
 FILE: neo/POS.ter/pos_Ter.cc

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
#include <iostream.h>
#include "odf_output/OdfposcltImpl.hh"
#include <stdlib.h>
#include <ctype.h>
#include "store.hh"


void POSTerminal_i::_initialize_new_POSTerminal(
    				PseudoNameService_ptr pns, CORBA::Long storeid,
    				POS::POSId id) {
  // Load in the stringified object references from the files and
  // construct references to these objects
  char caStr[255];
  try {
    m_taxRef = AStore::Tax::_narrow(pns->Resolve("Tax"));
    sprintf(caStr,"Store_%ld",storeid);
    m_storeRef = AStore::Store::_narrow(pns->Resolve(caStr));
    sprintf(caStr,"OutputMedia_%ld",id);
    m_outputMediaRef = POS::OutputMedia::_narrow(pns->Resolve(caStr));
  }
  catch(...) {
    cerr << "Trouble finding tax, store, or outputmedia " << endl;
  }
  // Initialize the member variables to their appropriate values
  m_itemBarcode = 0;
  m_storeAccessRef = AStore::StoreAccess::_null();
  m_id = id;
  m_POSTaxTotal = m_POSTotal = 0.0;
  m_saleTaxableSubTotal = m_saleSubTotal = 0.0;
}

void  POSTerminal_i:: login () {
  if (!m_storeAccessRef->_is_nil()) {
    cerr << "Can't log in twice" << endl;
    return;
  }
  // Get a reference to the StoreAccess object for this POS
  try {
    m_storeAccessRef = m_storeRef->login(m_id);
  }
  catch(...) {
    cerr << "Error in Login" << endl;
    return;
  }
  m_saleSubTotal = m_POSTotal = m_POSTaxTotal = 0.0;
  m_itemQuantity = 1;
}

void  POSTerminal_i:: print_POS_sales_summary () {
  if (!LoggedIn())
    return;
  if ((m_itemBarcode != 0) || (m_saleSubTotal != 0.0))
    return;
  char caOpStr[255];
  sprintf(caOpStr,"%25s %8.2f\n%25s %8.2f\n","Point of Sale Total := ",
	  m_POSTotal, "Tax Total := ",m_POSTaxTotal);
  try {
    m_outputMediaRef->output_text(caOpStr);
  }
  catch(...) {
    cerr << "Error in Sales Summary" << endl;
  }
}

void  POSTerminal_i:: print_store_sales_summary () {
  if (!LoggedIn())
    return;
  if ((m_itemBarcode != 0) || (m_saleSubTotal != 0.0))
    return;
  char caOpStr[255];

  // Find and output the total sales and tax for the store

  AStore::Store::StoreTotals *tots;
  try {
    tots = m_storeRef->totals();
  }
  catch(...) {
    cerr << "Error finding store totals" << endl;
    return;
  }
  sprintf(caOpStr,"%s %7.2f\n%s %7.2f\n","Total Sales :=",tots->store_total(),
				   "Total Tax   :=",tots->store_tax_total());
  delete tots;
  try {
    m_outputMediaRef->output_text("STORE TOTALS");
    m_outputMediaRef->output_text(caOpStr);
  }
  catch(...) {
    cerr << "Error with Output Media" << endl;
    return;
  }

  // Output the totals for each POS in turn

  AStore::POSList_var PL;
  try {
    m_storeRef->get_POS_totals(PL);
  } catch(...) {
    cerr << "Error Getting Store Totals" << endl;
    return;
  }

  CORBA::ULong i = 0;
  while(i<PL->length()) {
    if ((*PL)[i].id()>0) {
      sprintf(caOpStr,"%15s %ld\n%15s %9.2f\n%15s %9.2f\n",
	      "POS   I.D.  :-", (*PL)[i].id(),
	      "Total Sales :-", (*PL)[i].total_sales(),
	      "Total Tax   :-", (*PL)[i].total_taxes());
      try {
        m_outputMediaRef->output_text(caOpStr);
      }
      catch(...) {
	  cerr << "Error with Output Media" << endl;
	  return;
      }
    }
    i++;
  }
}

void  POSTerminal_i:: send_barcode (const POS::Barcode item) {
  if (!LoggedIn())
    return;
  AStore::ItemInfo_var ItemInf;

  CORBA::Float price;
  CORBA::Float taxablePrice;
  if (m_itemBarcode)
    delete[] m_itemBarcode;
  m_itemBarcode = new char[strlen(item) + 1];
  strcpy(m_itemBarcode,item);

  try {
    m_storeAccessRef->find_price(m_itemBarcode,m_itemQuantity,m_id,
				 price,taxablePrice,ItemInf);
  }
  catch(AStore::BarcodeNotFound bcnf) {
    m_itemQuantity = 1;    
    cerr << "Invalid Barcode Found" << endl;
    return;
  }
  catch(...) {
    m_itemQuantity = 1;
    cerr << "Error in find Price" << endl;
    return;
  }

  CORBA::Float itemExt = (CORBA::Float)m_itemQuantity * ItemInf->itemcost();
  m_saleSubTotal += itemExt;

  char caOpStr[255];
  char * szFmtStr;
  if (taxablePrice > 0.0)
    szFmtStr = "%3d %10s %20s %7.2f %7.2f *";
  else
    szFmtStr = "%3d %10s %20s %7.2f %7.2f";
  sprintf(caOpStr,szFmtStr,m_itemQuantity,m_itemBarcode,ItemInf->name(),
	  ItemInf->itemcost(),itemExt);
  delete ItemInf;
  try {
    m_outputMediaRef->output_text(caOpStr);
  }
  catch(...) {
    cerr << "Error with Output Media" << endl;
    return;
  }
  m_saleTaxableSubTotal += taxablePrice * (CORBA::Float)m_itemQuantity;
  m_itemQuantity = 1;
}

void  POSTerminal_i:: item_quantity (CORBA::Long qty) {
  if (!LoggedIn())
    return;
  if (qty > 0)
    m_itemQuantity = qty;
}

void  POSTerminal_i:: send_barcode_and_quantity (const POS::Barcode item, 
				     CORBA::Long qty) {
  if (!LoggedIn())
    return;
  item_quantity(qty);
  send_barcode(item);
}

void  POSTerminal_i:: end_of_sale () {
  if (!LoggedIn())
    return;
  char caOpStr[255];
  CORBA::Float saleTax;
  CORBA::Float saleTotal;

  sprintf(caOpStr,"Taxable Sub-Total := %8.2f",m_saleTaxableSubTotal);
  m_outputMediaRef->output_text(caOpStr);
  saleTax = m_taxRef->calculate_tax(m_saleTaxableSubTotal);
  sprintf(caOpStr,"Taxes             := %8.2f",saleTax);
  m_outputMediaRef->output_text(caOpStr);
  saleTotal = saleTax + m_saleSubTotal;
  sprintf(caOpStr,"Total             := %8.2f",saleTotal);
  m_outputMediaRef->output_text(caOpStr);
  m_outputMediaRef->output_text("\nGo raibh maith agat\n");
  m_POSTotal += saleTotal;
  m_POSTaxTotal += saleTax;

  try {
    m_storeRef->update_store_totals(m_id,saleTotal,saleTax);
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
  if (m_storeAccessRef->_is_nil()) {
    cerr << "Need to log in first" << endl;
    return 0;
  }
  else
    return 1;
}
