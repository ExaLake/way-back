// NetworkResource.h: interface for the CNetworkResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKRESOURCE_H__C855318B_17FC_11D3_B3C5_00105A98B108__INCLUDED_)
#define AFX_NETWORKRESOURCE_H__C855318B_17FC_11D3_B3C5_00105A98B108__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "visiwrap.h"
#include <list>

class CNetworkResource;

//////////////////////////////////////////////////////////////////////
// CNetworkResource
//

class CNetworkResource
{
public:		// C'tor/d'tor
	CNetworkResource();
	CNetworkResource(NETRESOURCE* buffer);
	virtual ~CNetworkResource();

private:
	CVisioShape m_Shape;
	std::list<CNetworkResource*> m_Resources;
	CString m_DisplayName;
	DWORD m_DisplayType;
	DWORD m_Type;

public:		// Operations.
	BOOL Display(CVisioPage& page, CVisioMasters& masters);
	void AddResource(CNetworkResource* nr);
	UINT GetShapeId();

public:		// Properties.
	inline void SetDisplayType(DWORD val);
	inline DWORD GetDisplayType();
	inline void SetDisplayName(LPTSTR val);
	inline CString GetDisplayName();
	inline void SetType(DWORD val);
	inline DWORD GetType();
	inline CVisioShape& GetShape();
};

// Inline definitions.
#include "NetworkResource.inl"

#endif // !defined(AFX_NETWORKRESOURCE_H__C855318B_17FC_11D3_B3C5_00105A98B108__INCLUDED_)
