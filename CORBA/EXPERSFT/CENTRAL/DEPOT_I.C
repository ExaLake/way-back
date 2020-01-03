/*

Copyright (c) 1995 Expersoft Corporation.  All Rights Reserved.  

Unlimited use, reproduction, and distribution of this software is
permitted.  Any copy of this software must include both the above
copyright notice of Expersoft Corporation and this paragraph.  Any
distribution of this software must comply with all applicable United
States export control laws.  This software is made available AS IS,
and EXPERSOFT CORPORATION DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE, AND NOTWITHSTANDING ANY OTHER
PROVISION CONTAINED HEREIN, ANY LIABILITY FOR DAMAGES RESULTING FROM
THE SOFTWARE OR ITS USE IS EXPRESSLY DISCLAIMED, WHETHER ARISING IN
CONTRACT, TORT (INCLUDING NEGLIGENCE) OR STRICT LIABILITY, EVEN IF
EXPERSOFT CORPORATION IS ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

*/

#include <fstream.h>
#include <PNS.h>
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
