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

#include <iostream.h>
#include "DepotData.h"

// Locate an item in the tree - returning the data contained within it

unsigned long DepotData::Locate(const char* bc, AStore::ItemInfo &i) { //###
  TreeNode *t;
  unsigned long status=LocateNode(bc,t);
  if (status)
    i=t->m_item;
  return status;
}

// Add some information to the tree

void DepotData::Insert(const AStore::ItemInfo &i) {
  TreeNode *temp;
  if (!LocateNode(i.Item,temp)) {
    TreeNode *new_node = new TreeNode;
    new_node->m_item = i;
    if (m_root==0) {
      m_root=new_node;
      return;
    }
    if (strcmp(i.Item,temp->m_item.Item)<0)
      temp->m_left=new_node;
    else
      temp->m_right=new_node;
  }
  else {
    temp->m_item=i;
  }
}

// Locate a node in the tree - returns whether found or not
// If found, ret_node is set to be the node where it was found
// otherwise returns the node off which it should be Inserted
unsigned long DepotData::LocateNode(const char* bc, TreeNode * &ret_node) { // ###
  int compare;
  ret_node=m_root;
  if (ret_node==0) return 0;
  compare=strcmp(bc,ret_node->m_item.Item);
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
    compare=strcmp(bc,ret_node->m_item.Item);
  }
  return 1;
}
