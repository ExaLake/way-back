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


#ifndef Depot_ih
#define Depot_ih

#include "Central.hh"
#include "PNS.hh"
#include "DepotData.h"

class Depot_i : public CentralOffice::DepotBOAImpl {
  DepotData m_items;
public:
  Depot_i(PseudoNameService_ptr PNS);
  virtual void FindItemInfo (AStore::AStoreId StoreId,
                              const char* Item,      // ###
                              CORBA::Long Quantity,
                              AStore::ItemInfo*& IInfo,
			      CORBA::Environment
			      &It_env=CORBA::default_environment);
};

#endif
