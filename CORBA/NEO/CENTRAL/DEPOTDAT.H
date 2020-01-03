/********************************************************
 FILE: neo/central/DepotData.h

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
#ifndef depotdata_h
#define depotdata_h

#include "central.hh"
#include <stream.h>

// The depot stores all info about the products as a binary tree
// This is the basic tree node

class TreeNode {
public:
  TreeNode *m_left, *m_right;
  AStore::ItemInfo *m_item;
  
  TreeNode() : m_left(0), m_right(0) {}
};

class DepotData {
  TreeNode *m_root;
  virtual unsigned long locate_node(const POS::Barcode &bc, TreeNode * &ret_node);
public:
  DepotData() : m_root(0) {};
  virtual unsigned long locate(const POS::Barcode &bc,AStore::ItemInfo* &i);
  virtual void insert(const AStore::ItemInfo &i);
};

#endif
