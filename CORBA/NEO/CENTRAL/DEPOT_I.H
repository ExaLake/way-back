/********************************************************
 FILE: neo/central/depot_i.h

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
#ifndef depot_ih
#define depot_ih

#include "central.hh"
#include "pnamesvc.hh"
#include "depotdata.h"

class Depot_i: public virtual ODF::Servant {
  DepotData m_items;
public:
  void _initialize_new_Depot(PseudoNameService_ptr pns);
  void find_item_info (AStore::AStoreId store_id,
                              const POS::Barcode item,
                              CORBA::Long quantity,
                              AStore::ItemInfo*& iinfo);
};

#endif
