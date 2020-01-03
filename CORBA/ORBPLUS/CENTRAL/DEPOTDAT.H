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



#ifndef depotdata_h
#define depotdata_h

#include "CentralServer.hh"

// The depot stores all info about the products as a binary tree
// This is the basic tree node

class TreeNode {
public:
  TreeNode *m_left;
  TreeNode *m_right;
  AStore::ItemInfo m_item;
  
  TreeNode() : m_left(0), m_right(0) {}
};

class DepotData {
  TreeNode *m_root;
  virtual unsigned long LocateNode(const char* bc, TreeNode * &ret_node);
public:
  DepotData() : m_root(0) {};
  virtual unsigned long Locate(const char* bc,AStore::ItemInfo &i);
  virtual void Insert(const AStore::ItemInfo &i);
};

#endif
