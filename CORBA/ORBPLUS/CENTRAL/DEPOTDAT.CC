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


#include <iostream.h>
#include "DepotData.h"

// Locate an item in the tree - returning the data contained within it

unsigned long DepotData::Locate(const char* bc, AStore::ItemInfo &i) {
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
    TreeNode *new_node=new TreeNode;
    new_node->m_item=i;
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
// otherwise returns the node off which it should be inserted

unsigned long DepotData::LocateNode(const char* bc, TreeNode * &ret_node) {
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
