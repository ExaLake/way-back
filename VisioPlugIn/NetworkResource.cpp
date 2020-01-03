// NetworkResource.cpp: implementation of the CNetworkResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetInfo.h"
#include "NetworkResource.h"
#include "ShapesInc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetworkResource::CNetworkResource()
{
	// Properties.
	SetDisplayName(_T("The Network Universe"));
	SetDisplayType(-1);
	SetType(-1);
}

CNetworkResource::CNetworkResource(NETRESOURCE* buffer)
{
	// Store only the elements we need from the NETRESOURCE
	// struct.
	SetDisplayName(buffer->lpRemoteName);
	SetDisplayType(buffer->dwDisplayType);
	SetType(buffer->dwType);
}


CNetworkResource::~CNetworkResource()
{
	std::list<CNetworkResource*>::iterator i;

	for(i = m_Resources.begin(); i != m_Resources.end();)
	{
		CNetworkResource* nr = *i++;

		delete nr;
		nr = NULL;
	}

	m_Resources.clear();
}

void CNetworkResource::AddResource(CNetworkResource* nr)
{
	ASSERT(NULL != nr);

	m_Resources.push_back(nr);
}

UINT CNetworkResource::GetShapeId()
{
	UINT id = SHAPEID_DEFAULT;

	switch(GetDisplayType())
	{
	case RESOURCEDISPLAYTYPE_GENERIC:
		id = SHAPEID_GENERIC;
		break;

	case RESOURCEDISPLAYTYPE_DOMAIN:
		id = SHAPEID_DOMAIN;
		break;

	case RESOURCEDISPLAYTYPE_SERVER:
		id = SHAPEID_SERVER;
		break;

	case RESOURCEDISPLAYTYPE_SHARE:
		switch(GetType())
		{
		case RESOURCETYPE_DISK:
			id = SHAPEID_SHAREDISK;
			break;

		case RESOURCETYPE_PRINT:
			id = SHAPEID_SHAREPRINTER;
			break;

		default:
			id = SHAPEID_SHARE;
			break;
		}
		break;

	case RESOURCEDISPLAYTYPE_FILE:
		id = SHAPEID_FILE;
		break;

	case RESOURCEDISPLAYTYPE_GROUP:
		id = SHAPEID_GROUP;
		break;

#if(WINVER >= 0x0400)

	case RESOURCEDISPLAYTYPE_NETWORK:
		id = SHAPEID_NETWORK;
		break;

	case RESOURCEDISPLAYTYPE_ROOT:
		id = SHAPEID_ROOT;
		break;

	case RESOURCEDISPLAYTYPE_SHAREADMIN:
		id = SHAPEID_SHARADMIN;
		break;

	case RESOURCEDISPLAYTYPE_DIRECTORY:
		id = SHAPEID_DIRECTORY;
		break;

#endif /* WINVER >= 0x0400 */

	case RESOURCEDISPLAYTYPE_TREE:
		id = SHAPEID_TREE;
		break;

#if(WINVER >= 0x0400)

	case RESOURCEDISPLAYTYPE_NDSCONTAINER:
		id = SHAPEID_NDSCONTAINER;
		break;

#endif /* WINVER >= 0x400 */

	default:
		// Uses default shape.
		break;
	}

	return(g_Shapes[id]);
}

BOOL CNetworkResource::Display(CVisioPage& page, CVisioMasters& masters)
{
	CVisioMaster master;
	HRESULT hr;
	long id = GetShapeId();

	double x = 0.0;
	double y = 0.0;

	if(id > 0)
	{
		hr = masters.Item(COleVariant((long) GetShapeId()), master);

		hr = page.Drop(master, x, y, m_Shape);

		ASSERT(SUCCEEDED(hr));

		m_Shape.putText(VBstr(GetDisplayName()));
	}

	std::list<CNetworkResource*>::iterator i;

	for(i = m_Resources.begin(); i != m_Resources.end();)
	{
		CNetworkResource* nr = *i++;

		nr->Display(page, masters);

		// Connect this shape to all its children.
		hr = masters.Item(COleVariant(_T("Dynamic Connector")), master);

		if(SUCCEEDED(hr))
		{
			CVisioShape shape;

			hr = page.Drop(master, x, y, shape);

			ShapeDynamicConnect(shape, m_Shape, nr->GetShape());
		}
	}

	return(SUCCEEDED(hr));
}

