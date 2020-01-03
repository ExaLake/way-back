/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 12:02:54 PM
  Comments: XFloorPropertiesWndDesign.h: interface for the CXFloorPropertiesWndDesign class.
 ************************************/

#if !defined(AFX_XFLOORPROPERTIESWNDDESIGN_H__567504B6_6335_11D2_86BB_0040055C08D9__INCLUDED_)
#define AFX_XFLOORPROPERTIESWNDDESIGN_H__567504B6_6335_11D2_86BB_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XFloorPropertiesWnd.h"

class CXFloorPropertiesWndDesign : public CXFloorPropertiesWnd  
{
	friend class CXPropertiesWndPropPage;
public:
	CXFloorPropertiesWndDesign();
	virtual ~CXFloorPropertiesWndDesign();

	virtual BOOL OnCommand( WPARAM wParam, LPARAM lParam );
protected:
	virtual void Fill(CString& stream);
	virtual void DataExchange(CDataExchange* pDX);
	virtual CPageListCtrl* NewPageListCtrl(int nIndex, CXPropertiesWndCtrl* pControl = NULL);

};

#endif // !defined(AFX_XFLOORPROPERTIESWNDDESIGN_H__567504B6_6335_11D2_86BB_0040055C08D9__INCLUDED_)
