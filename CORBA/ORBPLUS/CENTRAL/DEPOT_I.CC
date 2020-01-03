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

#include <fstream.h>
#include "Depot_i.h"

const int NITEMTYPES=3;

const char *depotdata_file = "depot.dat";

const char *itemTypesText[NITEMTYPES] = {"FOOD","CLOTHES","OTHER"};

Depot_i::Depot_i(PseudoNameService_ptr PNS, CORBA::Environment& IT_env) {
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
      is >> (char *)loaditem.Item;
      is >> (char *)loaditem.Name;
      is >> loaditem.Quantity;
      is >> loaditem.Itemcost;
      // Read in the string containing the itemtype and convert it to an
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
   CentralOffice::Depot_var DepotObjRef = _this();
   PNS->BindName("Depot", DepotObjRef, IT_env);
}

void Depot_i::FindItemInfo (AStore::AStoreId StoreId,
                              const char* Item,
                              CORBA::Long Quantity, 
                              AStore::ItemInfo*& IInfo,
                              CORBA::Environment &IT_env) {
   IT_env.clear();                  
   IInfo = new AStore::ItemInfo;
   if (m_items.Locate(Item,*IInfo)) {
   }
   else {
      AStore::BarcodeNotFound *bcnf = new AStore::BarcodeNotFound;
      bcnf->item = Item;
      // Raise the exception here
      IT_env.exception(bcnf);  
   }
}
