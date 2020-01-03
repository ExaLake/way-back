/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 12:17:45 PM
  Comments: XDesignPopupMenu.cpp: implementation of the CXDesignPopupMenu class.
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "XDesignPopupMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Function name	: CXDesignPopupMenu::CXDesignPopupMenu
// Description	    : default Contructor
// Return type		: 
CXDesignPopupMenu::CXDesignPopupMenu(UINT nIDMenu, LPCTSTR lpszPopupName, CPoint p, CWnd* pParentWnd )
{
	m_pPopupMenu = NULL;
	m_point = p;
	m_pParentWnd = pParentWnd;
	VERIFY(LoadMenu(nIDMenu));
	int i = 0;
	CString popupName;
	while (GetMenuString(i, popupName, MF_BYPOSITION)>0)
	{
		if (popupName.CompareNoCase(lpszPopupName) == 0)
		{
			m_pPopupMenu = GetSubMenu(i);
			break;
		}
		i++;
	}
}

// Function name	: CXDesignPopupMenu::~CXDesignPopupMenu
// Description	    : virtual destructor
// Return type		: 
CXDesignPopupMenu::~CXDesignPopupMenu()
{

}

// Function name	: CXDesignPopupMenu::GetPopupMenu
// Description	    : 
// Return type		: CMenu* 
CMenu* CXDesignPopupMenu::GetPopupMenu()
{
	return m_pPopupMenu;
}

// Function name	: CXDesignPopupMenu::Show
// Description	    : Show the popup menu
// Return type		: void 
BOOL CXDesignPopupMenu::Show()
{
	if (CMenu* pMenu = GetPopupMenu())
	{
		pMenu->TrackPopupMenu(TPM_CENTERALIGN, m_point.x ,m_point.y, m_pParentWnd, NULL);
		return TRUE;
	}
	return FALSE;
}
