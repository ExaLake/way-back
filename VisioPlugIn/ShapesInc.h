// ShapesInc.h
//

#ifndef SHAPESINC_H
#define SHAPESINC_H

#include "visiwrap.h"

#define SHAPEID_DEFAULT				0

#define SHAPEID_GENERIC				0
#define SHAPEID_DOMAIN				1
#define SHAPEID_SERVER				2
#define SHAPEID_SHARE				3
#define SHAPEID_FILE					4
#define SHAPEID_GROUP				5
#define SHAPEID_NETWORK				6
#define SHAPEID_ROOT					7
#define SHAPEID_SHARADMIN			8
#define SHAPEID_DIRECTORY			9
#define SHAPEID_TREE					10
#define SHAPEID_NDSCONTAINER		11
#define SHAPEID_SHAREDISK			12
#define SHAPEID_SHAREPRINTER		13

#define SHAPEID_CONNECTOR			35

extern int g_Shapes[];

// Shape utility functions.
extern BOOL ShapeDynamicConnect(CVisioShape& connector, CVisioShape& src, CVisioShape& dst);
extern BOOL ShapeGetCell(CVisioShape& shape, const CString& val, CVisioCell& cell);
extern BOOL CellSetFormula(CVisioCell& cell, const CString& val);

#endif // SHAPESINC_H
