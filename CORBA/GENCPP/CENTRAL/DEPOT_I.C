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
#include <fstream.h>
#include <### PNS interface header file>
#include "Depot_i.h"
#include <FindPNS.h>

const  int   NITEMTYPES=3;

const char *depotdata_file = "depot.dat";

const char *itemtypestext[NITEMTYPES] = {"FOOD","CLOTHES","OTHER"};

Depot_i::Depot_i(PseudoNameService_ptr pns)
{
  AStore::ItemInfo loaditem;
  loaditem.Item = new char[30];
  loaditem.Name = new char[40];
  char tempstring[30];
  int i;
  ifstream is(depotdata_file);
  if (!is)
  {
    cerr << "Could not open depot data file" << depotdata_file << endl;
    return;
  }
  while (!is.eof()) {
    is >> loaditem.Item;
    is >> loaditem.Name;
    is >> loaditem.Quantity;
    is >> loaditem.Itemcost;
    // Read in the string containing the itemtype and convert it to an
    // enumerated value
    is >> tempstring;
    i=0;
    while (i < NITEMTYPES && strcmp(tempstring,itemtypestext[i]) != 0)
      i++;
    if (i < NITEMTYPES)
    {
      loaditem.Itemtype=AStore::ItemTypes(i);
      m_items.Insert(loaditem);
    }
  }
  // Register the object with the name service

  try {
    pns->BindName("Depot", _this());
  }
  catch(...) {
    cerr << "Trouble Binding Depot" << endl;
  }

}

void Depot_i::FindItemInfo (CORBA::Long             StoreId, 
                              const char           *Item, 
                              CORBA::Long           Quantity, 
                              AStore::ItemInfo_out  IInfo)
{
    IInfo = new AStore::ItemInfo;
    if (!m_items.Locate(Item,*IInfo))
    {
       AStore::BarcodeNotFound *bcnf = new AStore::BarcodeNotFound;
       bcnf->item = Item;
       // Raise the exception here
       throw(*bcnf);
    }
}
