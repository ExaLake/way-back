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

#include <fstream.h>
#include "Depot_i.h"

const int NITEMTYPES=3;

const char *depotdata_file = "depot.dat";

const char *itemTypesText[NITEMTYPES] = {"FOOD","CLOTHES","OTHER"};

Depot_i::Depot_i(PseudoNameService_ptr PNS) {
  AStore::ItemInfo loaditem;
  loaditem.Item = new char[30];
  loaditem.Name = new char[40];
  char tempstring[30];
  int i;
  ifstream is(depotdata_file);
  if (!is) {
    cerr << "Could not open depot data file " << depotdata_file << endl;
    return;
  }
  while (!is.eof()) {
    is >> loaditem.Item;
    is >> loaditem.Name;
    is >> loaditem.Quantity;
    is >> loaditem.Itemcost;
    // Read in the string containing the item type and convert it to an
    // enumerated value
    is >> tempstring;
    i=0;
    while (i < NITEMTYPES && strcmp(tempstring,itemTypesText[i]) != 0)
      i++;
    if (i < NITEMTYPES) {
      loaditem.Itemtype=AStore::ItemTypes(i);
      m_items.Insert(loaditem);
    }
  }
  // Register the object with the name service
  try {
    PNS->BindName("Depot",this);
  }
  catch(...) {
    cerr << "Trouble Binding the Depot" << endl;
  }
}

void Depot_i::FindItemInfo (AStore::AStoreId StoreId,
                              const char* Item,   // ###
                              CORBA::Long Quantity, 
                              AStore::ItemInfo*& IInfo,
			      CORBA::Environment &IT_env) {
    IInfo = new AStore::ItemInfo;
    if (m_items.Locate(Item,*IInfo)) {
    }
    else {
      // Raise the exception here
      throw(AStore::BarcodeNotFound(Item));
    }
}
