/*

Copyright (c) 1995 Expersoft Corporation.  All Rights Reserved.  

Unlimited use, reproduction, and distribution of this software is
permitted.  Any copy of this software must include both the above
copyright notice of Expersoft Corporation and this paragraph.  Any
distribution of this software must comply with all applicable United
States export control laws.  This software is made available AS IS,
and EXPERSOFT CORPORATION DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE, AND NOTWITHSTANDING ANY OTHER
PROVISION CONTAINED HEREIN, ANY LIABILITY FOR DAMAGES RESULTING FROM
THE SOFTWARE OR ITS USE IS EXPRESSLY DISCLAIMED, WHETHER ARISING IN
CONTRACT, TORT (INCLUDING NEGLIGENCE) OR STRICT LIABILITY, EVEN IF
EXPERSOFT CORPORATION IS ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

*/

#ifndef PNDATA_H
#define PNDATA_H

#include <iostream.h>
#include <pbroker/corba/idl.h>

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
