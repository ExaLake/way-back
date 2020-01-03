/*

Copyright (C) 1996 by the Object Management Group, Inc.  All  
rights reserved.  

Permission to use, copy, modify, and distribute this software for
any teaching or instructional purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that copyright notice and this permission
notice appear in supporting documentation, and that the names of
Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
(Wiley) not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
assume any liability of any alleged or actual damages arising
from the use of or the inability to use this software.  (Some
states do not allow the exclusion of implied warranties, so the
exclusion may not apply to you.)

*/
#ifndef PNDATA_H
#define PNDATA_H

#include <iostream.h>

struct PNStruct {
  CORBA::Object_var obj;
  char name[80];
};

class TreeNode {
public:
  TreeNode *m_left, *m_right;
  PNStruct m_item;
  
  TreeNode() : m_left(0), m_right(0) {}
};

class PNData {
  TreeNode *m_root;
  virtual unsigned char locate_node(const char *name, TreeNode * &ret_node);
public:
  PNData() : m_root(0) {};
  virtual unsigned char locate(const char *name,CORBA::Object_ptr &obj);
  virtual void insert(const char *name, CORBA::Object_ptr obj);
};

#endif
