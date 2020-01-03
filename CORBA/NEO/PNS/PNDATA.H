/********************************************************
 FILE: neo/PNS/pndata.h

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
#ifndef pntree_h
#define pntree_h

#include "../compat.hh"
#include <iostream.h>
#include <corba/orb.hh>

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
