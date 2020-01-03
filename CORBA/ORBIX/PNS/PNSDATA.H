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

#ifndef pntree_h
#define pntree_h

#include <PNS.hh>

struct PNStruct {
  CORBA::Object_var obj;
  char name[80];
};

class TreeNode {
public:
  TreeNode* m_left;
  TreeNode* m_right;
  PNStruct m_item;
  
  TreeNode() : m_left(0), m_right(0) {}
};

class PNData {
  TreeNode* m_root;
  virtual unsigned char LocateNode(const char* name, TreeNode*& ret_node);
public:
  PNData() : m_root(0) {};
  virtual unsigned char Locate(const char* name,CORBA::Object_ptr& obj);
  virtual void Insert(const char* name, CORBA::Object_ptr obj);
};

#endif
