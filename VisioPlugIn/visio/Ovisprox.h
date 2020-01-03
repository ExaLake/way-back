/* OVISPROX.H - Visio Automation Interface Declarations
 * Copyright (C) 1991-1996 Visio Corporation. All rights reserved.
 */

//	This file is the old (Visio 4.1 and earlier) IVISPROX.H


#ifndef _OVISPROX_H
#define _OVISPROX_H

#define _IVISPROX_H

#pragma message("Including ovisprox.h...")

#ifdef __cplusplus
#define IFACE_DECL(iface, ptr)\
interface iface;              \
typedef iface FAR * ptr;
#else
#define IFACE_DECL(iface, ptr)\
typedef interface iface iface;\
typedef iface FAR * ptr;
#endif

IFACE_DECL(IVisioApplication, LPVISIOAPPLICATION)
IFACE_DECL(IVisioCell, LPVISIOCELL)
IFACE_DECL(IVisioChars, LPVISIOCHARS)
IFACE_DECL(IVisioConnect, LPVISIOCONNECT)
IFACE_DECL(IVisioConnects, LPVISIOCONNECTS)
IFACE_DECL(IVisioDocument, LPVISIODOCUMENT)
IFACE_DECL(IVisioDocuments, LPVISIODOCUMENTS)
IFACE_DECL(IVisioMaster, LPVISIOMASTER)
IFACE_DECL(IVisioMasters, LPVISIOMASTERS)
IFACE_DECL(IVisioPage, LPVISIOPAGE)
IFACE_DECL(IVisioPages, LPVISIOPAGES)
IFACE_DECL(IVisioSelection, LPVISIOSELECTION)
IFACE_DECL(IVisioShape, LPVISIOSHAPE)
IFACE_DECL(IVisioShapes, LPVISIOSHAPES)
IFACE_DECL(IVisioStyle, LPVISIOSTYLE)
IFACE_DECL(IVisioStyles, LPVISIOSTYLES)
IFACE_DECL(IVisioWindow, LPVISIOWINDOW)
IFACE_DECL(IVisioWindows, LPVISIOWINDOWS)
IFACE_DECL(IVisioLayer, LPVISIOLAYER)
IFACE_DECL(IVisioLayers, LPVISIOLAYERS)
IFACE_DECL(IVisioFont, LPVISIOFONT)
IFACE_DECL(IVisioFonts, LPVISIOFONTS)
IFACE_DECL(IVisioColor, LPVISIOCOLOR)
IFACE_DECL(IVisioColors, LPVISIOCOLORS)
IFACE_DECL(IVisioAddon, LPVISIOADDON)
IFACE_DECL(IVisioAddons, LPVISIOADDONS)
IFACE_DECL(IVisioEvent, LPVISIOEVENT)
IFACE_DECL(IVisioEvents, LPVISIOEVENTS)

#undef  INTERFACE
#define INTERFACE   IVisioApplication

DECLARE_INTERFACE_(IVisioApplication , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioApplication methods ***
    STDMETHOD(ActiveDocument)       (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(ActivePage)           (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(ActiveWindow)         (THIS_ LPVISIOWINDOW FAR * lpdispRet) PURE;
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Documents)            (THIS_ LPVISIODOCUMENTS FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getOnDataChangeDelay) (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(putOnDataChangeDelay) (THIS_ long Delay) PURE;
    STDMETHOD(ProcessID)            (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(Quit)                 (THIS) PURE;
    STDMETHOD(Redo)                 (THIS) PURE;
    STDMETHOD(getScreenUpdating)    (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putScreenUpdating)    (THIS_ short OnOrOff) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Undo)                 (THIS) PURE;
    STDMETHOD(Version)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(WindowHandle)         (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Windows)              (THIS_ LPVISIOWINDOWS FAR * lpdispRet) PURE;
    STDMETHOD(Language)             (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(IsVisio16)            (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(IsVisio32)            (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(WindowHandle32)       (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(InstanceHandle)       (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(InstanceHandle32)     (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(BuiltInMenus)         (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(BuiltInToolbars)      (THIS_ short fWhichToolbars, LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(CustomMenus)          (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(SetCustomMenus)       (THIS_ LPUNKNOWN MenusObject) PURE;
    STDMETHOD(getCustomMenusFile)   (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putCustomMenusFile)   (THIS_ BSTR FileName) PURE;
    STDMETHOD(ClearCustomMenus)     (THIS) PURE;
    STDMETHOD(CustomToolbars)       (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(SetCustomToolbars)    (THIS_ LPUNKNOWN ToolbarsObject) PURE;
    STDMETHOD(getCustomToolbarsFile) (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putCustomToolbarsFile) (THIS_ BSTR FileName) PURE;
    STDMETHOD(ClearCustomToolbars)  (THIS) PURE;
    STDMETHOD(getAddonPaths)        (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putAddonPaths)        (THIS_ BSTR PathsString) PURE;
    STDMETHOD(getDrawingPaths)      (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putDrawingPaths)      (THIS_ BSTR PathsString) PURE;
    STDMETHOD(getFilterPaths)       (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putFilterPaths)       (THIS_ BSTR PathsString) PURE;
    STDMETHOD(getHelpPaths)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putHelpPaths)         (THIS_ BSTR PathsString) PURE;
    STDMETHOD(getStartupPaths)      (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putStartupPaths)      (THIS_ BSTR PathsString) PURE;
    STDMETHOD(getStencilPaths)      (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putStencilPaths)      (THIS_ BSTR PathsString) PURE;
    STDMETHOD(getTemplatePaths)     (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putTemplatePaths)     (THIS_ BSTR PathsString) PURE;
    STDMETHOD(getUserName)          (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putUserName)          (THIS_ BSTR UserName) PURE;
    STDMETHOD(getPromptForSummary)  (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPromptForSummary)  (THIS_ short OnOrOff) PURE;
    STDMETHOD(Addons)               (THIS_ LPVISIOADDONS FAR * lpdispRet) PURE;
    STDMETHOD(SaveWorkspaceAs)      (THIS_ BSTR FileName) PURE;
    STDMETHOD(DoCmd)                (THIS_ short CommandID) PURE;
    STDMETHOD(ProfileName)          (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(EventInfo)            (THIS_ long EventSeqNum, BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(Active)               (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(getDeferRecalc)       (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putDeferRecalc)       (THIS_ short OnOrOff) PURE;
    STDMETHOD(getAlertResponse)     (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putAlertResponse)     (THIS_ short Response) PURE;
    STDMETHOD(getShowProgress)      (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putShowProgress)      (THIS_ short OnOrOff) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioCell

DECLARE_INTERFACE_(IVisioCell , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioCell methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Error)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getFormula)           (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putFormula)           (THIS_ BSTR Formula) PURE;
    STDMETHOD(FormulaForce)         (THIS_ BSTR Formula) PURE;
    STDMETHOD(GlueTo)               (THIS_ LPVISIOCELL CellObject) PURE;
    STDMETHOD(GlueToPos)            (THIS_ LPVISIOSHAPE SheetObject, double xPercent, double yPercent) PURE;
    STDMETHOD(getResult)            (THIS_ VARIANT UnitsNameOrCode, double FAR * lpr8Ret) PURE;
    STDMETHOD(putResult)            (THIS_ VARIANT UnitsNameOrCode, double Value) PURE;
    STDMETHOD(ResultForce)          (THIS_ VARIANT UnitsNameOrCode, double Value) PURE;
    STDMETHOD(getResultIU)          (THIS_ double FAR * lpr8Ret) PURE;
    STDMETHOD(putResultIU)          (THIS_ double Value) PURE;
    STDMETHOD(ResultIUForce)        (THIS_ double Value) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Units)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Name)                 (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(LocalName)            (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putRowName)           (THIS_ BSTR RowName) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Shape)                (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Style)                (THIS_ LPVISIOSTYLE FAR * lpdispRet) PURE;
    STDMETHOD(Section)              (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Row)                  (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Column)               (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(IsConstant)           (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(IsInherited)          (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(getResultInt)         (THIS_ VARIANT UnitsNameOrCode, short fRound, long FAR * lpi4Ret) PURE;
    STDMETHOD(putResultInt)         (THIS_ VARIANT UnitsNameOrCode, long Value) PURE;
    STDMETHOD(ResultIntForce)       (THIS_ VARIANT UnitsNameOrCode, long Value) PURE;
    STDMETHOD(ResultStr)            (THIS_ VARIANT UnitsNameOrCode, BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(Trigger)              (THIS) PURE;
    STDMETHOD(getRowName)           (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioChars

DECLARE_INTERFACE_(IVisioChars , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioChars methods ***
    STDMETHOD(AddCustomField)       (THIS_ BSTR Formula, short Format) PURE;
    STDMETHOD(AddField)             (THIS_ short Category, short Code, short Format) PURE;
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(getBegin)             (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(putBegin)             (THIS_ long IPIndex) PURE;
    STDMETHOD(CharCount)            (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(CharProps)            (THIS_ short CellIndex, short Value) PURE;
    STDMETHOD(CharPropsRow)         (THIS_ short BiasLorR, short FAR * lpi2Ret) PURE;
    STDMETHOD(Copy)                 (THIS) PURE;
    STDMETHOD(Cut)                  (THIS) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getEnd)               (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(putEnd)               (THIS_ long IPIndex) PURE;
    STDMETHOD(FieldCategory)        (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(FieldCode)            (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(FieldFormat)          (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(FieldFormula)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(IsField)              (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ParaProps)            (THIS_ short CellIndex, short Value) PURE;
    STDMETHOD(ParaPropsRow)         (THIS_ short BiasLorR, short FAR * lpi2Ret) PURE;
    STDMETHOD(Paste)                (THIS) PURE;
    STDMETHOD(TabPropsRow)          (THIS_ short BiasLorR, short FAR * lpi2Ret) PURE;
    STDMETHOD(RunBegin)             (THIS_ short RunType, long FAR * lpi4Ret) PURE;
    STDMETHOD(RunEnd)               (THIS_ short RunType, long FAR * lpi4Ret) PURE;
    STDMETHOD(Shape)                (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getText)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putText)              (THIS_ VARIANT StrCharsOrSheet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioConnect

DECLARE_INTERFACE_(IVisioConnect , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioConnect methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(FromSheet)            (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(ToSheet)              (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(FromCell)             (THIS_ LPVISIOCELL FAR * lpdispRet) PURE;
    STDMETHOD(ToCell)               (THIS_ LPVISIOCELL FAR * lpdispRet) PURE;
    STDMETHOD(FromPart)             (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ToPart)               (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioConnects

DECLARE_INTERFACE_(IVisioConnects , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioConnects methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Item)                 (THIS_ short Index, LPVISIOCONNECT FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(FromSheet)            (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ToSheet)              (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioDocument

DECLARE_INTERFACE_(IVisioDocument , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioDocument methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(InPlace)              (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Masters)              (THIS_ LPVISIOMASTERS FAR * lpdispRet) PURE;
    STDMETHOD(Pages)                (THIS_ LPVISIOPAGES FAR * lpdispRet) PURE;
    STDMETHOD(Styles)               (THIS_ LPVISIOSTYLES FAR * lpdispRet) PURE;
    STDMETHOD(Name)                 (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(Path)                 (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(FullName)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(Drop)                 (THIS_ LPUNKNOWN ObjectToDrop, short xPos, short yPos, LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getSaved)             (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putSaved)             (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(ReadOnly)             (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Save)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(SaveAs)               (THIS_ BSTR FileName, short FAR * lpi2Ret) PURE;
    STDMETHOD(getVersion)           (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(putVersion)           (THIS_ long Version) PURE;
    STDMETHOD(getTitle)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putTitle)             (THIS_ BSTR Title) PURE;
    STDMETHOD(getSubject)           (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putSubject)           (THIS_ BSTR Subject) PURE;
    STDMETHOD(getCreator)           (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putCreator)           (THIS_ BSTR Creator) PURE;
    STDMETHOD(getKeywords)          (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putKeywords)          (THIS_ BSTR Keywords) PURE;
    STDMETHOD(getDescription)       (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putDescription)       (THIS_ BSTR Description) PURE;
    STDMETHOD(Print)                (THIS) PURE;
    STDMETHOD(Close)                (THIS) PURE;
    STDMETHOD(CustomMenus)          (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(SetCustomMenus)       (THIS_ LPUNKNOWN MenusObject) PURE;
    STDMETHOD(getCustomMenusFile)   (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putCustomMenusFile)   (THIS_ BSTR FileName) PURE;
    STDMETHOD(ClearCustomMenus)     (THIS) PURE;
    STDMETHOD(CustomToolbars)       (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(SetCustomToolbars)    (THIS_ LPUNKNOWN ToolbarsObject) PURE;
    STDMETHOD(getCustomToolbarsFile) (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putCustomToolbarsFile) (THIS_ BSTR FileName) PURE;
    STDMETHOD(ClearCustomToolbars)  (THIS) PURE;
    STDMETHOD(Fonts)                (THIS_ LPVISIOFONTS FAR * lpdispRet) PURE;
    STDMETHOD(Colors)               (THIS_ LPVISIOCOLORS FAR * lpdispRet) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(Template)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(SaveAsEx)             (THIS_ BSTR FileName, short SaveFlags) PURE;
    STDMETHOD(getSavePreviewMode)   (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putSavePreviewMode)   (THIS_ short OnOrOff) PURE;
    STDMETHOD(GetIcon)              (THIS_ short ID, BSTR FileName) PURE;
    STDMETHOD(SetIcon)              (THIS_ short ID, short Index, BSTR FileName) PURE;
    STDMETHOD(getLeftMargin)        (THIS_ VARIANT UnitsNameOrCode, double FAR * lpr8Ret) PURE;
    STDMETHOD(putLeftMargin)        (THIS_ VARIANT UnitsNameOrCode, double Value) PURE;
    STDMETHOD(getRightMargin)       (THIS_ VARIANT UnitsNameOrCode, double FAR * lpr8Ret) PURE;
    STDMETHOD(putRightMargin)       (THIS_ VARIANT UnitsNameOrCode, double Value) PURE;
    STDMETHOD(getTopMargin)         (THIS_ VARIANT UnitsNameOrCode, double FAR * lpr8Ret) PURE;
    STDMETHOD(putTopMargin)         (THIS_ VARIANT UnitsNameOrCode, double Value) PURE;
    STDMETHOD(getBottomMargin)      (THIS_ VARIANT UnitsNameOrCode, double FAR * lpr8Ret) PURE;
    STDMETHOD(putBottomMargin)      (THIS_ VARIANT UnitsNameOrCode, double Value) PURE;
    STDMETHOD(getPrintLandscape)    (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPrintLandscape)    (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(getPrintCenteredH)    (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPrintCenteredH)    (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(getPrintCenteredV)    (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPrintCenteredV)    (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(getPrintScale)        (THIS_ double FAR * lpr8Ret) PURE;
    STDMETHOD(putPrintScale)        (THIS_ double Scale) PURE;
    STDMETHOD(getPrintFitOnPages)   (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPrintFitOnPages)   (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(getPrintPagesAcross)  (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPrintPagesAcross)  (THIS_ short PageCount) PURE;
    STDMETHOD(getPrintPagesDown)    (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPrintPagesDown)    (THIS_ short PageCount) PURE;
    STDMETHOD(getDefaultStyle)      (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putDefaultStyle)      (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getDefaultLineStyle)  (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putDefaultLineStyle)  (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getDefaultFillStyle)  (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putDefaultFillStyle)  (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getDefaultTextStyle)  (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putDefaultTextStyle)  (THIS_ BSTR StyleName) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(OpenStencilWindow)    (THIS_ LPVISIOWINDOW FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioDocuments

DECLARE_INTERFACE_(IVisioDocuments , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioDocuments methods ***
    STDMETHOD(Add)                  (THIS_ BSTR FileName, LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Open)                 (THIS_ BSTR FileName, LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameOrIndex, LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(OpenEx)               (THIS_ BSTR FileName, short Flags, LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioMaster

DECLARE_INTERFACE_(IVisioMaster , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioMaster methods ***
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(getPrompt)            (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putPrompt)            (THIS_ BSTR PromptString) PURE;
    STDMETHOD(getAlignName)         (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putAlignName)         (THIS_ short fMasAlignName) PURE;
    STDMETHOD(getIconSize)          (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putIconSize)          (THIS_ short fMasIconSize) PURE;
    STDMETHOD(getIconUpdate)        (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putIconUpdate)        (THIS_ short fMasIconUpdate) PURE;
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getName)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putName)              (THIS_ BSTR MasterName) PURE;
    STDMETHOD(Shapes)               (THIS_ LPVISIOSHAPES FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(OneD)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Delete)               (THIS) PURE;
    STDMETHOD(UniqueID)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(Layers)               (THIS_ LPVISIOLAYERS FAR * lpdispRet) PURE;
    STDMETHOD(PageSheet)            (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Drop)                 (THIS_ LPUNKNOWN ObjectToDrop, double xPos, double yPos, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(CenterDrawing)        (THIS) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(DrawLine)             (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawRectangle)        (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawOval)             (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawSpline)           (THIS_ SAFEARRAY FAR* FAR* xyArray, double Tolerance, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawBezier)           (THIS_ SAFEARRAY FAR* FAR* xyArray, short degree, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawPolyline)         (THIS_ SAFEARRAY FAR* FAR* xyArray, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Import)               (THIS_ BSTR FileName, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Export)               (THIS_ BSTR FileName) PURE;
    STDMETHOD(InsertFromFile)       (THIS_ BSTR FileName, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(InsertObject)         (THIS_ BSTR ClassID, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(OpenDrawWindow)       (THIS_ LPVISIOWINDOW FAR * lpdispRet) PURE;
    STDMETHOD(OpenIconWindow)       (THIS_ LPVISIOWINDOW FAR * lpdispRet) PURE;
    STDMETHOD(Open)                 (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(Close)                (THIS) PURE;
    STDMETHOD(DropMany)             (THIS_ SAFEARRAY FAR* FAR* ObjectsToDrop, SAFEARRAY FAR* FAR* xyArray, short FAR * lpi2Ret) PURE;
    STDMETHOD(GetFormulas)          (THIS_ SAFEARRAY FAR* FAR* SSRCArray, SAFEARRAY FAR* FAR* FormulaArray) PURE;
    STDMETHOD(GetResults)           (THIS_ SAFEARRAY FAR* FAR* SSRCArray, short Flags, VARIANT UnitsNameOrCode, SAFEARRAY FAR* FAR* ResultArray) PURE;
    STDMETHOD(SetFormulas)          (THIS_ SAFEARRAY FAR* FAR* SSRCArray, SAFEARRAY FAR* FAR* FormulaArray, short Flags, short FAR * lpi2Ret) PURE;
    STDMETHOD(SetResults)           (THIS_ SAFEARRAY FAR* FAR* SSRCArray, VARIANT UnitsNameOrCode, SAFEARRAY FAR* FAR* ResultArray, short Flags, short FAR * lpi2Ret) PURE;
    STDMETHOD(Connects)             (THIS_ LPVISIOCONNECTS FAR * lpdispRet) PURE;
    STDMETHOD(ImportIcon)           (THIS_ BSTR FileName) PURE;
    STDMETHOD(ExportIcon)           (THIS_ BSTR FileName, short Flags) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioMasters

DECLARE_INTERFACE_(IVisioMasters , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioMasters methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameUIDOrIndex, LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(Add)                  (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioPage

DECLARE_INTERFACE_(IVisioPage , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioPage methods ***
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getBackground)        (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putBackground)        (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(Paste)                (THIS) PURE;
    STDMETHOD(PasteSpecial)         (THIS_ short Format) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(DrawLine)             (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawRectangle)        (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawOval)             (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getName)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putName)              (THIS_ BSTR PageName) PURE;
    STDMETHOD(Shapes)               (THIS_ LPVISIOSHAPES FAR * lpdispRet) PURE;
    STDMETHOD(Drop)                 (THIS_ LPUNKNOWN ObjectToDrop, double xPos, double yPos, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(AddGuide)             (THIS_ short Type, double xPos, double yPos, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(getBackPage)          (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(putBackPage)          (THIS_ BSTR PageName) PURE;
    STDMETHOD(Print)                (THIS) PURE;
    STDMETHOD(Import)               (THIS_ BSTR FileName, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Export)               (THIS_ BSTR FileName) PURE;
    STDMETHOD(Layers)               (THIS_ LPVISIOLAYERS FAR * lpdispRet) PURE;
    STDMETHOD(PageSheet)            (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Delete)               (THIS_ short fRenumberPages) PURE;
    STDMETHOD(CenterDrawing)        (THIS) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(DrawSpline)           (THIS_ SAFEARRAY FAR* FAR* xyArray, double Tolerance, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawBezier)           (THIS_ SAFEARRAY FAR* FAR* xyArray, short degree, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawPolyline)         (THIS_ SAFEARRAY FAR* FAR* xyArray, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(InsertFromFile)       (THIS_ BSTR FileName, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(InsertObject)         (THIS_ BSTR ClassID, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(OpenDrawWindow)       (THIS_ LPVISIOWINDOW FAR * lpdispRet) PURE;
    STDMETHOD(DropMany)             (THIS_ SAFEARRAY FAR* FAR* ObjectsToDrop, SAFEARRAY FAR* FAR* xyArray, short FAR * lpi2Ret) PURE;
    STDMETHOD(GetFormulas)          (THIS_ SAFEARRAY FAR* FAR* SSRCArray, SAFEARRAY FAR* FAR* FormulaArray) PURE;
    STDMETHOD(GetResults)           (THIS_ SAFEARRAY FAR* FAR* SSRCArray, short Flags, VARIANT UnitsNameOrCode, SAFEARRAY FAR* FAR* ResultArray) PURE;
    STDMETHOD(SetFormulas)          (THIS_ SAFEARRAY FAR* FAR* SSRCArray, SAFEARRAY FAR* FAR* FormulaArray, short Flags, short FAR * lpi2Ret) PURE;
    STDMETHOD(SetResults)           (THIS_ SAFEARRAY FAR* FAR* SSRCArray, VARIANT UnitsNameOrCode, SAFEARRAY FAR* FAR* ResultArray, short Flags, short FAR * lpi2Ret) PURE;
    STDMETHOD(Connects)             (THIS_ LPVISIOCONNECTS FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioPages

DECLARE_INTERFACE_(IVisioPages , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioPages methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameOrIndex, LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Add)                  (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioSelection

DECLARE_INTERFACE_(IVisioSelection , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioSelection methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ short Index, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Export)               (THIS_ BSTR FileName) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(ContainingPage)       (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(ContainingMaster)     (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(ContainingShape)      (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(BringForward)         (THIS) PURE;
    STDMETHOD(BringToFront)         (THIS) PURE;
    STDMETHOD(SendBackward)         (THIS) PURE;
    STDMETHOD(SendToBack)           (THIS) PURE;
    STDMETHOD(getStyle)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putStyle)             (THIS_ BSTR StyleName) PURE;
    STDMETHOD(StyleKeepFmt)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getLineStyle)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putLineStyle)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(LineStyleKeepFmt)     (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getFillStyle)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putFillStyle)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(FillStyleKeepFmt)     (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getTextStyle)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putTextStyle)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(TextStyleKeepFmt)     (THIS_ BSTR StyleName) PURE;
    STDMETHOD(Combine)              (THIS) PURE;
    STDMETHOD(Fragment)             (THIS) PURE;
    STDMETHOD(Intersect)            (THIS) PURE;
    STDMETHOD(Subtract)             (THIS) PURE;
    STDMETHOD(Union)                (THIS) PURE;
    STDMETHOD(FlipHorizontal)       (THIS) PURE;
    STDMETHOD(FlipVertical)         (THIS) PURE;
    STDMETHOD(ReverseEnds)          (THIS) PURE;
    STDMETHOD(Rotate90)             (THIS) PURE;
    STDMETHOD(Copy)                 (THIS) PURE;
    STDMETHOD(Cut)                  (THIS) PURE;
    STDMETHOD(Delete)               (THIS) PURE;
    STDMETHOD(Duplicate)            (THIS) PURE;
    STDMETHOD(Group)                (THIS) PURE;
    STDMETHOD(ConvertToGroup)       (THIS) PURE;
    STDMETHOD(Ungroup)              (THIS) PURE;
    STDMETHOD(SelectAll)            (THIS) PURE;
    STDMETHOD(DeselectAll)          (THIS) PURE;
    STDMETHOD(Select)               (THIS_ LPVISIOSHAPE SheetObject, short SelectAction) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(Trim)                 (THIS) PURE;
    STDMETHOD(Join)                 (THIS) PURE;
    STDMETHOD(FitCurve)             (THIS_ double Tolerance, short Flags) PURE;
    STDMETHOD(SetFormulas)          (THIS_ SAFEARRAY FAR* FAR* SSRCArray, SAFEARRAY FAR* FAR* FormulaArray, short Flags, short FAR * lpi2Ret) PURE;
    STDMETHOD(SetResults)           (THIS_ SAFEARRAY FAR* FAR* SSRCArray, VARIANT UnitsNameOrCode, SAFEARRAY FAR* FAR* ResultArray, short Flags, short FAR * lpi2Ret) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioShape

DECLARE_INTERFACE_(IVisioShape , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioShape methods ***
    STDMETHOD(Group)                (THIS) PURE;
    STDMETHOD(BringForward)         (THIS) PURE;
    STDMETHOD(BringToFront)         (THIS) PURE;
    STDMETHOD(ConvertToGroup)       (THIS) PURE;
    STDMETHOD(FlipHorizontal)       (THIS) PURE;
    STDMETHOD(FlipVertical)         (THIS) PURE;
    STDMETHOD(ReverseEnds)          (THIS) PURE;
    STDMETHOD(SendBackward)         (THIS) PURE;
    STDMETHOD(SendToBack)           (THIS) PURE;
    STDMETHOD(Rotate90)             (THIS) PURE;
    STDMETHOD(Ungroup)              (THIS) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Parent)               (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Master)               (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(Type)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Cells)                (THIS_ BSTR CellName, LPVISIOCELL FAR * lpdispRet) PURE;
    STDMETHOD(CellsSRC)             (THIS_ short Section, short Row, short Column, LPVISIOCELL FAR * lpdispRet) PURE;
    STDMETHOD(Shapes)               (THIS_ LPVISIOSHAPES FAR * lpdispRet) PURE;
    STDMETHOD(getData1)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putData1)             (THIS_ BSTR String) PURE;
    STDMETHOD(getData2)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putData2)             (THIS_ BSTR String) PURE;
    STDMETHOD(getData3)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putData3)             (THIS_ BSTR String) PURE;
    STDMETHOD(getHelp)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putHelp)              (THIS_ BSTR String) PURE;
    STDMETHOD(NameID)               (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(getName)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putName)              (THIS_ BSTR SheetName) PURE;
    STDMETHOD(getText)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putText)              (THIS_ BSTR String) PURE;
    STDMETHOD(CharCount)            (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(Characters)           (THIS_ LPVISIOCHARS FAR * lpdispRet) PURE;
    STDMETHOD(Copy)                 (THIS) PURE;
    STDMETHOD(Cut)                  (THIS) PURE;
    STDMETHOD(Delete)               (THIS) PURE;
    STDMETHOD(Duplicate)            (THIS) PURE;
    STDMETHOD(Drop)                 (THIS_ LPUNKNOWN ObjectToDrop, double xPos, double yPos, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(getOneD)              (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putOneD)              (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(GeometryCount)        (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(RowCount)             (THIS_ short Section, short FAR * lpi2Ret) PURE;
    STDMETHOD(AddSection)           (THIS_ short Section, short FAR * lpi2Ret) PURE;
    STDMETHOD(DeleteSection)        (THIS_ short Section) PURE;
    STDMETHOD(AddRow)               (THIS_ short Section, short Row, short RowTag, short FAR * lpi2Ret) PURE;
    STDMETHOD(DeleteRow)            (THIS_ short Section, short Row) PURE;
    STDMETHOD(RowsCellCount)        (THIS_ short Section, short Row, short FAR * lpi2Ret) PURE;
    STDMETHOD(getRowType)           (THIS_ short Section, short Row, short FAR * lpi2Ret) PURE;
    STDMETHOD(putRowType)           (THIS_ short Section, short Row, short RowTag) PURE;
    STDMETHOD(SetCenter)            (THIS_ double xPos, double yPos) PURE;
    STDMETHOD(SetBegin)             (THIS_ double xPos, double yPos) PURE;
    STDMETHOD(SetEnd)               (THIS_ double xPos, double yPos) PURE;
    STDMETHOD(Connects)             (THIS_ LPVISIOCONNECTS FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getStyle)             (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putStyle)             (THIS_ BSTR StyleName) PURE;
    STDMETHOD(StyleKeepFmt)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getLineStyle)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putLineStyle)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(LineStyleKeepFmt)     (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getFillStyle)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putFillStyle)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(FillStyleKeepFmt)     (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getTextStyle)         (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putTextStyle)         (THIS_ BSTR StyleName) PURE;
    STDMETHOD(TextStyleKeepFmt)     (THIS_ BSTR StyleName) PURE;
    STDMETHOD(Export)               (THIS_ BSTR FileName) PURE;
    STDMETHOD(AreaIU)               (THIS_ double FAR * lpr8Ret) PURE;
    STDMETHOD(LengthIU)             (THIS_ double FAR * lpr8Ret) PURE;
    STDMETHOD(GeomExIf)             (THIS_ short fFill, double LineRes, LPUNKNOWN FAR * lpunkRet) PURE;
    STDMETHOD(UniqueID)             (THIS_ short fUniqueID, BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(ContainingPage)       (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(ContainingMaster)     (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(ContainingShape)      (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(SectionExists)        (THIS_ short Section, short fLocalExists, BOOL FAR * lpboolRet) PURE;
    STDMETHOD(RowExists)            (THIS_ short Section, short Row, short fLocalExists, BOOL FAR * lpboolRet) PURE;
    STDMETHOD(CellExists)           (THIS_ BSTR CellName, short fLocalExists, BOOL FAR * lpboolRet) PURE;
    STDMETHOD(CellsSRCExists)       (THIS_ short Section, short Row, short Column, short fLocalExists, BOOL FAR * lpboolRet) PURE;
    STDMETHOD(LayerCount)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Layer)                (THIS_ short Index, LPVISIOLAYER FAR * lpdispRet) PURE;
    STDMETHOD(AddNamedRow)          (THIS_ short Section, BSTR RowName, short RowTag, short FAR * lpi2Ret) PURE;
    STDMETHOD(AddRows)              (THIS_ short Section, short Row, short RowTag, short RowCount, short FAR * lpi2Ret) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(DrawLine)             (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawRectangle)        (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawOval)             (THIS_ double xLeft, double yTop, double xRight, double yBottom, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawSpline)           (THIS_ SAFEARRAY FAR* FAR* xyArray, double Tolerance, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawBezier)           (THIS_ SAFEARRAY FAR* FAR* xyArray, short degree, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(DrawPolyline)         (THIS_ SAFEARRAY FAR* FAR* xyArray, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(FitCurve)             (THIS_ double Tolerance, short Flags) PURE;
    STDMETHOD(Import)               (THIS_ BSTR FileName, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(CenterDrawing)        (THIS) PURE;
    STDMETHOD(InsertFromFile)       (THIS_ BSTR FileName, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(InsertObject)         (THIS_ BSTR ClassID, short Flags, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(ClassID)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(ForeignType)          (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Object)               (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(OpenDrawWindow)       (THIS_ LPVISIOWINDOW FAR * lpdispRet) PURE;
    STDMETHOD(OpenSheetWindow)      (THIS_ LPVISIOWINDOW FAR * lpdispRet) PURE;
    STDMETHOD(ID)                   (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(DropMany)             (THIS_ SAFEARRAY FAR* FAR* ObjectsToDrop, SAFEARRAY FAR* FAR* xyArray, short FAR * lpi2Ret) PURE;
    STDMETHOD(GetFormulas)          (THIS_ SAFEARRAY FAR* FAR* SSRCArray, SAFEARRAY FAR* FAR* FormulaArray) PURE;
    STDMETHOD(GetResults)           (THIS_ SAFEARRAY FAR* FAR* SSRCArray, short Flags, VARIANT UnitsNameOrCode, SAFEARRAY FAR* FAR* ResultArray) PURE;
    STDMETHOD(SetFormulas)          (THIS_ SAFEARRAY FAR* FAR* SSRCArray, SAFEARRAY FAR* FAR* FormulaArray, short Flags, short FAR * lpi2Ret) PURE;
    STDMETHOD(SetResults)           (THIS_ SAFEARRAY FAR* FAR* SSRCArray, VARIANT UnitsNameOrCode, SAFEARRAY FAR* FAR* ResultArray, short Flags, short FAR * lpi2Ret) PURE;
    STDMETHOD(FromConnects)         (THIS_ LPVISIOCONNECTS FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioShapes

DECLARE_INTERFACE_(IVisioShapes , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioShapes methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameUIDOrIndex, LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(ContainingPage)       (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(ContainingMaster)     (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(ContainingShape)      (THIS_ LPVISIOSHAPE FAR * lpdispRet) PURE;
    STDMETHOD(CenterDrawing)        (THIS) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(ItemFromID)           (THIS_ short ObjectID, LPVISIOSHAPE FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioStyle

DECLARE_INTERFACE_(IVisioStyle , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioStyle methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getName)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putName)              (THIS_ BSTR StyleName) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(getBasedOn)           (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putBasedOn)           (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getTextBasedOn)       (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putTextBasedOn)       (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getLineBasedOn)       (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putLineBasedOn)       (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getFillBasedOn)       (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putFillBasedOn)       (THIS_ BSTR StyleName) PURE;
    STDMETHOD(getIncludesText)      (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putIncludesText)      (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(getIncludesLine)      (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putIncludesLine)      (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(getIncludesFill)      (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putIncludesFill)      (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(Cells)                (THIS_ BSTR CellName, LPVISIOCELL FAR * lpdispRet) PURE;
    STDMETHOD(Delete)               (THIS_ LPUNKNOWN FAR * lpdispRet) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(ID)                   (THIS_ short FAR * lpi2Ret) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioStyles

DECLARE_INTERFACE_(IVisioStyles , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioStyles methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameOrIndex, LPVISIOSTYLE FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Add)                  (THIS_ BSTR StyleName, BSTR BasedOn, short fIncludesText, short fIncludesLine, short fIncludesFill, LPVISIOSTYLE FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(ItemFromID)           (THIS_ short ObjectID, LPVISIOSTYLE FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioWindow

DECLARE_INTERFACE_(IVisioWindow , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioWindow methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Activate)             (THIS) PURE;
    STDMETHOD(Type)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(getPage)              (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(putPage)              (THIS_ BSTR PageName) PURE;
    STDMETHOD(getZoom)              (THIS_ double FAR * lpr8Ret) PURE;
    STDMETHOD(putZoom)              (THIS_ double Zoom) PURE;
    STDMETHOD(Close)                (THIS) PURE;
    STDMETHOD(SelectAll)            (THIS) PURE;
    STDMETHOD(DeselectAll)          (THIS) PURE;
    STDMETHOD(Selection)            (THIS_ LPVISIOSELECTION FAR * lpdispRet) PURE;
    STDMETHOD(Select)               (THIS_ LPVISIOSHAPE SheetObject, short SelectAction) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Cut)                  (THIS) PURE;
    STDMETHOD(Copy)                 (THIS) PURE;
    STDMETHOD(Paste)                (THIS) PURE;
    STDMETHOD(Delete)               (THIS) PURE;
    STDMETHOD(Duplicate)            (THIS) PURE;
    STDMETHOD(Group)                (THIS) PURE;
    STDMETHOD(Union)                (THIS) PURE;
    STDMETHOD(Combine)              (THIS) PURE;
    STDMETHOD(Fragment)             (THIS) PURE;
    STDMETHOD(AddToGroup)           (THIS) PURE;
    STDMETHOD(RemoveFromGroup)      (THIS) PURE;
    STDMETHOD(SubType)              (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Intersect)            (THIS) PURE;
    STDMETHOD(Subtract)             (THIS) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(WindowHandle)         (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(WindowHandle32)       (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(Trim)                 (THIS) PURE;
    STDMETHOD(Join)                 (THIS) PURE;
    STDMETHOD(getShowRulers)        (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putShowRulers)        (THIS_ short OnOrOff) PURE;
    STDMETHOD(getShowGrid)          (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putShowGrid)          (THIS_ short OnOrOff) PURE;
    STDMETHOD(getShowGuides)        (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putShowGuides)        (THIS_ short OnOrOff) PURE;
    STDMETHOD(getShowConnectPoints) (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putShowConnectPoints) (THIS_ short OnOrOff) PURE;
    STDMETHOD(getShowPageBreaks)    (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putShowPageBreaks)    (THIS_ short OnOrOff) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioWindows

DECLARE_INTERFACE_(IVisioWindows , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioWindows methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ short Index, LPVISIOWINDOW FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Arrange)              (THIS) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioLayer

DECLARE_INTERFACE_(IVisioLayer , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioLayer methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Page)                 (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(Master)               (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Row)                  (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Add)                  (THIS_ LPVISIOSHAPE SheetObject, short fPresMems) PURE;
    STDMETHOD(Remove)               (THIS_ LPVISIOSHAPE SheetObject, short fPresMems) PURE;
    STDMETHOD(Delete)               (THIS_ short fDeleteShapes) PURE;
    STDMETHOD(getName)              (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putName)              (THIS_ BSTR LayerName) PURE;
    STDMETHOD(CellsC)               (THIS_ short Column, LPVISIOCELL FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioLayers

DECLARE_INTERFACE_(IVisioLayers , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioLayers methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Page)                 (THIS_ LPVISIOPAGE FAR * lpdispRet) PURE;
    STDMETHOD(Master)               (THIS_ LPVISIOMASTER FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameOrIndex, LPVISIOLAYER FAR * lpdispRet) PURE;
    STDMETHOD(Add)                  (THIS_ BSTR LayerName, LPVISIOLAYER FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(PersistsEvents)       (THIS_ BOOL FAR * lpboolRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioFont

DECLARE_INTERFACE_(IVisioFont , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioFont methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Name)                 (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(ID)                   (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Attributes)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(CharSet)              (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(PitchAndFamily)       (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioFonts

DECLARE_INTERFACE_(IVisioFonts , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioFonts methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameOrIndex, LPVISIOFONT FAR * lpdispRet) PURE;
    STDMETHOD(ItemFromID)           (THIS_ long ObjectID, LPVISIOFONT FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioColor

DECLARE_INTERFACE_(IVisioColor , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioColor methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getRed)               (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putRed)               (THIS_ short RGBVal) PURE;
    STDMETHOD(getGreen)             (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putGreen)             (THIS_ short RGBVal) PURE;
    STDMETHOD(getBlue)              (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putBlue)              (THIS_ short RGBVal) PURE;
    STDMETHOD(getFlags)             (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putFlags)             (THIS_ short fColorFlags) PURE;
    STDMETHOD(getPaletteEntry)      (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(putPaletteEntry)      (THIS_ long ColPalEntry) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioColors

DECLARE_INTERFACE_(IVisioColors , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioColors methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(Document)             (THIS_ LPVISIODOCUMENT FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ short Index, LPVISIOCOLOR FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Stat)                 (THIS_ short FAR * lpi2Ret) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioAddon

DECLARE_INTERFACE_(IVisioAddon , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioAddon methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Name)                 (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Enabled)              (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(Run)                  (THIS_ BSTR ArgString) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioAddons

DECLARE_INTERFACE_(IVisioAddons , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioAddons methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ VARIANT NameOrIndex, LPVISIOADDON FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Add)                  (THIS_ BSTR FileName, LPVISIOADDON FAR * lpdispRet) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioEvent

DECLARE_INTERFACE_(IVisioEvent , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioEvent methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(EventList)            (THIS_ LPVISIOEVENTS FAR * lpdispRet) PURE;
    STDMETHOD(Index)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(getEvent)             (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putEvent)             (THIS_ short Event) PURE;
    STDMETHOD(getAction)            (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putAction)            (THIS_ short Action) PURE;
    STDMETHOD(getTarget)            (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putTarget)            (THIS_ BSTR Target) PURE;
    STDMETHOD(getTargetArgs)        (THIS_ BSTR FAR * lpbstrRet) PURE;
    STDMETHOD(putTargetArgs)        (THIS_ BSTR TargetArgs) PURE;
    STDMETHOD(Trigger)              (THIS_ BSTR ContextString) PURE;
    STDMETHOD(Delete)               (THIS) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(ID)                   (THIS_ long FAR * lpi4Ret) PURE;
    STDMETHOD(getEnabled)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putEnabled)           (THIS_ short TrueOrFalse) PURE;
    STDMETHOD(Persistable)          (THIS_ BOOL FAR * lpboolRet) PURE;
    STDMETHOD(getPersistent)        (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(putPersistent)        (THIS_ short OnOrOff) PURE;
    };


#undef  INTERFACE
#define INTERFACE   IVisioEvents

DECLARE_INTERFACE_(IVisioEvents , IUnknown)
    {
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVisioEvents methods ***
    STDMETHOD(Application)          (THIS_ LPVISIOAPPLICATION FAR * lpdispRet) PURE;
    STDMETHOD(ObjectType)           (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Item)                 (THIS_ short Index, LPVISIOEVENT FAR * lpdispRet) PURE;
    STDMETHOD(Count)                (THIS_ short FAR * lpi2Ret) PURE;
    STDMETHOD(Add)                  (THIS_ short Event, short Action, BSTR Target, BSTR TargetArgs, LPVISIOEVENT FAR * lpdispRet) PURE;
    STDMETHOD(AddAdvise)            (THIS_ short Event, VARIANT SinkIUnkOrIDisp, BSTR IIDSink, BSTR TargetArgs, LPVISIOEVENT FAR * lpdispRet) PURE;
    STDMETHOD(ItemFromID)           (THIS_ long ObjectID, LPVISIOEVENT FAR * lpdispRet) PURE;
    };


#endif /* _OVISPROX_H */
