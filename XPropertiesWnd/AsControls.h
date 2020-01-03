/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 1:56:05 PM
  Comments: AsControls.h: interface for the CAsControls class.
 ************************************/

#if !defined(AFX_ASCONTROLS_H__567504B9_6335_11D2_86BB_0040055C08D9__INCLUDED_)
#define AFX_ASCONTROLS_H__567504B9_6335_11D2_86BB_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define PROTECTED FALSE

#include <afxTempl.h>

class CAsControls  
{
public:
	virtual UINT GetID(LPCTSTR lpszAs);
	virtual LPCTSTR GetName(UINT idAs);
	CAsControls();
	virtual ~CAsControls();
protected:
	virtual void RemoveAll();
	virtual void Add(UINT id, LPCTSTR lpszAs, BOOL bEnable = TRUE);
	CMap<UINT,UINT,CString*, CString*> m_mapControls;
	CMapStringToOb m_mapControlsString;
};

#endif // !defined(AFX_ASCONTROLS_H__567504B9_6335_11D2_86BB_0040055C08D9__INCLUDED_)
