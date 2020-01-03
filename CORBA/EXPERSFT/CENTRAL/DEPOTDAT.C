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

#include "DepotDat.h"

unsigned long DepotData::Locate(const POS::Barcode bc,AStore::ItemInfo &i) {
  TreeNode *t;
  unsigned long status=LocateNode(bc,t);
  if (status)
    i=t->m_item;
  return status;
}

void DepotData::Insert(const AStore::ItemInfo &i) {
  TreeNode *temp;
  const char *s = i.Item;
  if (!LocateNode(s,temp)) {
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

unsigned long DepotData::LocateNode(const POS::Barcode bc, TreeNode * &ret_node) {
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
