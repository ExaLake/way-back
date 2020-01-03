/********************************************************
 FILE: neo/central/depotdata.cc

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
#include "depotdata.h"
// Locate an item in the tree - returning the data contained within it
unsigned long DepotData::locate(const POS::Barcode &bc,AStore::ItemInfo* &i) {
  TreeNode *t;
  unsigned long status=locate_node(bc,t);
  if (status)
    i= new AStore::ItemInfo(*t->m_item);
  return status;
}

// Add some information to the tree
void DepotData::insert(const AStore::ItemInfo &i) {
  TreeNode *temp;
  if (!locate_node(i.item(),temp)) {
    TreeNode *new_node=new TreeNode;
    new_node->m_item = new AStore::ItemInfo( i );
    if (m_root==0) {
      m_root=new_node;
      return;
    }
    if (strcmp(i.item(),temp->m_item->item())<0)
      temp->m_left=new_node;
    else
      temp->m_right=new_node;
  }
  else {
    temp->m_item = new AStore::ItemInfo( i );
  }
}

// Locate a node in the tree - returns whether found or not
// If found, ret_node is set to be the node where it was found
// otherwise returns the node off which it should be inserted
unsigned long DepotData::locate_node(const POS::Barcode &bc, TreeNode * &ret_node) {
  int compare;
  ret_node=m_root;
  if (ret_node==0) return 0;
  compare=strcmp(bc,ret_node->m_item->item());
  while (compare!=0) {
    if (compare<0) {
      if (ret_node->m_left==0)
        return 0;
      else
        ret_node=ret_node->m_left;
    }
    else {
      if (ret_node->m_right==0)
        return 0;
      else
        ret_node=ret_node->m_right;
    }
    compare=strcmp(bc,ret_node->m_item->item());
  }
  return 1;
}
