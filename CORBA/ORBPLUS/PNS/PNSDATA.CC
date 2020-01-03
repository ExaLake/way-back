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


#include <string.h>
#include "PNSData.h"

// Locate an item in the tree - returning the data contained within it

unsigned char PNData::Locate(const char *name, CORBA::Object_ptr &obj) {
  TreeNode *t;
  unsigned long status=LocateNode(name,t);
  if (status)
    obj=t->m_item.obj;
  return status;
}

// Add some information to the tree
// If the data was there already - replace the previous entry
// otherwise returns the node off which it should be inserted

void PNData::Insert(const char *name, CORBA::Object_ptr obj) {
  TreeNode *temp;
  if (!LocateNode(name,temp)) {
    TreeNode *new_node=new TreeNode;
    strcpy(new_node->m_item.name,name);
    new_node->m_item.obj=obj;
    if (m_root==0) {
      m_root=new_node;
      return;
    }
    if (strcmp(name,temp->m_item.name)<0)
      temp->m_left=new_node;
    else
      temp->m_right=new_node;
  }
  else {
    CORBA::release(temp->m_item.obj);
    temp->m_item.obj=obj;
  }
}

// Locate a node in the tree - returns whether found or not
// If found, ret_node is set to be the node where it was found

unsigned char PNData::LocateNode(const char *name, TreeNode * &ret_node) {
  int compare;
  ret_node=m_root;
  if (ret_node==0) return 0;
  compare=strcmp(name,ret_node->m_item.name);
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
    compare=strcmp(name,ret_node->m_item.name);
  }
  return 1;
}
