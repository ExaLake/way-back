/********************************************************
 FILE: neo/depot/depot_i.cc

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
#include "odf_output/OdfdepotImpl.hh"
#include <stream.h>

const int NITEMTYPES=3;

const char *depotdata_file = "depot.dat";

const char *itemtypestext[NITEMTYPES] = {"FOOD","CLOTHES","OTHER"};


void
Depot_i::_initialize_new_Depot(PseudoNameService_ptr pns) {
  AStore::ItemInfo loaditem;
  loaditem.item(CORBA::string_allocate(30));
  loaditem.name(CORBA::string_allocate(40));
  char tempstring[30];
  int i;
  ifstream is(depotdata_file);
  if (!is) {
    cerr << "Could not open depot data file" << depotdata_file << endl;
    return;
  }
  while (!is.eof()) {
    is >> loaditem.item();
    is >> loaditem.name();
    is >> loaditem.quantity();
    is >> loaditem.itemcost();
    // Read in the string containing the itemtype and convert it to an
    // enumerated value
    is >> tempstring;
    i=0;
    while (i < NITEMTYPES && strcmp(tempstring,itemtypestext[i]) != 0)
      i++;
    if (i < NITEMTYPES) {
      loaditem.itemtype()=AStore::ItemTypes(i);
      m_items.insert(loaditem);
    }
  }
  // Register the object with the name service
  try {
    pns->Bind("Depot",_servant_objref());
  }
  catch(...) {
    cerr << "Trouble Binding Depot" << endl;
  }
}

void Depot_i::find_item_info (AStore::AStoreId store_id,
                              const POS::Barcode item,
                              CORBA::Long quantity, 
                              AStore::ItemInfo*& iinfo) {
    iinfo = new AStore::ItemInfo;
    if (m_items.locate(item,iinfo)) {
    }
    else {
      AStore::BarcodeNotFound *bcnf = new AStore::BarcodeNotFound;
      bcnf->item() = item;
      // Raise the exception here
      throw(bcnf);
    }
}
