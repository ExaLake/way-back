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

#include "PNSData.h"
#include <string.h>

// Locate an item in the tree - returning the data contained within it

unsigned char PNData::locate(const char *name, CORBA::Object_ptr &obj) {
  TreeNode *t;
  unsigned long status=locate_node(name,t);
  if (status)
    obj=t->m_item.obj;
  return status;
}

// Add some information to the tree
// If the data was there already - replace the previous entry
// otherwise returns the node off which it should be inserted

void PNData::insert(const char *name, CORBA::Object_ptr obj) {
  TreeNode *temp;
  if (!locate_node(name,temp)) {
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

unsigned char PNData::locate_node(const char *name, TreeNode * &ret_node) {
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
