// ShapesInc.cpp
//

#include "stdafx.h"
#include "ShapesInc.h"

// This is the resource --> shape map.
// Each resource has a corresponding shape identifier
// that is used as an index into this array. The value
// at a particular index itself acts as an index into
// the stencil being used to construct the diagram.

// Never use "0" as an index value since it is not
// a valid shape index in Visio.

int g_Shapes[] =
{
	15,		// SHAPEID_GENERIC
	14,		// SHAPEID_DOMAIN
	1,			// SHAPEID_SERVER
	3,			// SHAPEID_SHARE
	4,			// SHAPEID_FILE
	5,			// SHAPEID_GROUP
	8,			// SHAPEID_NETWORK
	14,		// SHAPEID_ROOT
	8,			// SHAPEID_SHAREADMIN
	9,			// SHAPEID_DIRECTORY
	10,		// SHAPEID_TREE
	11,		// SHAPEID_NDSCONTAINER
	29,		// SHAPEID_SHAREDISK
	16			// SHAPEID_SHAREPRINTER
};

///////////////////////////////////////////////////////////////////////////////
// ShapeDynamicConnect
//
// Modifies the supplied connector object so that it connects the src and
// dst shapes.
//
// Params:
// CVisioShape& - connector shape
// CVisioShape& - source
// CVisioShape& - destination
//
// Returns:
// BOOL - TRUE|FALSE success flag
//
// Type:
// global
//
BOOL ShapeDynamicConnect(CVisioShape& connector, CVisioShape& src, CVisioShape& dst)
{
	// This is one area of the Visio model that could be improved.
	// The process of establishing a link between two shapes is
	// too convoluted.
	CVisioCell srcCell;
	CVisioCell dstCell;

	// Using the PinX cell on each shape creates
	// a "dynamic" connector. They differ from
	// normal connectors in that the connection
	// point on each shape can change as the shapes
	// are relocated. This helps to minimize cross-
	// overs by aiding the routing of the connectors.

	ShapeGetCell(connector, _T("BeginX"), srcCell);
	ShapeGetCell(src, _T("PinX"), dstCell);

	srcCell.GlueTo(dstCell);

	ShapeGetCell(connector, _T("EndX"), srcCell);
	ShapeGetCell(dst, _T("PinX"), dstCell);

	srcCell.GlueTo(dstCell);

	// By changing the end arrow head we can make it much
	// clearer the containment relationship.
	ShapeGetCell(connector, _T("EndArrow"), srcCell);
	CellSetFormula(srcCell, _T("4"));

	return(TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// ShapeGetCell
//
// Convenience function that returns a cell object on the supplied shape.
//
// Params:
// CVisioShape&   - shape whose cell is to be retrieved
// const CString& - name of the cell to be retrieved
// CVisioCell&    - retrieved cell
//
// Returns:
// BOOL - TRUE|FALSE success flag
//
// Type:
// global
//
BOOL ShapeGetCell(CVisioShape& shape, const CString& val, CVisioCell& cell)
{
	BSTR cellName = val.AllocSysString();
	HRESULT hr;

	hr = shape.Cells(cellName, cell);

	ASSERT(SUCCEEDED(hr));

	FREE_BSTR(cellName);

	return(SUCCEEDED(hr));
}

///////////////////////////////////////////////////////////////////////////////
// CellSetFormula
//
// Convenience function that sets the formula of the supplied cell.
//
// Params:
// CVisioCell&    - cell
// const CString& - formula
//
// Returns:
// BOOL - TRUE|FALSE success flag
//
// Type:
// global
//
BOOL CellSetFormula(CVisioCell& cell, const CString& val)
{
	BSTR formula = val.AllocSysString();
	HRESULT hr;

	hr = cell.putFormula(formula);

	ASSERT(SUCCEEDED(hr));

	FREE_BSTR(formula);

	return(SUCCEEDED(hr));
}


