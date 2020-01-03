//	VFWDDECL.H - Forward declarations compatible with the "C" compiler.
//	Copyright (C) 1996-1997 Visio Corporation. All rights reserved.
//

#ifndef _vfwddecl_H
#define _vfwddecl_H

//  ********************************************************************************

//	This is an example of what we want the IFACE_DECL macro to expand to:
//	(Assumes 32-bit or large memory model, i.e. no need for FAR)

//	For C:
//		typedef interface Application Application;
//		typedef Application *LPVISIOAPPLICATION;

//	For C++:
//		interface Application;
//		typedef Application *LPVISIOAPPLICATION;

//  ********************************************************************************

#ifndef __cplusplus
//	Must be the "C" compiler, do it the way "C" understands it:
#define IFACE_DECL(name, ptrName)\
	typedef interface name name;\
	typedef name *ptrName;
#endif

#ifndef IFACE_DECL
//	Compiling with C++ (probably!), do it the way C++ understands it:
#define IFACE_DECL(name, ptrName)\
	interface name;\
	typedef name *ptrName;
#endif

//  ********************************************************************************
//	Forward interface declarations
//		for all of the "ivisprox.h" Visio v4.1 OLE-exposed automation objects

#ifndef VISIO_LPS_FORWARD_DECLARED
#define VISIO_LPS_FORWARD_DECLARED

IFACE_DECL(IVApplication, LPVISIOAPPLICATION)
IFACE_DECL(IVCell,        LPVISIOCELL)
IFACE_DECL(IVCharacters,  LPVISIOCHARS)
IFACE_DECL(IVConnect,     LPVISIOCONNECT)
IFACE_DECL(IVConnects,    LPVISIOCONNECTS)
IFACE_DECL(IVDocument,    LPVISIODOCUMENT)
IFACE_DECL(IVDocuments,   LPVISIODOCUMENTS)
IFACE_DECL(IVMaster,      LPVISIOMASTER)
IFACE_DECL(IVMasters,     LPVISIOMASTERS)
IFACE_DECL(IVPage,        LPVISIOPAGE)
IFACE_DECL(IVPages,       LPVISIOPAGES)
IFACE_DECL(IVSelection,   LPVISIOSELECTION)
IFACE_DECL(IVShape,       LPVISIOSHAPE)
IFACE_DECL(IVShapes,      LPVISIOSHAPES)
IFACE_DECL(IVStyle,       LPVISIOSTYLE)
IFACE_DECL(IVStyles,      LPVISIOSTYLES)
IFACE_DECL(IVWindow,      LPVISIOWINDOW)
IFACE_DECL(IVWindows,     LPVISIOWINDOWS)
IFACE_DECL(IVLayer,       LPVISIOLAYER)
IFACE_DECL(IVLayers,      LPVISIOLAYERS)
IFACE_DECL(IVFont,        LPVISIOFONT)
IFACE_DECL(IVFonts,       LPVISIOFONTS)
IFACE_DECL(IVColor,       LPVISIOCOLOR)
IFACE_DECL(IVColors,      LPVISIOCOLORS)
IFACE_DECL(IVAddon,       LPVISIOADDON)
IFACE_DECL(IVAddons,      LPVISIOADDONS)
IFACE_DECL(IVEvent,       LPVISIOEVENT)
IFACE_DECL(IVEventList,   LPVISIOEVENTS)

//  ********************************************************************************
//	These are only in the v4.2 header file, but need to be forward declared before
//		including "visio.h" when compiling with the compatibility layer in "C"

IFACE_DECL(IVMenuItem,        LPVISIOMENUITEM)
IFACE_DECL(IVMenuItems,       LPVISIOMENUITEMS)
IFACE_DECL(IVMenu,            LPVISIOMENU)
IFACE_DECL(IVMenus,           LPVISIOMENUS)
IFACE_DECL(IVMenuSet,         LPVISIOMENUSET)
IFACE_DECL(IVMenuSets,        LPVISIOMENUSETS)
IFACE_DECL(IVToolbarItem,     LPVISIOTOOLBARITEM)
IFACE_DECL(IVToolbarItems,    LPVISIOTOOLBARITEMS)
IFACE_DECL(IVToolbar,         LPVISIOTOOLBAR)
IFACE_DECL(IVToolbars,        LPVISIOTOOLBARS)
IFACE_DECL(IVToolbarSet,      LPVISIOTOOLBARSET)
IFACE_DECL(IVToolbarSets,     LPVISIOTOOLBARSETS)
IFACE_DECL(IVStatusBarItem,   LPVISIOSTATUSBARITEM)
IFACE_DECL(IVStatusBarItems,  LPVISIOSTATUSBARITEMS)
IFACE_DECL(IVStatusBar,       LPVISIOSTATUSBAR)
IFACE_DECL(IVStatusBars,      LPVISIOSTATUSBARS)
IFACE_DECL(IVAccelItem,       LPVISIOACCELITEM)
IFACE_DECL(IVAccelItems,      LPVISIOACCELITEMS)
IFACE_DECL(IVAccelTable,      LPVISIOACCELTABLE)
IFACE_DECL(IVAccelTables,     LPVISIOACCELTABLES)
IFACE_DECL(IVUIObject,        LPVISIOUIOBJECT)

IFACE_DECL(IEnumVMenuItem,      LPVISIOENUMVMENUITEM);
IFACE_DECL(IEnumVMenu,          LPVISIOENUMVMENU);
IFACE_DECL(IEnumVMenuSet,       LPVISIOENUMVMENUSET);
IFACE_DECL(IEnumVToolbarItem,   LPVISIOENUMVTOOLBARITEM);
IFACE_DECL(IEnumVToolbar,       LPVISIOENUMVTOOLBAR);
IFACE_DECL(IEnumVToolbarSet,    LPVISIOENUMVTOOLBARSET);
IFACE_DECL(IEnumVStatusBarItem, LPVISIOENUMVSTATUSBARITEM);
IFACE_DECL(IEnumVStatusBar,     LPVISIOENUMVSTATUSBAR);
IFACE_DECL(IEnumVAccelItem,     LPVISIOENUMVACCELITEM);
IFACE_DECL(IEnumVAccelTable,    LPVISIOENUMVACCELTABLE);

//  ********************************************************************************
//	New tyepdefs in Visio 5.0:
//	(We still need to update these here so that plain "C" files will compile...)

IFACE_DECL(IVHyperlink,       LPVISIOHYPERLINK);
IFACE_DECL(IVOLEObjects,      LPVISIOOBJECTS);
IFACE_DECL(IVOLEObject,       LPVISIOOBJECT);
IFACE_DECL(IVPaths,           LPVISIOPATHS);
IFACE_DECL(IVPath,            LPVISIOPATH);
IFACE_DECL(IVCurve,           LPVISIOCURVE);


#endif	//	VISIO_LPS_FORWARD_DECLARED

//  ********************************************************************************

#endif	//	_vfwddecl_H
