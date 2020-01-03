/* V41METH.H - Compatibility Layer file
 * Copyright (C) 1996 Visio Corporation. All rights reserved.
 */

#ifndef _v41meth_H
#define _v41meth_H

// ***

//	Only define these name mappings if:
#ifdef VISIO_41_COMPATIBILITY_LAYER

// ***

// *** IVisioApplication methods ***
#define ActiveDocument get_ActiveDocument
#define ActivePage get_ActivePage
#define ActiveWindow get_ActiveWindow
#define Application get_Application
#define Documents get_Documents
#define ObjectType get_ObjectType
#define getOnDataChangeDelay get_OnDataChangeDelay
#define putOnDataChangeDelay put_OnDataChangeDelay
#define ProcessID get_ProcessID
#define getScreenUpdating get_ScreenUpdating
#define putScreenUpdating put_ScreenUpdating
//#define Stat get_Stat
#define Version get_Version
#define WindowHandle get_WindowHandle
#define Windows get_Windows
#define Language get_Language
#define IsVisio16 get_IsVisio16
#define IsVisio32 get_IsVisio32
#define WindowHandle32 get_WindowHandle32
#define InstanceHandle get_InstanceHandle
#define InstanceHandle32 get_InstanceHandle32
#define BuiltInMenus get_BuiltInMenus
#define BuiltInToolbars get_BuiltInToolbars
#define CustomMenus get_CustomMenus
#define getCustomMenusFile get_CustomMenusFile
#define putCustomMenusFile put_CustomMenusFile
#define CustomToolbars get_CustomToolbars
#define getCustomToolbarsFile get_CustomToolbarsFile
#define putCustomToolbarsFile put_CustomToolbarsFile
#define getAddonPaths get_AddonPaths
#define putAddonPaths put_AddonPaths
#define getDrawingPaths get_DrawingPaths
#define putDrawingPaths put_DrawingPaths
#define getFilterPaths get_FilterPaths
#define putFilterPaths put_FilterPaths
#define getHelpPaths get_HelpPaths
#define putHelpPaths put_HelpPaths
#define getStartupPaths get_StartupPaths
#define putStartupPaths put_StartupPaths
#define getStencilPaths get_StencilPaths
#define putStencilPaths put_StencilPaths
#define getTemplatePaths get_TemplatePaths
#define putTemplatePaths put_TemplatePaths
#define getUserName get_UserName
#define putUserName put_UserName
#define getPromptForSummary get_PromptForSummary
#define putPromptForSummary put_PromptForSummary
#define Addons get_Addons
#define ProfileName get_ProfileName
#define EventInfo get_EventInfo
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents
#define Active get_Active
#define getDeferRecalc get_DeferRecalc
#define putDeferRecalc put_DeferRecalc
#define getAlertResponse get_AlertResponse
#define putAlertResponse put_AlertResponse
#define getShowProgress get_ShowProgress
#define putShowProgress put_ShowProgress

// *** IVisioCell methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Error get_Error
#define getFormula get_Formula
#define putFormula put_Formula
#define FormulaForce put_FormulaForce
#define getResult get_Result
#define putResult put_Result
#define ResultForce put_ResultForce
#define getResultIU get_ResultIU
#define putResultIU put_ResultIU
#define ResultIUForce put_ResultIUForce
//#define Stat get_Stat
#define Units get_Units
#define Name get_Name
#define LocalName get_LocalName
#define putRowName put_RowName
#define Document get_Document
#define Shape get_Shape
#define Style get_Style
#define Section get_Section
#define Row get_Row
#define Column get_Column
#define IsConstant get_IsConstant
#define IsInherited get_IsInherited
#define getResultInt get_ResultInt
#define putResultInt put_ResultFromInt
#define ResultIntForce put_ResultFromIntForce
#define ResultStr get_ResultStr
#define getRowName get_RowName
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioChars methods ***
#define Application get_Application
#define getBegin get_Begin
#define putBegin put_Begin
#define CharCount get_CharCount
#define CharPropsRow get_CharPropsRow
#define CharProps put_CharProps
#define ParaProps put_ParaProps
#define ObjectType get_ObjectType
#define getEnd get_End
#define putEnd put_End
#define FieldCategory get_FieldCategory
#define FieldCode get_FieldCode
#define FieldFormat get_FieldFormat
#define FieldFormula get_FieldFormula
#define IsField get_IsField
#define ParaPropsRow get_ParaPropsRow
#define TabPropsRow get_TabPropsRow
#define RunBegin get_RunBegin
#define RunEnd get_RunEnd
#define Shape get_Shape
//#define Stat get_Stat
//#define getText get_TextAsString
#define putText put_Text
#define Document get_Document
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioConnect methods ***
#define Application get_Application
//#define Stat get_Stat
#define FromSheet get_FromSheet
#define ToSheet get_ToSheet
#define FromCell get_FromCell
#define ToCell get_ToCell
#define FromPart get_FromPart
#define ToPart get_ToPart
#define ObjectType get_ObjectType
#define Index get_Index
#define Document get_Document

// *** IVisioConnects methods ***
#define Application get_Application
#define Item get_Item
#define Count get_Count
#define FromSheet get_FromSheet
#define ObjectType get_ObjectType
#define Document get_Document
//#define Stat get_Stat

// *** IVisioDocument methods ***
#define Application get_Application
//#define Stat get_Stat
#define ObjectType get_ObjectType
#define InPlace get_InPlace
#define Masters get_Masters
#define Pages get_Pages
#define Styles get_Styles
#define Name get_Name
#define Path get_Path
#define FullName get_FullName
#define Index get_Index
#define getSaved get_Saved
#define putSaved put_Saved
#define ReadOnly get_ReadOnly
#define getVersion get_Version
#define putVersion put_Version
#define getTitle get_Title
#define putTitle put_Title
#define getSubject get_Subject
#define putSubject put_Subject
#define getCreator get_Creator
#define putCreator put_Creator
#define getKeywords get_Keywords
#define putKeywords put_Keywords
#define getDescription get_Description
#define putDescription put_Description
#define CustomMenus get_CustomMenus
#define getCustomMenusFile get_CustomMenusFile
#define putCustomMenusFile put_CustomMenusFile
#define CustomToolbars get_CustomToolbars
#define getCustomToolbarsFile get_CustomToolbarsFile
#define putCustomToolbarsFile put_CustomToolbarsFile
#define Fonts get_Fonts
#define Colors get_Colors
#define EventList get_EventList
#define Template get_Template
#define getSavePreviewMode get_SavePreviewMode
#define putSavePreviewMode put_SavePreviewMode
#define getLeftMargin get_LeftMargin
#define putLeftMargin put_LeftMargin
#define getRightMargin get_RightMargin
#define putRightMargin put_RightMargin
#define getTopMargin get_TopMargin
#define putTopMargin put_TopMargin
#define getBottomMargin get_BottomMargin
#define putBottomMargin put_BottomMargin
#define getPrintLandscape get_PrintLandscape
#define putPrintLandscape put_PrintLandscape
#define getPrintCenteredH get_PrintCenteredH
#define putPrintCenteredH put_PrintCenteredH
#define getPrintCenteredV get_PrintCenteredV
#define putPrintCenteredV put_PrintCenteredV
#define getPrintScale get_PrintScale
#define putPrintScale put_PrintScale
#define getPrintFitOnPages get_PrintFitOnPages
#define putPrintFitOnPages put_PrintFitOnPages
#define getPrintPagesAcross get_PrintPagesAcross
#define putPrintPagesAcross put_PrintPagesAcross
#define getPrintPagesDown get_PrintPagesDown
#define putPrintPagesDown put_PrintPagesDown
#define getDefaultStyle get_DefaultStyle
#define putDefaultStyle put_DefaultStyle
#define getDefaultLineStyle get_DefaultLineStyle
#define putDefaultLineStyle put_DefaultLineStyle
#define getDefaultFillStyle get_DefaultFillStyle
#define putDefaultFillStyle put_DefaultFillStyle
#define getDefaultTextStyle get_DefaultTextStyle
#define putDefaultTextStyle put_DefaultTextStyle
#define PersistsEvents get_PersistsEvents
#define OpenStencilWindow get_OpenStencilWindow

// *** IVisioDocuments methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioMaster methods ***
#define Document get_Document
#define getPrompt get_Prompt
#define putPrompt put_Prompt
#define getAlignName get_AlignName
#define putAlignName put_AlignName
#define getIconSize get_IconSize
#define putIconSize put_IconSize
#define getIconUpdate get_IconUpdate
#define putIconUpdate put_IconUpdate
#define Application get_Application
//#define Stat get_Stat
#define ObjectType get_ObjectType
#define getName get_Name
#define putName put_Name
#define Shapes get_Shapes
#define Index get_Index
#define OneD get_OneD
#define UniqueID get_UniqueID
#define Layers get_Layers
#define PageSheet get_PageSheet
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioMasters methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define Document get_Document
//#define Stat get_Stat
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioPage methods ***
#define Document get_Document
#define Application get_Application
//#define Stat get_Stat
#define getBackground get_Background
#define putBackground put_Background
#define ObjectType get_ObjectType
#define Index get_Index
#define getName get_Name
#define putName put_Name
#define Shapes get_Shapes
#define getBackPage get_BackPageAsObj
#define putBackPage put_BackPageFromName
#define Layers get_Layers
#define PageSheet get_PageSheet
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioPages methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define Document get_Document
//#define Stat get_Stat
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioSelection methods ***
#define Application get_Application
//#define Stat get_Stat
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define Document get_Document
#define ContainingPage get_ContainingPage
#define ContainingMaster get_ContainingMaster
#define ContainingShape get_ContainingShape
#define getStyle get_Style
#define putStyle put_Style
#define StyleKeepFmt put_StyleKeepFmt
#define getLineStyle get_LineStyle
#define putLineStyle put_LineStyle
#define LineStyleKeepFmt put_LineStyleKeepFmt
#define getFillStyle get_FillStyle
#define putFillStyle put_FillStyle
#define FillStyleKeepFmt put_FillStyleKeepFmt
#define getTextStyle get_TextStyle
#define putTextStyle put_TextStyle
#define TextStyleKeepFmt put_TextStyleKeepFmt
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioShape methods ***
#define FromConnects get_FromConnects
#define Document get_Document
#define Parent get_Parent
#define Application get_Application
//#define Stat get_Stat
#define Master get_Master
#define Type get_Type
#define ObjectType get_ObjectType
#define Cells get_Cells
#define CellsSRC get_CellsSRC
#define Shapes get_Shapes
#define getData1 get_Data1
#define putData1 put_Data1
#define getData2 get_Data2
#define putData2 put_Data2
#define getData3 get_Data3
#define putData3 put_Data3
#define getHelp get_Help
#define putHelp put_Help
#define NameID get_NameID
#define getName get_Name
#define putName put_Name
#define getText get_Text
#define putText put_Text
#define CharCount get_CharCount
#define Characters get_Characters
#define getOneD get_OneD
#define putOneD put_OneD
#define GeometryCount get_GeometryCount
#define RowCount get_RowCount
#define RowsCellCount get_RowsCellCount
#define getRowType get_RowType
#define putRowType put_RowType
#define Connects get_Connects
#define Index get_Index
#define getStyle get_Style
#define putStyle put_Style
//#define StyleKeepFmt get_StyleKeepFmt
#define getLineStyle get_LineStyle
#define putLineStyle put_LineStyle
//#define LineStyleKeepFmt get_LineStyleKeepFmt
#define getFillStyle get_FillStyle
#define putFillStyle put_FillStyle
//#define FillStyleKeepFmt get_FillStyleKeepFmt
#define getTextStyle get_TextStyle
#define putTextStyle put_TextStyle
//#define TextStyleKeepFmt get_TextStyleKeepFmt
#define AreaIU get_AreaIU
#define LengthIU get_LengthIU
#define GeomExIf get_GeomExIf
#define UniqueID get_UniqueID
#define ContainingPage get_ContainingPage
#define ContainingMaster get_ContainingMaster
#define ContainingShape get_ContainingShape
#define SectionExists get_SectionExists
#define RowExists get_RowExists
#define CellExists get_CellExists
#define CellsSRCExists get_CellsSRCExists
#define LayerCount get_LayerCount
#define Layer get_Layer
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents
#define ClassID get_ClassID
#define ForeignType get_ForeignType
#define Object get_Object

// *** IVisioShapes methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define Document get_Document
#define ContainingPage get_ContainingPage
#define ContainingMaster get_ContainingMaster
#define ContainingShape get_ContainingShape
//#define Stat get_Stat
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioStyle methods ***
#define Application get_Application
//#define Stat get_Stat
#define ObjectType get_ObjectType
#define getName get_Name
#define putName put_Name
#define Index get_Index
#define Document get_Document
#define getBasedOn get_BasedOn
#define putBasedOn put_BasedOn
#define getTextBasedOn get_TextBasedOn
#define putTextBasedOn put_TextBasedOn
#define getLineBasedOn get_LineBasedOn
#define putLineBasedOn put_LineBasedOn
#define getFillBasedOn get_FillBasedOn
#define putFillBasedOn put_FillBasedOn
#define getIncludesText get_IncludesText
#define putIncludesText put_IncludesText
#define getIncludesLine get_IncludesLine
#define putIncludesLine put_IncludesLine
#define getIncludesFill get_IncludesFill
#define putIncludesFill put_IncludesFill
#define Cells get_Cells
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioStyles methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define Document get_Document
//#define Stat get_Stat
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioWindow methods ***
#define Application get_Application
//#define Stat get_Stat
#define ObjectType get_ObjectType
#define Type get_Type
#define Document get_Document
#define getPage get_PageAsObj
#define putPage put_PageFromName
#define getZoom get_Zoom
#define putZoom put_Zoom
#define Selection get_Selection
#define Index get_Index
#define SubType get_SubType
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents
#define WindowHandle get_WindowHandle
#define WindowHandle32 get_WindowHandle32
#define getShowRulers get_ShowRulers
#define putShowRulers put_ShowRulers
#define getShowGrid get_ShowGrid
#define putShowGrid put_ShowGrid
#define getShowGuides get_ShowGuides
#define putShowGuides put_ShowGuides
#define getShowConnectPoints get_ShowConnectPoints
#define putShowConnectPoints put_ShowConnectPoints
#define getShowPageBreaks get_ShowPageBreaks
#define putShowPageBreaks put_ShowPageBreaks

// *** IVisioWindows methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioLayer methods ***
#define Application get_Application
#define Document get_Document
#define Page get_Page
#define Master get_Master
#define Index get_Index
#define Row get_Row
#define getName get_Name
#define putName put_Name
#define CellsC get_CellsC
#define ObjectType get_ObjectType
//#define Stat get_Stat
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioLayers methods ***
#define Application get_Application
#define Document get_Document
#define Page get_Page
#define Master get_Master
#define Count get_Count
#define Item get_Item
#define ObjectType get_ObjectType
//#define Stat get_Stat
#define EventList get_EventList
#define PersistsEvents get_PersistsEvents

// *** IVisioFont methods ***
#define Application get_Application
#define Document get_Document
#define Index get_Index
#define Name get_Name
#define ID get_ID
#define Attributes get_Attributes
#define CharSet get_CharSet
#define PitchAndFamily get_PitchAndFamily
#define ObjectType get_ObjectType
//#define Stat get_Stat

// *** IVisioFonts methods ***
#define Application get_Application
#define Document get_Document
#define Count get_Count
#define Item get_Item
#define ItemFromID get_ItemFromID
#define ObjectType get_ObjectType
//#define Stat get_Stat

// *** IVisioColor methods ***
#define Application get_Application
#define Document get_Document
#define Index get_Index
#define getRed get_Red
#define putRed put_Red
#define getGreen get_Green
#define putGreen put_Green
#define getBlue get_Blue
#define putBlue put_Blue
#define getFlags get_Flags
#define putFlags put_Flags
#define getPaletteEntry get_PaletteEntry
#define putPaletteEntry put_PaletteEntry
#define ObjectType get_ObjectType
//#define Stat get_Stat

// *** IVisioColors methods ***
#define Application get_Application
#define Document get_Document
#define Count get_Count
#define Item get_Item
#define ObjectType get_ObjectType
//#define Stat get_Stat

// *** IVisioAddon methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Name get_Name
#define Index get_Index
#define Enabled get_Enabled

// *** IVisioAddons methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count

// *** IVisioEvent methods ***
#define Application get_Application
#define EventList get_EventList
#define Index get_Index
#define getEvent get_Event
#define putEvent put_Event
#define getAction get_Action
#define putAction put_Action
#define getTarget get_Target
#define putTarget put_Target
#define getTargetArgs get_TargetArgs
#define putTargetArgs put_TargetArgs
#define ObjectType get_ObjectType
#define ID get_ID
#define getEnabled get_Enabled
#define putEnabled put_Enabled
#define Persistable get_Persistable
#define getPersistent get_Persistent
#define putPersistent put_Persistent

// *** IVisioEvents methods ***
#define Application get_Application
#define ObjectType get_ObjectType
#define Item get_Item
#define Count get_Count
#define ItemFromID get_ItemFromID

// ***

#endif	//	VISIO_41_COMPATIBILITY_LAYER

#endif	//	_v41meth_H
