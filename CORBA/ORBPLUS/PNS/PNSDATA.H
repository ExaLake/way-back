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

#ifndef pntree_h
#define pntree_h

#include <PNSServer.hh>

struct PNStruct {
  CORBA::Object_var obj;
  char name[80];
};

class TreeNode {
public:  
  TreeNode *m_left;
  TreeNode *m_right;
  PNStruct m_item;
  
  TreeNode() : m_left(0), m_right(0) {}
};

class PNData {
  TreeNode *m_root;
  virtual unsigned char LocateNode(const char *name, TreeNode * &ret_node);
public:
  PNData() : m_root(0) {};
  virtual unsigned char Locate(const char *name,CORBA::Object_ptr &obj);
  virtual void Insert(const char *name, CORBA::Object_ptr obj);
};

#endif
