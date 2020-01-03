/* V41OBJS.H - Compatibility Layer file
 * Copyright (C) 1996 Visio Corporation. All rights reserved.
 */

#ifndef _v41objs_H
#define _v41objs_H

#ifdef VISIO_41_COMPATIBILITY_LAYER

//*************************************************************************************

//	This is an example of what we want the IFACE_DECL macro to expand to:
//	(Assumes 32-bit or large memory model, i.e. no need for FAR)

//	For C:
//		typedef interface IVisioApplication IVisioApplication;
//		typedef IVisioApplication *LPVISIOAPPLICATION;

//	For C++:
//		interface IVisioApplication;
//		typedef IVisioApplication *LPVISIOAPPLICATION;

//*************************************************************************************

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

//*************************************************************************************
//	Forward interface declarations
//		for all of the "ivisprox.h" Visio v4.1 OLE-exposed automation objects

#ifndef VISIO_LPS_FORWARD_DECLARED
#define VISIO_LPS_FORWARD_DECLARED

IFACE_DECL(IVisioApplication, LPVISIOAPPLICATION)
IFACE_DECL(IVisioCell,        LPVISIOCELL)
IFACE_DECL(IVisioChars,       LPVISIOCHARS)
IFACE_DECL(IVisioConnect,     LPVISIOCONNECT)
IFACE_DECL(IVisioConnects,    LPVISIOCONNECTS)
IFACE_DECL(IVisioDocument,    LPVISIODOCUMENT)
IFACE_DECL(IVisioDocuments,   LPVISIODOCUMENTS)
IFACE_DECL(IVisioMaster,      LPVISIOMASTER)
IFACE_DECL(IVisioMasters,     LPVISIOMASTERS)
IFACE_DECL(IVisioPage,        LPVISIOPAGE)
IFACE_DECL(IVisioPages,       LPVISIOPAGES)
IFACE_DECL(IVisioSelection,   LPVISIOSELECTION)
IFACE_DECL(IVisioShape,       LPVISIOSHAPE)
IFACE_DECL(IVisioShapes,      LPVISIOSHAPES)
IFACE_DECL(IVisioStyle,       LPVISIOSTYLE)
IFACE_DECL(IVisioStyles,      LPVISIOSTYLES)
IFACE_DECL(IVisioWindow,      LPVISIOWINDOW)
IFACE_DECL(IVisioWindows,     LPVISIOWINDOWS)
IFACE_DECL(IVisioLayer,       LPVISIOLAYER)
IFACE_DECL(IVisioLayers,      LPVISIOLAYERS)
IFACE_DECL(IVisioFont,        LPVISIOFONT)
IFACE_DECL(IVisioFonts,       LPVISIOFONTS)
IFACE_DECL(IVisioColor,       LPVISIOCOLOR)
IFACE_DECL(IVisioColors,      LPVISIOCOLORS)
IFACE_DECL(IVisioAddon,       LPVISIOADDON)
IFACE_DECL(IVisioAddons,      LPVISIOADDONS)
IFACE_DECL(IVisioEvent,       LPVISIOEVENT)
IFACE_DECL(IVisioEvents,      LPVISIOEVENTS)

//*************************************************************************************
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

#endif	//	VISIO_LPS_FORWARD_DECLARED


//	The following #define's map new to old names so that we can use
//	visio.h with existing source code which used to compile against
//	"ivisprox.h":

#define IVApplication IVisioApplication
#define IVCell IVisioCell
#define IVCharacters IVisioChars
#define IVConnect IVisioConnect
#define IVConnects IVisioConnects
#define IVDocument IVisioDocument
#define IVDocuments IVisioDocuments
#define IVMaster IVisioMaster
#define IVMasters IVisioMasters
#define IVPage IVisioPage
#define IVPages IVisioPages
#define IVSelection IVisioSelection
#define IVShape IVisioShape
#define IVShapes IVisioShapes
#define IVStyle IVisioStyle
#define IVStyles IVisioStyles
#define IVWindow IVisioWindow
#define IVWindows IVisioWindows
#define IVLayer IVisioLayer
#define IVLayers IVisioLayers
#define IVFont IVisioFont
#define IVFonts IVisioFonts
#define IVColor IVisioColor
#define IVColors IVisioColors
#define IVAddon IVisioAddon
#define IVAddons IVisioAddons
#define IVEvent IVisioEvent
#define IVEventList IVisioEvents

//	And the IID's...

#define IID_IVApplication IID_IVisioApplication
#define IID_IVCell IID_IVisioCell
#define IID_IVCharacters IID_IVisioChars
#define IID_IVConnect IID_IVisioConnect
#define IID_IVConnects IID_IVisioConnects
#define IID_IVDocument IID_IVisioDocument
#define IID_IVDocuments IID_IVisioDocuments
#define IID_IVMaster IID_IVisioMaster
#define IID_IVMasters IID_IVisioMasters
#define IID_IVPage IID_IVisioPage
#define IID_IVPages IID_IVisioPages
#define IID_IVSelection IID_IVisioSelection
#define IID_IVShape IID_IVisioShape
#define IID_IVShapes IID_IVisioShapes
#define IID_IVStyle IID_IVisioStyle
#define IID_IVStyles IID_IVisioStyles
#define IID_IVWindow IID_IVisioWindow
#define IID_IVWindows IID_IVisioWindows
#define IID_IVLayer IID_IVisioLayer
#define IID_IVLayers IID_IVisioLayers
#define IID_IVFont IID_IVisioFont
#define IID_IVFonts IID_IVisioFonts
#define IID_IVColor IID_IVisioColor
#define IID_IVColors IID_IVisioColors
#define IID_IVAddon IID_IVisioAddon
#define IID_IVAddons IID_IVisioAddons
#define IID_IVEvent IID_IVisioEvent
#define IID_IVEventList IID_IVisioEvents

//*************************************************************************************

#endif	//	VISIO_41_COMPATIBILITY_LAYER

#endif	//	_v41objs_H
