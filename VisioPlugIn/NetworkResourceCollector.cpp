// NetworkResourceCollector.cpp: implementation of the CNetworkResourceCollector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VNetInfo.h"
#include "visiwrap.h"
#include "NetInfo.h"
#include "NetworkResourceCollector.h"
#include "NetworkResource.h"
#include "ShapesInc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CNetworkResourceCollector::CNetworkResourceCollector(VNetInfo* addon)
{
	m_Addon = addon;

	m_RootResource = new CNetworkResource();
}

CNetworkResourceCollector::~CNetworkResourceCollector()
{
	DeleteNetworkResources();
}

BOOL CNetworkResourceCollector::Run()
{
	Collect(m_RootResource);
	Display();

	return(TRUE);
}

BOOL CNetworkResourceCollector::Collect(CNetworkResource* parent, NETRESOURCE* nr /* NULL */)
{
	HANDLE enumHandle = 0;
	DWORD rc = 0;

	rc = ::WNetOpenEnum(
		RESOURCE_GLOBALNET,
		RESOURCETYPE_ANY,
		0,							// ignored
		nr,
		&enumHandle);

	if(NO_ERROR == rc)
	{
		NETRESOURCE* buffer = NULL;
		DWORD bufferSize = 0;
		
		bufferSize = sizeof(NETRESOURCE);

		buffer = (NETRESOURCE*) malloc(bufferSize);

		ASSERT(NULL != buffer);

		::ZeroMemory(buffer, bufferSize);

		do
		{
			DWORD count = 1;

			rc = ::WNetEnumResource(
				enumHandle,
				&count,
				buffer,
				&bufferSize);

			switch(rc)
			{
			case NO_ERROR:
				{
					// buffer now describes a single network resource.
					CNetworkResource* res = CreateNetworkResource(buffer);

					ASSERT(NULL != res);

					parent->AddResource(res);

					Collect(res, buffer);

					break;
				}

			case ERROR_MORE_DATA:
				// For clarity I am not protecting against
				// realloc returning NULL - should it do
				// so then we'll lose the memory already
				// allocated to buffer. Be warned!
				buffer = (NETRESOURCE*) realloc(buffer, bufferSize);

				ASSERT(NULL != buffer);

				ZeroMemory(buffer, bufferSize);

				break;

			default:
				break;
			}
		} while(ERROR_NO_MORE_ITEMS != rc);

		free(buffer);
		buffer = NULL;

		::WNetCloseEnum(enumHandle);
	}

	return(TRUE);
}

BOOL CNetworkResourceCollector::Display()
{
	CVisioApplication app;

	m_Addon->GetApp(app);

	CVisioDocuments documents;
	HRESULT hr;

	hr = app.Documents(documents);

	if(SUCCEEDED(hr))
	{
		CVisioDocument document;
		BSTR filename = CString("Basic Network.vst").AllocSysString();

		hr = documents.Add(filename, document);

		FREE_BSTR(filename);;

		if(SUCCEEDED(hr))
		{
			CVisioMasters masters;
			short documentsCount;

			documents.Count(&documentsCount);

			for(int i = 1; i <= documentsCount; i++)
			{
				CVisioDocument document;

				documents.Item(COleVariant((long) i), document);

				BSTR bstrName;
				CString name;

				document.Name(bstrName);
				name = bstrName;

				FREE_BSTR(bstrName);

				TRACE1("%s\n", name);

				// We're looking for this specific stencil.
				if(-1 != name.Find("basic network shapes.vss"))
				{
					document.Masters(masters);

					break;
				}
			}

			CVisioPages pages;

			hr = document.Pages(pages);

			if(SUCCEEDED(hr))
			{
				CVisioPage page;

				hr = pages.Item(COleVariant((long) 1), page);

				if(SUCCEEDED(hr))
				{
					m_RootResource->Display(page, masters);

					Layout(page);
				}
			}
		}
	}

	return(SUCCEEDED(hr));
}

CNetworkResource* CNetworkResourceCollector::CreateNetworkResource(NETRESOURCE* buffer)
{
	ASSERT(NULL != buffer);

	CNetworkResource* nr = new CNetworkResource(buffer);

	ASSERT(NULL != nr);

	return(nr);
}

void CNetworkResourceCollector::DeleteNetworkResources()
{
	delete m_RootResource;
	m_RootResource = NULL;
}

BOOL CNetworkResourceCollector::Layout(CVisioPage& page)
{
	HRESULT hr;

	CVisioShape shape;

	hr = page.PageSheet(shape);

	ASSERT(SUCCEEDED(hr));

	CVisioCell cell;

	ShapeGetCell(shape, _T("User.visControlsAsInputs"), cell);
	CellSetFormula(cell, _T("0"));

	ShapeGetCell(shape, _T("User.visPlacementStyle"), cell);
	CellSetFormula(cell, _T("1"));

	ShapeGetCell(shape, _T("User.visPlacementDepth"), cell);
	CellSetFormula(cell, _T("1"));

	ShapeGetCell(shape, _T("User.visRoutingStyle"), cell);
	CellSetFormula(cell, _T("7"));

	ShapeGetCell(shape, _T("User.visResize"), cell);
	CellSetFormula(cell, _T("-1"));

	page.Layout();

	return(TRUE);
}
