// NetworkResourceCollector.h: interface for the CNetworkResourceCollector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKRESOURCECOLLECTOR_H__C855318A_17FC_11D3_B3C5_00105A98B108__INCLUDED_)
#define AFX_NETWORKRESOURCECOLLECTOR_H__C855318A_17FC_11D3_B3C5_00105A98B108__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <list>

class VNetInfo;
class CNetworkResource;

//////////////////////////////////////////////////////////////////////
// CNetworkResourceCollector
//

class CNetworkResourceCollector  
{
public:		// C'tor/d'tor.
	CNetworkResourceCollector(VNetInfo* addon);
	~CNetworkResourceCollector();

public:		// Operations.
	BOOL Run();

private:		// Implementation.
	BOOL Layout(CVisioPage& page);
	void DeleteNetworkResources();
	CNetworkResource* CreateNetworkResource(NETRESOURCE* buffer);
	BOOL Display();
	BOOL Collect(CNetworkResource* parent, NETRESOURCE* nr = NULL);
	VNetInfo* m_Addon;

	// Having a "special" root object makes the Collect
	// code simpler.
	CNetworkResource* m_RootResource;

public:
#ifdef _DEBUG
	void Dump();
#else
#define Dump()
#endif // _DEBUG
};

#endif // !defined(AFX_NETWORKRESOURCECOLLECTOR_H__C855318A_17FC_11D3_B3C5_00105A98B108__INCLUDED_)
