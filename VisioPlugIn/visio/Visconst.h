/* VISCONST.H - Visio Automation Constants
 * Copyright (C) 1991-1997 Visio Corporation. All rights reserved.
 */


#ifndef _VISCONST_H
#define _VISCONST_H

// Class name to be used with Create/GetObject.
#define visApi                                    "visio.application"

// Unit codes to be used with cell.result and similar methods.
#define visNumber                                 32
#define visDate                                   40
#define visDurationUnits                          42
#define visElapsedWeek                            43
#define visElapsedDay                             44
#define visElapsedHour                            45
#define visElapsedMin                             46
#define visElapsedSec                             47
#define visTypeUnits                              48
#define visPoints                                 50
#define visPicas                                  51
#define visDidots                                 53
#define visCiceros                                54
#define visPageUnits                              63
#define visDrawingUnits                           64
#define visInches                                 65
#define visFeet                                   66
#define visFeetAndInches                          67
#define visMiles                                  68
#define visCentimeters                            69
#define visMillimeters                            70
#define visMeters                                 71
#define visKilometers                             72
#define visInchFrac                               73
#define visMileFrac                               74
#define visYards                                  75
#define visNautMiles                              76
#define visAngleUnits                             80
#define visDegrees                                81
#define visDegreeMinSec                           82
#define visRadians                                83
#define visMin                                    84
#define visSec                                    85
#define visCurrency                               111
#define visNoCast                                 252

// Type codes returned by window.type and subtype.
#define visWinOther                               0
#define visDrawing                                1
#define visStencil                                2
#define visSheet                                  3
#define visIcon                                   4
#define visPageWin                                128
#define visPageGroupWin                           160
#define visMasterWin                              64
#define visMasterGroupWin                         96

// Values to use with Window.ShowScrollBars.
// These have effect only if Visio is running as a control.
#define visScrollBarNeither                       0x0
#define visScrollBarHoriz                         0x1
#define visScrollBarVert                          0x4
#define visScrollBarBoth                          0x5

// Type codes returned by shape.type and foreigntype.
#define visTypePage                               1
#define visTypeGroup                              2
#define visTypeShape                              3
#define visTypeForeignObject                      4
#define visTypeGuide                              5
#define visTypeMetafile                           0x10
#define visTypeBitmap                             0x20
#define visTypeIsLinked                           0x100
#define visTypeIsEmbedded                         0x200
#define visTypeIsControl                          0x400
#define visTypeIsOLE2                             0x8000

// The value shape.id will not return for any shape.
#define visInvalShapeID                           -1
// The id of a page's or master's page sheet.
#define visPageSheetID                            0

// Indices of sections in shape or style objects.
#define visSectionInval                           255
#define visSectionFirst                           0
#define visSectionLast                            252
#define visSectionNone                            255
#define visSectionObject                          1
#define visSectionMember                          2
#define visSectionCharacter                       3
#define visSectionParagraph                       4
#define visSectionTab                             5
#define visSectionScratch                         6
// visSectionExport and visSectionConnectionPts name the same section.
#define visSectionExport                          7
#define visSectionConnectionPts                   7
#define visSectionTextField                       8
#define visSectionControls                        9
#define visSectionFirstComponent                  10
#define visSectionLastComponent                   239
#define visSectionAction                          240
#define visSectionLayer                           241
#define visSectionUser                            242
#define visSectionProp                            243
#define visSectionLastReal                        243

// Indices of rows in shape or style object sections.
#define visRowFirst                               0
#define visRowLast                                -2
#define visRowNone                                -1

// Indices of rows in visSectionObject.
#define visRowXFormOut                            1
#define visRowXFormIn                             1
#define visRowLine                                2
#define visRowFill                                3
#define visRowXForm1D                             4
#define visRowEvent                               5
#define visRowLayerMem                            6
#define visRowGuide                               7
#define visRowStyle                               8
#define visRowForeign                             9
#define visRowPage                                10
#define visRowText                                11
#define visRowTextXForm                           12
#define visRowAlign                               14
#define visRowLock                                15
#define visRowData123                             16
#define visRowMisc                                17
#define visRowRulerGrid                           18
#define visRowHyperlink                           19

// Index of component properties row and 1st vertex row
// in a geometry section (visSectionFirstComponent+i).
#define visRowComponent                           0
#define visRowVertex                              1

// Index of 1st row in visSectionMember, etc.
#define visRowMember                              0
#define visRowCharacter                           0
#define visRowParagraph                           0
#define visRowTab                                 0
#define visRowScratch                             0
// visRowExport and visRowConnectionPts name the same row.
#define visRowExport                              0
#define visRowConnectionPts                       0
#define visRowField                               0
#define visRowControl                             0
#define visRowAction                              0
#define visRowLayer                               0
#define visRowUser                                0
#define visRowProp                                0

// Generic index of 1st row in non-object/geometry section.
#define visRowFormat                              0

// Row tags to be used with shape.rowtype and similar methods.
#define visTagBase                                130
#define visTagRowVoid                             180
#define visTagInvalid                             -1

// Tags of geometry section rows. (visSectionFirstComponent+i)
#define visTagComponent                           137
#define visTagMoveTo                              138
#define visTagLineTo                              139
#define visTagArcTo                               140
#define visTagEllipticalArcTo                     144
#define visTagSplineBeg                           165
#define visTagSplineSpan                          166

// Tags of rows in visSectionTab.
#define visTagTab0                                136
#define visTagTab2                                150
#define visTagTab10                               151

// Tags of rows in visSectionControls.
#define visTagCtlPt                               162
#define visTagCtlPtTip                            170

// Tags of rows in visSectionConnectionPts.
#define visTagCnnctPt                             153
#define visTagCnnctNamed                          185
#define visTagCnnctPtABCD                         186
#define visTagCnnctNamedABCD                      187

// Indices of cells in visRowXFormOut and visRowTextXForm.
#define visXFormPinX                              0
#define visXFormPinY                              1
#define visXFormWidth                             2
#define visXFormHeight                            3
#define visXFormLocPinX                           4
#define visXFormLocPinY                           5
#define visXFormAngle                             6

// Indices of cells in visRowXFormOut but not visRowTextXForm.
#define visXFormFlipX                             7
#define visXFormFlipY                             8
#define visXFormResizeMode                        9

// Indices of cells in visRowLine.
#define visLineWeight                             0
#define visLineColor                              1
#define visLinePattern                            2
#define visLineRounding                           3
#define visLineArrowSize                          4
#define visLineBeginArrow                         5
#define visLineEndArrow                           6
#define visLineEndCap                             7

// Indices of cells in visRowFill.
#define visFillForegnd                            0
#define visFillBkgnd                              1
#define visFillPattern                            2
#define visFillShdwForegnd                        3
#define visFillShdwBkgnd                          4
#define visFillShdwPattern                        5

// Indices of cells in visRowXForm1D.
#define vis1DBeginX                               0
#define vis1DBeginY                               1
#define vis1DEndX                                 2
#define vis1DEndY                                 3

// Indices of cells in visRowEvent.
#define visEvtCellTheData                         0
#define visEvtCellTheText                         1
#define visEvtCellDblClick                        2
#define visEvtCellXFMod                           3
#define visEvtCellDrop                            4

// Indices of cells in visRowLayerMem.
#define visLayerMember                            0

// Indices of cells in visRowGuide. [0:visX 1:visY]
#define visGuideFlags                             2

// Indices of cells in visRowStyle.
#define visStyleIncludesLine                      0
#define visStyleIncludesFill                      1
#define visStyleIncludesText                      2

// Indices of cells in visRowForeign.
#define visFrgnImgOffsetX                         0
#define visFrgnImgOffsetY                         1
#define visFrgnImgWidth                           2
#define visFrgnImgHeight                          3

// Indices of cells in visRowPage.
#define visPageWidth                              0
#define visPageHeight                             1
#define visPageShdwOffsetX                        2
#define visPageShdwOffsetY                        3
#define visPageScale                              4
#define visPageDrawingScale                       5
#define visPageDrawSizeType                       6
#define visPageDrawScaleType                      7

// Indices of cells in visRowText.
#define visTxtBlkLeftMargin                       0
#define visTxtBlkRightMargin                      1
#define visTxtBlkTopMargin                        2
#define visTxtBlkBottomMargin                     3
#define visTxtBlkVerticalAlign                    4
#define visTxtBlkBkgnd                            5

// Indices of cells in visRowAlign.
#define visAlignLeft                              0
#define visAlignCenter                            1
#define visAlignRight                             2
#define visAlignTop                               3
#define visAlignMiddle                            4
#define visAlignBottom                            5

// Indices of cells in visRowLock.
#define visLockWidth                              0
#define visLockHeight                             1
#define visLockMoveX                              2
#define visLockMoveY                              3
#define visLockAspect                             4
#define visLockDelete                             5
#define visLockBegin                              6
#define visLockEnd                                7
#define visLockRotate                             8
#define visLockCrop                               9
#define visLockVtxEdit                            10
#define visLockTextEdit                           11
#define visLockFormat                             12
#define visLockGroup                              13
#define visLockCalcWH                             14
#define visLockSelect                             15

// Indices of cells in visRowData123.
#define visObjHelp                                0
#define visCopyRight                              1

// Indices of cells in visRowMisc.
#define visNoObjHandles                           0
#define visNonPrinting                            1
#define visNoCtlHandles                           2
#define visNoAlignBox                             3
#define visUpdateAlignBox                         4
#define visHideText                               5
#define visDynFeedback                            8
#define visGlueType                               9
#define visWalkPref                               10
#define visBegTrigger                             11
#define visEndTrigger                             12
#define visLOFlags                                13
#define visLOInteraction                          14
#define visLOBehavior                             15

// Indices of cells in visRowRulerGrid.
#define visXRulerDensity                          0
#define visYRulerDensity                          1
#define visXRulerOrigin                           4
#define visYRulerOrigin                           5
#define visXGridDensity                           6
#define visYGridDensity                           7
#define visXGridSpacing                           8
#define visYGridSpacing                           9
#define visXGridOrigin                            10
#define visYGridOrigin                            11

// Indices of cells in visRowHyperlink.
#define visHLinkDescription                       0
#define visHLinkAddress                           1
#define visHLinkSubAddress                        2
#define visHLinkExtraInfo                         3
#define visHLinkFrame                             4
#define visHLinkNewWin                            5

// Indices of cells in visRowComponent.
#define visCompNoFill                             0
#define visCompNoShow                             2

// Cell indices for visRowVertex+i.
// ...if rowtype is visTagMoveTo or visTagLineTo.
#define visX                                      0
#define visY                                      1
// ...if rowtype is visTagArcTo.
//    [0:visX 1:visY]
#define visBow                                    2
// ...if rowtype is visTagEllipticalArcTo.
//    [0:visX 1:visY]
#define visControlX                               2
#define visControlY                               3
#define visEccentricityAngle                      4
#define visAspectRatio                            5
// ...if rowtype is visTagSplineBeg.
//    [0:visX 1:visY]
#define visSplineKnot                             2
#define visSplineKnot2                            3
#define visSplineKnot3                            4
#define visSplineDegree                           5
// ...if rowtype is visTagSplineSpan.
//    [0:visX 1:visY 2:visSplineKnot]

// Indices of cells in visRowField+i.
#define visFieldCell                              0

// Indices of cells in visRowCharacter+i.
#define visCharacterFont                          0
#define visCharacterColor                         1
#define visCharacterStyle                         2
#define visCharacterCase                          3
#define visCharacterPos                           4
#define visCharacterSize                          7

// Indices of cells in visRowParagraph+i.
#define visIndentFirst                            0
#define visIndentLeft                             1
#define visIndentRight                            2
#define visSpaceLine                              3
#define visSpaceBefore                            4
#define visSpaceAfter                             5
#define visHorzAlign                              6

// Indices of cells in visRowTab+i.
// ...# of tab stops in row kept in cell visTabStopCount.
#define visTabStopCount                           0
// ...position of stop j is in cell ((j-1)*3)+1.
// ...alignment of stop j is in cell ((j-1)*3)+2.
#define visTabPos                                 1
#define visTabAlign                               2

// Indices of cells in visRowScratch+i.
#define visScratchX                               0
#define visScratchY                               1
#define visScratchA                               2
#define visScratchB                               3
#define visScratchC                               4
#define visScratchD                               5

// Indices of cells in visRowConnectionPts+i.
//    [0:visX 1:visY]
// These exist if row's type is visTagCnnctPtABCD or visTagCnnctNamedABCD.
#define visCnnctA                                 2
#define visCnnctB                                 3
#define visCnnctC                                 4
#define visCnnctD                                 5

// Indices of cells in visRowControl+i.
#define visCtlX                                   0
#define visCtlY                                   1
#define visCtlXDyn                                2
#define visCtlYDyn                                3
#define visCtlXCon                                4
#define visCtlYCon                                5
#define visCtlGlue                                6
// These exist if row's type is visTagCtlPtTip.
// visCtlType cell exists but is not used by Visio.
#define visCtlType                                7
#define visCtlTip                                 8

// Indices of cells in visRowAction+i.
#define visActionMenu                             0
#define visActionPrompt                           1
#define visActionHelp                             2
#define visActionAction                           3
#define visActionChecked                          4
#define visActionDisabled                         5

// Indices of cells in visRowLayer+i.
#define visLayerName                              0
#define visLayerColor                             2
#define visLayerStatus                            3
#define visLayerVisible                           4
#define visLayerPrint                             5
#define visLayerActive                            6
#define visLayerLock                              7
#define visLayerSnap                              8
#define visLayerGlue                              9

// Indices of cells in visRowUser+i.
#define visUserValue                              0
#define visUserPrompt                             1

// Indices of cells in visRowProp+i.
#define visCustPropsValue                         0
#define visCustPropsPrompt                        1
#define visCustPropsLabel                         2
#define visCustPropsFormat                        3
#define visCustPropsSortKey                       4
#define visCustPropsType                          5
#define visCustPropsInvis                         6
#define visCustPropsAsk                           7

// Values for visXFormResizeMode cell.
#define visXFormResizeDontCare                    0
#define visXFormResizeSpread                      1
#define visXFormResizeScale                       2

// Values for visFill[Shdw]Pattern cells.
#define visNoFill                                 0
#define visSolid                                  1
#define visWideUpDiagonal                         2
#define visWideCross                              3
#define visWideDiagonalCross                      4
#define visWideDownDiagonal                       5
#define visWideHorz                               6
#define visWideVert                               7
#define visBackDotsMini                           8
#define visHalfAndHalf                            9
#define visForeDotsMini                           10
#define visForeDotsNarrow                         11
#define visForeDotsWide                           12
#define visThickHorz                              13
#define visThickVertical                          14
#define visThickDownDiagonal                      15
#define visThickUpDiagonal                        16
#define visThickDiagonalCross                     17
#define visBackDotsWide                           18
#define visThinHorz                               19
#define visThinVert                               20
#define visThinDownDiagonal                       21
#define visThinUpDiagonal                         22
#define visThinCross                              23
#define visThinDiagonalCross                      24

// Values for visGuideFlags cell.
#define visGuideXActive                           0x400
#define visGuideYActive                           0x800

// Values for visPageDrawSizeType cell.
#define visPrintSetup                             0
#define visTight                                  1
#define visStandard                               2
#define visCustom                                 3
#define visLogical                                4
#define visDSMetric                               5
#define visDSEngr                                 6
#define visDSArch                                 7

// Values for visPageDrawScaleType cell.
#define visNoScale                                0
#define visArchitectural                          1
#define visEngineering                            2
#define visScaleCustom                            3
#define visScaleMetric                            4
#define visScaleMechanical                        5

// Values for visTxtBlkVerticalAlign cell.
#define visVertTop                                0
#define visVertMiddle                             1
#define visVertBottom                             2

// Values for visTxtBlkBkgnd cell. (or color index)
#define visTxtBlkOpaque                           0xff

// Values for visDynFeedback cell.
#define visDynFBDefault                           0
#define visDynFBUCon3Leg                          1
#define visDynFBUCon5Leg                          2

// Values for visGlueType cell.
#define visGlueTypeDefault                        0
#define visGlueTypeTrigger                        1
#define visGlueTypeWalking                        2

// Values for visWalkPref cell.
#define visWalkPrefBegNS                          0x1
#define visWalkPrefEndNS                          0x2

// Values for visLOFlags cell.
#define visLOFlagsVisDecides                      0
#define visLOFlagsPlacable                        1
#define visLOFlagsRoutable                        2
#define visLOFlagsDont                            4
// This bit set by Visio in groups with placable/routable members.
#define visLOFlagsPNRGroup                        8

// Values for visLOInteraction cell.
// These have effect if visLOFlags includes visLOFlagsPlacable.
#define visLOIPlaceNormal                         0
// These have effect if visLOFlags includes visLOFlagsRoutable.
#define visLOIRouteNormal                         0

// Values for visLOBehavior cell.
// These have effect if visLOFlags includes visLOFlagsPlacable.
#define visLOBPlaceNormal                         0
// These have effect if visLOFlags includes visLOFlagsRoutable.
#define visLOBRouteNormal                         0
#define visLOBRouteRightAng                       1
#define visLOBRouteStraight                       2
#define visLOBRouteFlowNS                         5
#define visLOBRouteFlowWE                         6
#define visLOBRouteTreeNS                         7
#define visLOBRouteTreeWE                         8

// Values for visX/YRulerDensity cells.
#define visRulerFine                              32
#define visRulerNormal                            16
#define visRulerCoarse                            8
#define visRulerFixed                             0

// Values for visX/YGridDensity cells.
#define visGridFine                               8
#define visGridNormal                             4
#define visGridCoarse                             2
#define visGridFixed                              0

// Values for visCharacterStyle cell.
#define visBold                                   0x1
#define visItalic                                 0x2
#define visUnderLine                              0x4
#define visSmallCaps                              0x8

// Values for visCharacterCase cell.
#define visCaseNormal                             0
#define visCaseAllCaps                            1
#define visCaseInitialCaps                        2

// Values for visCharacterPos cell.
#define visPosNormal                              0
#define visPosSuper                               1
#define visPosSub                                 2

// Values for visHorzAlign cell.
#define visHorzLeft                               0
#define visHorzCenter                             1
#define visHorzRight                              2
#define visHorzJustify                            3
#define visHorzForce                              4

// Values for visTabAlign cell.
#define visTabStopLeft                            0
#define visTabStopCenter                          1
#define visTabStopRight                           2
#define visTabStopDecimal                         3
#define visTabStopComma                           4

// Values for visCtlX/YCon cells.
#define visCtlProportional                        0
#define visCtlLocked                              1
#define visCtlOffsetMin                           2
#define visCtlOffsetMid                           3
#define visCtlOffsetMax                           4
#define visCtlProportionalHidden                  5
#define visCtlLockedHidden                        6
#define visCtlOffsetMinHidden                     7
#define visCtlOffsetMidHidden                     8
#define visCtlOffsetMaxHidden                     9

// Values for visLayerColor cell. (Use shape color)
#define visNoLayerColor                           0xff

// Values for visLayerStatus cell.
#define visLayerValid                             0
#define visLayerDeleted                           1
#define visLayerAvailable                         2

// Values for visCustPropsType cell.
#define visPropTypeString                         0
#define visPropTypeListFix                        1
#define visPropTypeNumber                         2
#define visPropTypeBool                           3
#define visPropTypeListVar                        4

// Indices of colors (in default palette).
#define visTransparent                            0
#define visBlack                                  0
#define visWhite                                  1
#define visRed                                    2
#define visGreen                                  3
#define visBlue                                   4
#define visYellow                                 5
#define visMagenta                                6
#define visCyan                                   7
#define visDarkRed                                8
#define visDarkGreen                              9
#define visDarkBlue                               10
#define visDarkYellow                             11
#define visPurple                                 12
#define visDarkCyan                               13
#define visGray                                   14
#define visGray10                                 15
#define visGray20                                 16
#define visGray30                                 17
#define visGray40                                 18
#define visDarkGray                               19
#define visGray50                                 19
#define visGray60                                 20
#define visGray70                                 21
#define visGray80                                 22
#define visGray90                                 23

// Flags to be passed to the OpenEx method.
#define visOpenCopy                               1
#define visOpenRO                                 2
#define visOpenDocked                             4
#define visOpenDontList                           8

// Flags to be passed to the SaveAsEx method.
#define visSaveAsRO                               1
#define visSaveAsWS                               2

// Flags to be passed to the SavePreviewMode property.
#define visSavePrevNone                           0
#define visSavePrevDraft1st                       1
#define visSavePrevDetailed1st                    2
#define visSavePrevDraftAll                       4
#define visSavePrevDetailedAll                    8

// Flags passed to or returned by Document.Mode.
#define visDocModeRun                             0
#define visDocModeDesign                          1

// Flags to be passed to InsertObject or InsertFromFile.
#define visInsertLink                             0x8
#define visInsertIcon                             0x10
#define visInsertDontShow                         0x1000
#define visInsertAsControl                        0x2000
#define visInsertAsEmbed                          0x4000

// Flag to be passed to GetResults indicating desired return type.
#define visGetFloats                              0
#define visGetTruncatedInts                       1
#define visGetRoundedInts                         2
#define visGetStrings                             3
#define visGetFormulas                            4

// Flags to be passed to SetFormulas or SetResults.
#define visSetFormulas                            0x1
#define visSetBlastGuards                         0x2
#define visSetTestCircular                        0x4

// Flags to be passed to BoundingBox.
#define visBBoxUprightWH                          0x1
#define visBBoxUprightText                        0x2
#define visBBoxExtents                            0x4
#define visBBoxIncludeGuides                      0x1000
#define visBBoxDrawingCoords                      0x2000
#define visBBoxNoNonPrint                         0x4000

// Results returned from HitTest.
#define visHitOutside                             0
#define visHitOnBoundary                          1
#define visHitInside                              2

// Action codes used in conjunction with Select method.
#define visDeselect                               1
#define visSelect                                 2
#define visSubSelect                              3
#define visSelectAll                              4
#define visDeselectAll                            256

// Action codes to be passed to Shape.UniqueID.
#define visGetGUID                                0
#define visGetOrMakeGUID                          1
#define visDeleteGUID                             2

// Flag to be passed to Shape.SectionExists and similar methods.
#define visExistsLocally                          1
#define visExistsAnywhere                         0

// Result codes returned by Cell.Error property.
#define visErrorSuccess                           0
#define visErrorDivideByZero                      39
#define visErrorValue                             47
#define visErrorReference                         55
#define visErrorName                              61
#define visErrorNumber                            68
#define visErrorNotAvailable                      74

// Truncate vs Round arg to be passed to Cell.ResultInt.
#define visTruncate                               0
#define visRound                                  1

// Run types to be passed to Characters.RunBegin/End.
#define visCharPropRow                            1
#define visParaPropRow                            2
#define visTabPropRow                             3
#define visWordRun                                10
#define visParaRun                                11
#define visFieldRun                               20

// Bias to be passed to Characters.CharPropsRow, etc.
#define visBiasLetVisioChoose                     0
#define visBiasLeft                               1
#define visBiasRight                              2

// Toolbar flavor to be passed to BuiltInToolbars or ToolbarStyle.
//     Visio 5.0 no longer supports toolbar flavors.
//     BuiltInToolbars now ignores argument passed to it.
//     ToolbarStyle can still be used to show/hide toolbars.
//     App.ShowToolbar is now available to do this also.
#define visToolBarNone                            -1
#define visToolBarOn                              0
// These are obsolete as of Visio 5.0. Effect now equivalent to visToolBarOn.
#define visToolBarMSOffice                        0
#define visToolBarLotusSS                         0

// Flags to pass to DrawSpline.
#define visSplinePeriodic                         1
#define visSplineDoCircles                        2
#define visSplineAbrupt                           4
#define visSpline1D                               8

// Type codes to be passed to Page.AddGuide.
#define visPoint                                  1
#define visHorz                                   2
#define visVert                                   3

// Attribute codes returned by Font.Attributes.
#define visFontRaster                             16
#define visFontDevice                             32
#define visFontScalable                           64
#define visFont0Alias                             128

// Result codes returned by Stat method.
// (Prior to Visio 4.1, Stat always returned visStatNormal)
#define visStatNormal                             0
#define visStatAppHasShutdown                     1
#define visStatDeleted                            2
#define visStatTouched                            4
#define visStatClosed                             8
#define visStatSuspended                          16

// Flags to use with App.TraceFlags.
#define visTraceEvents                            0x1
#define visTraceAdvises                           0x2
#define visTraceAddonInvokes                      0x4
#define visTraceCallsToVBA                        0x8

// The ID no Event object can have.
#define visEvtIDInval                             -1

// Event codes to be used with Event and EventList objects.
#define visEvtCodeInval                           0
#define visEvtCodeDocCreate                       1
#define visEvtCodeDocOpen                         2
#define visEvtCodeDocSave                         3
#define visEvtCodeDocSaveAs                       4
#define visEvtCodeDocRunning                      5
#define visEvtCodeDocDesign                       6
#define visEvtCodeBefDocSave                      7
#define visEvtCodeBefDocSaveAs                    8
#define visEvtCodeBefForcedFlush                  200
#define visEvtCodeAfterForcedFlush                201
#define visEvtCodeWinSelChange                    701
#define visEvtCodeBefWinSelDel                    702
#define visEvtCodeBefWinPageTurn                  703
#define visEvtCodeWinPageTurn                     704
#define visEvtCodeShapeDelete                     801
#define visEvtCodeBefSelDel                       901
#define visEvtCodeSelAdded                        902

// Combine these with type codes that follow to be informed
// of addition, deletion or modification of those types.
#define visEvtAdd                                 0x8000
#define visEvtDel                                 0x4000
#define visEvtMod                                 0x2000

// Combine these with visEvtAdd/Del/Mod
#define visEvtWindow                              0x1
#define visEvtDoc                                 0x2
#define visEvtStyle                               0x4
#define visEvtMaster                              0x8
#define visEvtPage                                0x10
// visEvtLayer not used. Value may be used for different purpose in future.
#define visEvtLayer                               0x20
#define visEvtShape                               0x40
#define visEvtText                                0x80
// visEvtConnect supported as of Visio 5.0. (Defined but implemented prior to 5.0.)
#define visEvtConnect                             0x100
// visEvtSection not used. Value may be used for different purpose in future.
#define visEvtSection                             0x200
// visEvtRow not used. Value may be used for different purpose in future.
#define visEvtRow                                 0x400
// visEvtCell+visEvtMod fires when a cell's value changes.
#define visEvtCell                                0x800
// visEvtFormula+visEvtMod fires when a cell's formula changes.
#define visEvtFormula                             0x1000

// Combine this with app event codes that follow to be
// informed when those events happen to this instance.
#define visEvtApp                                 0x1000

// Combine these with visEvtApp
#define visEvtAppActivate                         0x1
#define visEvtAppDeactivate                       0x2
#define visEvtObjActivate                         0x4
#define visEvtObjDeactivate                       0x8
#define visEvtBeforeQuit                          0x10
#define visEvtBeforeModal                         0x20
#define visEvtAfterModal                          0x40
#define visEvtWinActivate                         0x80
#define visEvtMarker                              0x100
#define visEvtNonePending                         0x200
#define visEvtIdle                                0x400

// These are obsolete and unsupported as of Visio 4.1.
#define visEvtCode1stUser                         28672
#define visEvtCodeLastUser                        32767

// These are obsolete. Use visEvtCodeDocXxx instead.
#define visEvtCodeCreate                          1
#define visEvtCodeOpen                            2

// Action codes to be used with Event and EventList objects.
#define visActCodeRunAddon                        1
#define visActCodeAdvise                          2

// Pass this to EventInfo to get info on most recent event.
#define visEvtIdMostRecent                        0


// These are the codes returned by object.ObjectType.
#define visObjTypeUnknown                         1
#define visObjTypeApp                             3
#define visObjTypeCell                            4
#define visObjTypeChars                           5
#define visObjTypeConnect                         8
#define visObjTypeConnects                        9
#define visObjTypeDoc                             10
#define visObjTypeDocs                            11
#define visObjTypeMaster                          12
#define visObjTypeMasters                         13
#define visObjTypePage                            14
#define visObjTypePages                           15
#define visObjTypeSelection                       16
#define visObjTypeShape                           17
#define visObjTypeShapes                          18
#define visObjTypeStyle                           19
#define visObjTypeStyles                          20
#define visObjTypeWindow                          21
#define visObjTypeWindows                         22
#define visObjTypeLayer                           25
#define visObjTypeLayers                          26
#define visObjTypeFont                            27
#define visObjTypeFonts                           28
#define visObjTypeColor                           29
#define visObjTypeColors                          30
#define visObjTypeAddon                           31
#define visObjTypeAddons                          32
#define visObjTypeEvent                           33
#define visObjTypeEventList                       34
#define visObjTypeGlobal                          36
#define visObjTypeHyperlink                       37
#define visObjTypeOLEObjects                      38
#define visObjTypeOLEObject                       39
#define visObjTypePaths                           40
#define visObjTypePath                            41
#define visObjTypeCurve                           42

// Text field categories.
#define visFCatCustom                             0
#define visFCatDateTime                           1
#define visFCatDocument                           2
#define visFCatGeometry                           3
#define visFCatObject                             4
#define visFCatPage                               5
#define visFCatNotes                              6

// Text field Date/Time codes.
#define visFCodeCreateDate                        0
#define visFCodeCreateTime                        1
#define visFCodeCurrentDate                       2
#define visFCodeCurrentTime                       3
#define visFCodeEditDate                          4
#define visFCodeEditTime                          5
#define visFCodePrintDate                         6
#define visFCodePrintTime                         7

// Text field Document Info codes.
#define visFCodeCreator                           0
#define visFCodeDescription                       1
#define visFCodeDirectory                         2
#define visFCodeFileName                          3
#define visFCodeKeyWords                          4
#define visFCodeSubject                           5
#define visFCodeTitle                             6
#define visFCodeManager                           7
#define visFCodeCompany                           8
#define visFCodeCategory                          9
#define visFCodeHyperlinkBase                     10

// Text field Geometry Info codes.
#define visFCodeWidth                             0
#define visFCodeHeight                            1
#define visFCodeAngle                             2

// Text field Object Info codes.
#define visFCodeData1                             0
#define visFCodeData2                             1
#define visFCodeData3                             2
#define visFCodeObjectID                          3
#define visFCodeMasterName                        4
#define visFCodeObjectName                        5
#define visFCodeObjectType                        6

// Text field Page Info codes.
#define visFCodeBackgroundName                    0
#define visFCodePageName                          1
#define visFCodeNumberOfPages                     2
#define visFCodePageNumber                        3

// Text field format codes.
#define visFmtNumGenNoUnits                       0
#define visFmtNumGenDefUnits                      1

#define visFmt0PlNoUnits                          2
#define visFmt0PlDefUnits                         3
#define visFmt1PlNoUnits                          4
#define visFmt1PlDefUnits                         5
#define visFmt2PlNoUnits                          6
#define visFmt2PlDefUnits                         7
#define visFmt3PlNoUnits                          8
#define visFmt3PlDefUnits                         9

#define visFmtFeetAndInches                       10
#define visFmtRadians                             11
#define visFmtDegrees                             12
#define visFmtFeetAndInches1Pl                    13
#define visFmtFeetAndInches2Pl                    14

#define visFmtFraction1PlNoUnits                  15
#define visFmtFraction1PlDefUnits                 16
#define visFmtFraction2PlNoUnits                  17
#define visFmtFraction2PlDefUnits                 18

#define visFmtDateShort                           20
#define visFmtDateLong                            21
#define visFmtDateMDYY                            22
#define visFmtDateMMDDYY                          23
#define visFmtDateMmmDYYYY                        24
#define visFmtDateMmmmDYYYY                       25
#define visFmtDateDMYY                            26
#define visFmtDateDDMMYY                          27
#define visFmtDateDMMMYYYY                        28
#define visFmtDateDMMMMYYYY                       29

#define visFmtTimeGen                             30
#define visFmtTimeHMM                             31
#define visFmtTimeHHMM                            32
#define visFmtTimeHMM24                           33
#define visFmtTimeHHMM24                          34
#define visFmtTimeHMMAMPM                         35
#define visFmtTimeHHMMAMPM                        36

#define visFmtStrNormal                           37
#define visFmtStrLower                            38
#define visFmtStrUpper                            39

#define visFmtJDategggeXmXdXww                    40
#define visFmtJDateyyyyXmXdXww                    41
#define visFmtJDategggeXmXdX                      42
#define visFmtJDateyyyyXmXdX                      43
#define visFmtJDateyyyymd                         44
#define visFmtJDateyymmdd                         45
#define visFmtJDatehmmaxpx                        46
#define visFmtJDateaxpxhmm                        47
#define visFmtJDateaxpxhXmmX                      48
#define visFmtJDatehXmmX                          49

#define visFmtCDategggeXmmmmXdddd                 50
#define visFmtCDateggeXmmmmXdddd                  51
#define visFmtCDategeXmmmmXdddd                   52

// Document version codes.
#define visVersionUnsaved                         0x0
#define visVersion10                              0x10023
#define visVersion20                              0x20000
#define visVersion30                              0x30003
#define visVersion40                              0x40000
#define visVersion50                              0x50000

// Master.AlignName settings.
#define visLeft                                   1
#define visCenter                                 2
#define visRight                                  3

// Master.ExportIcon flags.
#define visIconFormatVisio                        0
#define visIconFormatBMP                          2

// Master.IconSize settings.
#define visNormal                                 1
#define visTall                                   2
#define visWide                                   3
#define visDouble                                 4

// Master.IconUpdate settings.
#define visAutomatic                              1
#define visManual                                 0

// Master.PatternFlags settings.
#define visMasIsLinePat                           0x1
#define visMasIsLineEnd                           0x2
#define visMasIsFillPat                           0x4

// Flags to use if visMasIsLinePat is set.
#define visMasLPTileDeform                        0x0
#define visMasLPTile                              0x10
#define visMasLPStretch                           0x20
#define visMasLPAnnotate                          0x30
#define visMasLPScale                             0x40

// Flags to use if visMasIsLineEnd is set.
#define visMasLEDefault                           0x0
#define visMasLEUpright                           0x100
#define visMasLEScale                             0x400

// Flags to use if visMasIsFillPat is set.
#define visMasFPTile                              0x0
#define visMasFPCenter                            0x1000
#define visMasFPStretch                           0x2000
#define visMasFPScale                             0x4000

// Codes returned by Connect.FromPart.
#define visConnectFromError                       -1
#define visFromNone                               0
#define visLeftEdge                               1
#define visCenterEdge                             2
#define visRightEdge                              3
#define visBottomEdge                             4
#define visMiddleEdge                             5
#define visTopEdge                                6
#define visBeginX                                 7
#define visBeginY                                 8
#define visBegin                                  9
#define visEndX                                   10
#define visEndY                                   11
#define visEnd                                    12
#define visControlPoint                           100

// Codes returned by Connect.ToPart.
#define visConnectToError                         -1
#define visToNone                                 0
#define visGuideX                                 1
#define visGuideY                                 2
#define visWholeShape                             3
#define visConnectionPoint                        100

// Obsolete - Use visConnectFrom/ToError.
#define visConnectError                           -1

// Obsolete - Use visFrom/ToNone.
#define visNone                                   0

// UI Object Set identifiers.
#define visUIObjSetNoDocument                     1
#define visUIObjSetDrawing                        2
#define visUIObjSetStencil                        3
#define visUIObjSetShapeSheet                     4
#define visUIObjSetIcon                           5
#define visUIObjSetInPlace                        6
#define visUIObjSetPrintPreview                   7
#define visUIObjSetText                           8
#define visUIObjSetCntx_DrawObjSel                9
#define visUIObjSetCntx_DrawOleObjSel             10
#define visUIObjSetCntx_DrawNoObjSel              11
#define visUIObjSetCntx_InPlaceNoObj              12
#define visUIObjSetCntx_TextEdit                  13
#define visUIObjSetCntx_StencilRO                 14
#define visUIObjSetCntx_ShapeSheet                15
#define visUIObjSetCntx_Toolbar                   16
#define visUIObjSetCntx_FullScreen                17
#define visUIObjSetBinderInPlace                  18
#define visUIObjSetCntx_Debug                     19
#define visUIObjSetCntx_StencilRW                 20
#define visUIObjSetCntx_StencilDocked             21
#define visUIObjSetHostingInPlace                 22
#define visUIObjSetCntx_Hyperlink                 23
#define visUIObjSetPal_LineColors                 24
#define visUIObjSetPal_LineWeights                25
#define visUIObjSetPal_LinePatterns               26
#define visUIObjSetPal_FillColors                 27
#define visUIObjSetPal_FillPatterns               28
#define visUIObjSetPal_TextColors                 29
#define visUIObjSetPal_AlignShapes                30
#define visUIObjSetPal_DistributeShapes           31
#define visUIObjSetPal_Shadow                     32
#define visUIObjSetPal_LineEnds                   33
#define visUIObjSetPal_CornerRounding             34

// Command numbers to be used with CmdNum property.
#define visCmdHierarchical                        200
#define visCmdFileNew                             1001
#define visCmdFileOpen                            1002
#define visCmdFileClose                           1003
#define visCmdFileSave                            1004
#define visCmdFileSaveAs                          1005
#define visCmdFileSaveWorkspace                   1006
#define visCmdFileImport                          1007
#define visCmdFileSummaryInfoDlg                  1009
#define visCmdFilePrint                           1010
#define visCmdFileExit                            1016
#define visCmdEditUndo                            1017
#define visCmdEditRedo                            1018
#define visCmdEditRepeat                          1019
#define visCmdUFEditCut                           1020
#define visCmdUFEditCopy                          1021
#define visCmdUFEditPaste                         1022
#define visCmdUFEditClear                         1023
#define visCmdUFEditDuplicate                     1024
#define visCmdUFEditSelectAll                     1025
#define visCmdEditSelectSpecial                   1026
#define visCmdEditPasteSpecial                    1027
#define visCmdEditOpenObject                      1029
#define visCmdEditLinks                           1030
#define visCmdEditInsertObject                    1031
#define visCmdEditInsertField                     1032
#define visCmdViewFitInWindow                     1033
#define visCmdView75                              1034
#define visCmdView100                             1035
#define visCmdView150                             1036
#define visCmdView200                             1037
#define visCmdViewCustom                          1038
#define visCmdViewRulers                          1039
#define visCmdViewGrid                            1040
#define visCmdViewGuides                          1041
#define visCmdViewConnections                     1042
#define visCmdEditFind                            1043
#define visCmdViewStatusBar                       1044
#define visCmdObjectBringForward                  1045
#define visCmdObjectBringToFront                  1046
#define visCmdObjectSendBackward                  1047
#define visCmdObjectSendToBack                    1048
#define visCmdObjectAlignObjects                  1049
#define visCmdObjectConnectObjects                1050
#define visCmdObjectGroup                         1051
#define visCmdObjectUngroup                       1052
#define visCmdObjectAddToGroup                    1053
#define visCmdObjectRemoveFromGroup               1054
#define visCmdObjectConvertToGroup                1055
#define visCmdObjectRotate90                      1056
#define visCmdObjectFlipVertical                  1057
#define visCmdObjectFlipHorizontal                1058
#define visCmdObjectReverse                       1059
#define visCmdObjectUnion                         1060
#define visCmdObjectCombine                       1061
#define visCmdObjectFragment                      1062
#define visCmdFormatStyle                         1063
#define visCmdFormatDefineStyles                  1064
#define visCmdFormatLine                          1065
#define visCmdFormatFill                          1066
#define visCmdFormatText                          1067
#define visCmdFormatFont                          1067
#define visCmdFormatParagraph                     1068
#define visCmdFormatTabs                          1069
#define visCmdFormatBlock                         1070
#define visCmdFormatBehavior                      1071
#define visCmdFormatProtection                    1072
#define visCmdFormatSpecial                       1073
#define visCmdOptionsEditDrawing                  1074
#define visCmdOptionsEditBackground               1075
#define visCmdOptionsPageSetup                    1076
#define visCmdOptionsGoToDrawing                  1077
#define visCmdOptionsNewPage                      1078
#define visCmdOptionsDeletePages                  1079
#define visCmdOptionsReorderPages                 1080
#define visCmdOptionsPreferences                  1081
#define visCmdOptionsColorPaletteDlg              1082
#define visCmdOptionsProtectDocument              1083
#define visCmdOptionsSnapGlueSetup                1084
#define visCmdWindowNewWindow                     1085
#define visCmdWindowCascadeAll                    1086
#define visCmdWindowTileAll                       1087
#define visCmdWindowShowShapeSheet                1088
#define visCmdWindowShowMasterObjects             1089
#define visCmdRunAddOnMenu                        1090
#define visCmdWindowShowDrawPage                  1091
#define visCmdHelpContents                        1092
#define visCmdDecreaseIndent                      1093
#define visCmdIncreaseIndent                      1094
#define visCmdDecreaseParaSpacing                 1095
#define visCmdIncreaseParaSpacing                 1096
#define visCmdTextRotate90                        1098
#define visCmdHelpAboutVisio                      1100
#define visCmdStenEditIcon                        1101
#define visCmdStenEditDrawing                     1102
#define visCmdStenNameMaster                      1103
#define visCmdStenNewMaster                       1104
#define visCmdStenImageMaster                     1105
#define visCmdStenCleanup                         1106
#define visCmdSWShowValues                        1107
#define visCmdSWShowFormulas                      1108
#define visCmdSWShowSectionsDlg                   1109
#define visCmdSWPasteNameDlg                      1110
#define visCmdSWPasteFunctionDlg                  1111
#define visCmdSWInsertRow                         1112
#define visCmdSWInsertRowAfter                    1113
#define visCmdSWChangeRowTypeDlg                  1114
#define visCmdSWDeleteRow                         1115
#define visCmdSWAddSectionDlg                     1116
#define visCmdSWDeleteSection                     1117
#define visCmdFormatDoubleClick                   1118
#define visCmdDrawLineStyle                       1122
#define visCmdDrawFillStyle                       1123
#define visCmdDrawSnap                            1124
#define visCmdDrawGlue                            1125
#define visCmdDrawZoom                            1126
#define visCmdTextStyle                           1128
#define visCmdTextFont                            1129
#define visCmdTextSize                            1130
#define visCmdTextBold                            1131
#define visCmdTextItalic                          1132
#define visCmdTextSmallCaps                       1133
#define visCmdTextSuperscript                     1134
#define visCmdTextSubscript                       1135
#define visCmdTextUline                           1136
#define visCmdSWCancel                            1139
#define visCmdSWAccept                            1140
#define visCmdSWFormula                           1141
#define visCmdSWShowToggle                        1142
#define visCmdIconLeftColor                       1143
#define visCmdIconPencilTool                      1145
#define visCmdRecalcObjectWH                      1146
#define visCmdTurnToPrevPage                      1147
#define visCmdTurnToNextPage                      1148
#define visCmdEditReplace                         1179
#define visCmdAlignObjectLeft                     1196
#define visCmdAlignObjectCenter                   1197
#define visCmdAlignObjectRight                    1198
#define visCmdAlignObjectTop                      1199
#define visCmdAlignObjectMiddle                   1200
#define visCmdAlignObjectBottom                   1201
#define visCmdCenterDrawing                       1202
#define visCmdDeselectAll                         1213
#define visCmdTextEditState                       1214
#define visCmdZoomIn                              1216
#define visCmdZoomOut                             1217
#define visCmdDRPointerTool                       1219
#define visCmdDRPencilTool                        1220
#define visCmdDRLineTool                          1221
#define visCmdDRQtrArcTool                        1222
#define visCmdDRRectTool                          1223
#define visCmdDROvalTool                          1224
#define visCmdDRConnectorTool                     1225
#define visCmdDRConnectionTool                    1226
#define visCmdDRTextTool                          1227
#define visCmdDRRotateTool                        1228
#define visCmdObjectDistributeDlg                 1230
#define visCmdDistributeHSpace                    1231
#define visCmdDistributeCenter                    1233
#define visCmdDistributeVSpace                    1235
#define visCmdDistributeMiddle                    1237
#define visCmdDlgLotusNotesFields                 1245
#define visCmdToolsSpelling                       1270
#define visCmdFormatPainter                       1271
#define visCmdStenFloating                        1274
#define visCmdView50                              1279
#define visCmdView400                             1280
#define visCmdSendAsMail                          1292
#define visCmdShapeActions                        1309
#define visCmdDRSplineTool                        1311
#define visCmdFormatCustPropEdit                  1312
#define visCmdRulerGridDlg                        1318
#define visCmdFormatShadow                        1333
#define visCmdFormatCorners                       1334
#define visCmdToolsInventory                      1335
#define visCmdPageSizeScale                       1076
#define visCmdStenSwitchSides                     1342
#define visCmdToolsArrayShapesAddOn               1354
#define visCmdSetLineWeight                       1355
#define visCmdSetLinePattern                      1356
#define visCmdSetLineEnds                         1357
#define visCmdSetLineCornerStyle                  1358
#define visCmdSetLineColor                        1359
#define visCmdCloseWindow                         1361
#define visCmdSetFillShadow                       1379
#define visCmdSetFillColor                        1385
#define visCmdHelpMode                            1386
#define visCmdOffsetDlg                           1387
#define visCmdDesignMode                          1388
#define visCmdShapeExplorer                       1389
#define visCmdSetFillPattern                      1399
#define visCmdSetCharColor                        1404
#define visCmdSetCharSizeUp                       1405
#define visCmdSetCharSizeDown                     1406
#define visCmdTextHAlignLeft                      1407
#define visCmdTextHAlignCenter                    1408
#define visCmdTextHAlignRight                     1409
#define visCmdTextHAlignJustify                   1412
#define visCmdTextVAlignTop                       1413
#define visCmdTextVAlignMiddle                    1414
#define visCmdTextVAlignBottom                    1422
#define visCmdStampTool                           1424
#define visCmdObjectInfoDlg                       1425
#define visCmdObjectHelp                          1428
#define visCmdFileOpenStencil                     1442
#define visCmdPrintPage                           1443
#define visCmdSWShapeActionDlg                    1444
#define visCmdLayerDlg                            1446
#define visCmdLayerSetupDlg                       1448
#define visCmdCropTool                            1449
#define visCmdTextBlockTool                       1451
#define visCmdStenClose                           1452
#define visCmdIntersect                           1453
#define visCmdSubtract                            1454
#define visCmdStenActivate                        1458
#define visCmdStenIconAndName                     1480
#define visCmdStenIconOnly                        1481
#define visCmdStenNameOnly                        1482
#define visCmdStenAutoArrange                     1483
#define visCmdPrintPreview                        1490
#define visCmdOpenInVisio                         1491
#define visCmdFullScreenMode                      1492
#define visCmdRotate90Clockwise                   1494
#define visCmdZoomLast                            1495
#define visCmdZoomPageWidth                       1496
#define visCmdToolbarsDlg                         1500
#define visCmdINETAddToFavorites                  1506
#define visCmdViewPageBreaks                      1509
#define visCmdZoomSingleTile                      1512
#define visCmdPreviousTile                        1513
#define visCmdNextTile                            1514
#define visCmdFirstTile                           1515
#define visCmdLastTile                            1516
#define visCmdInsertAutoCADAddOn                  1521
#define visCmdInsertControlDlg                    1522
#define visCmdJoin                                1533
#define visCmdTrim                                1534
#define visCmdDlgCustomFit                        1536
#define visCmdFitCurve                            1538
#define visCmdIconBucketTool                      1543
#define visCmdIconLassoTool                       1544
#define visCmdIconSelectNet                       1545
#define visCmdToolsLayoutShapesDlg                1574
#define visCmdToolsRunVBE                         1576
#define visCmdToolsMacroDlg                       1577
#define visCmdFileNewBlankDrawing                 1579
#define visCmdFileNewBlankStencil                 1582
#define visCmdProgRefHelp                         1584
#define visCmdInsertHyperLink                     1585
#define visCmdHelpTemplates                       1586
#define visCmdEmailRouting                        1588
#define visCmdSendToExchange                      1589
#define visCmdINETUserSearchPage                  1595
#define visCmdINETVisioHomePage                   1596
#define visCmdINETGoForward                       1598
#define visCmdINETGoBack                          1599
#define visCmdOpenActiveObject                    1601
#define visCmdCancelInPlaceEditing                1602
#define visCmdINETVisioSolutionsLibrary           1604
#define visCmdINETKnowledgeBase                   1605
#define visCmdINETDiagrammingResources            1606
#define visCmdINETOpenHlink                       1607
#define visCmdINETOpenHlinkNewWnd                 1608
#define visCmdINETCopyHyperlink                   1610
#define visCmdHyperlinkHier                       1611
#define visCmdINETEditHyperlink                   1619
#define visCmdINETPasteAsHyperlink                1620
#define visCmdBullets                             1633
#define visCmdShapeLayerToolbar                   1634
#define visCmdGoToPageToolbar                     1635
#define visCmdFormatAllTextProps                  1642
#define visCmdBrowseSampleDrawings                1645

// Toolbar and Status Bar constants for CtrlType property.
#define visCtrlTypeEND                            0x0
#define visCtrlTypeSTATE                          0x1
#define visCtrlTypeBUTTON                         0x2
#define visCtrlTypeSTATE_BUTTON                   0x3
#define visCtrlTypePALETTEBUTTON                  0x10
#define visCtrlTypeHIERBUTTON                     0x4
#define visCtrlTypeSTATE_HIERBUTTON               0x5
#define visCtrlTypeDROPBUTTON                     0x8
#define visCtrlTypeSTATE_DROPBUTTON               0x9
#define visCtrlTypeSPINBUTTON                     0x10
#define visCtrlTypePUSHBUTTON                     0x20
#define visCtrlTypeOWNERDRAW_BUTTON               0x21
#define visCtrlTypeEDITBOX                        0x40
#define visCtrlTypeCOMBOBOX                       0x80
#define visCtrlTypeCOMBODRAW                      0x100
#define visCtrlTypeLISTBOX                        0x200
#define visCtrlTypeLISTBOXDRAW                    0x201
#define visCtrlTypeCOLORBOX                       0x400
#define visCtrlTypeLABEL                          0x800
#define visCtrlTypeMESSAGE                        0x1000
#define visCtrlTypeSPACER                         0x4000

// Toolbar and Status Bar constants for Spacing property.
#define visCtrlSpacingNONE                        0x0
#define visCtrlSpacingVARIABLE_BEFORE             0x1
#define visCtrlSpacingVARIABLE_AFTER              0x2
#define visCtrlSpacingFIXED_BEFORE                0x4
#define visCtrlSpacingFIXED_AFTER                 0x8
#define visCtrlSpacingNEW_ROW                     0x10
#define visCtrlSpacingTB_NOTFIXED                 0x20
#define visCtrlSpacingPALETTERIGHT                0x40
#define visCtrlSpacingNEW_ROW_PALETTERIGHT        0x50

// Toolbar and Status Bar constants for control alignment.
#define visCtrlAlignmentLEFT                      0x1
#define visCtrlAlignmentCENTER                    0x2
#define visCtrlAlignmentRIGHT                     0x4
#define visCtrlAlignmentBOX                       0x80
#define visCtrlAlignmentLEFTBOX                   0x81
#define visCtrlAlignmentCENTERBOX                 0x82
#define visCtrlAlignmentRIGHTBOX                  0x84

// Toolbar and Status Bar constants for CntrlID property.
#define visCtrlIDNEW                              8383
#define visCtrlIDOPEN                             1
#define visCtrlIDOPENSTEN                         2
#define visCtrlIDSAVE                             3
#define visCtrlIDPRINT                            4
#define visCtrlIDPREVIEW                          5
#define visCtrlIDCUT                              6
#define visCtrlIDCOPY                             7
#define visCtrlIDPASTE                            8
#define visCtrlIDCLEAR                            9
#define visCtrlIDUNDO                             10
#define visCtrlIDREDO                             11
#define visCtrlIDREPEAT                           12
#define visCtrlIDPREVIOUSPAGE                     13
#define visCtrlIDNEXTPAGE                         14
#define visCtrlIDZOOMOUT                          15
#define visCtrlIDZOOMIN                           16
#define visCtrlIDZOOM100                          17
#define visCtrlIDFLIPHORZ                         18
#define visCtrlIDFLIPVERT                         19
#define visCtrlIDPOINTERTOOL                      20
#define visCtrlIDPENCILTOOL                       21
#define visCtrlIDLINETOOL                         22
#define visCtrlIDQTRARCTOOL                       23
#define visCtrlIDRECTTOOL                         24
#define visCtrlIDOVALTOOL                         25
#define visCtrlIDSTAMPTOOL                        26
#define visCtrlIDTEXTTOOL                         27
#define visCtrlIDROTATETOOL                       28
#define visCtrlIDCROPTOOL                         29
#define visCtrlIDCONNECTIONPTTOOL                 30
#define visCtrlIDSNAP                             31
#define visCtrlIDGLUE                             32
#define visCtrlIDRULER                            33
#define visCtrlIDGRID                             34
#define visCtrlIDGUIDE                            35
#define visCtrlIDCONNECT                          36
#define visCtrlIDROTATECLOCKWISE                  37
#define visCtrlIDROTATECOUNTER                    38
#define visCtrlIDNEWWINDOW                        39
#define visCtrlIDCORNERSTYLE                      40
#define visCtrlIDLINEEND                          41
#define visCtrlIDSHADOWSTYLE                      42
#define visCtrlIDFILLCOLOR                        43
#define visCtrlIDLINECOLOR                        44
#define visCtrlIDLINEWEIGHT                       45
#define visCtrlIDLINEPATTERN                      46
#define visCtrlIDFILLPATTERN                      47
#define visCtrlIDPOINTSIZEDOWN                    48
#define visCtrlIDPOINTSIZEUP                      49
#define visCtrlIDBOLD                             50
#define visCtrlIDITALIC                           51
#define visCtrlIDULINE                            52
#define visCtrlIDSUPERSCRIPT                      53
#define visCtrlIDSUBSCRIPT                        54
#define visCtrlIDTEXTCOLOR                        55
#define visCtrlIDTEXTLEFT                         56
#define visCtrlIDTEXTCENTER                       57
#define visCtrlIDTEXTRIGHT                        58
#define visCtrlIDTEXTJUSTIFY                      59
#define visCtrlIDTEXTTOP                          60
#define visCtrlIDTEXTMIDDLE                       61
#define visCtrlIDTEXTBOTTOM                       62
#define visCtrlIDALIGN                            63
#define visCtrlIDALIGNLEFT                        64
#define visCtrlIDALIGNCENTER                      65
#define visCtrlIDALIGNRIGHT                       66
#define visCtrlIDALIGNTOP                         67
#define visCtrlIDALIGNMIDDLE                      68
#define visCtrlIDALIGNBOTTOM                      69
#define visCtrlIDDISTRIBUTE                       70
#define visCtrlIDDHORZ_EQSPACE                    71
#define visCtrlIDDHORZ_CENTER                     72
#define visCtrlIDDVERT_EQSPACE                    73
#define visCtrlIDDVERT_MIDDLE                     74
#define visCtrlIDCONNECTSHAPES                    75
#define visCtrlIDFIRSTPAGE                        76
#define visCtrlIDLASTPAGE                         77
#define visCtrlIDPAGEBREAKS                       78
#define visCtrlIDICONNAME                         80
#define visCtrlIDICONONLY                         81
#define visCtrlIDNAMEONLY                         82
#define visCtrlIDARRANGEICONS                     83
#define visCtrlIDCANCELFORMULA                    84
#define visCtrlIDACCEPTFORMULA                    85
#define visCtrlIDICONPENCIL                       86
#define visCtrlIDICONBUCKET                       87
#define visCtrlIDICONLASSO                        88
#define visCtrlIDICONSELNET                       89
#define visCtrlIDBRINGFRONT                       90
#define visCtrlIDSENDBACK                         91
#define visCtrlIDGROUP                            92
#define visCtrlIDUNGROUP                          93
#define visCtrlIDCASCADE                          94
#define visCtrlIDTILE                             95
#define visCtrlIDCONNECTORTOOL                    96
#define visCtrlIDTEXTBLOCKTOOL                    97
#define visCtrlIDWHOLEPAGE                        98
#define visCtrlIDSINGLETILE                       99
#define visCtrlIDFORMULA                          190
#define visCtrlIDSPACER                           191
#define visCtrlIDALLSTYLESCOMBO                   200
#define visCtrlIDTEXTSTYLECOMBO                   201
#define visCtrlIDLINESTYLECOMBO                   202
#define visCtrlIDFILLSTYLECOMBO                   203
#define visCtrlIDZOOMCOMBO                        204
#define visCtrlIDFONTCOMBO                        205
#define visCtrlIDPOINTSIZECOMBO                   206
#define visCtrlIDALLSTYLESLIST                    220
#define visCtrlIDTEXTSTYLELIST                    221
#define visCtrlIDLINESTYLELIST                    222
#define visCtrlIDFILLSTYLELIST                    223
#define visCtrlIDZOOMLIST                         224
#define visCtrlIDFONTLIST                         225
#define visCtrlIDPOINTSIZELIST                    226
#define visCtrlIDGOTOPAGELIST                     227
#define visCtrlIDCLOSE                            240
#define visCtrlIDLEFTCOLORBOX                     300
#define visCtrlIDRIGHTCOLORBOX                    301
#define visCtrlIDCOLOR1                           302
#define visCtrlIDCOLOR2                           303
#define visCtrlIDCOLOR3                           304
#define visCtrlIDCOLOR4                           305
#define visCtrlIDCOLOR5                           306
#define visCtrlIDCOLOR6                           307
#define visCtrlIDCOLOR7                           308
#define visCtrlIDCOLOR8                           309
#define visCtrlIDCOLOR9                           310
#define visCtrlIDCOLOR10                          311
#define visCtrlIDCOLOR11                          312
#define visCtrlIDCOLOR12                          313
#define visCtrlIDCOLOR13                          314
#define visCtrlIDCOLOR14                          315
#define visCtrlIDCOLOR15                          316
#define visCtrlIDCOLOR16                          317
#define visCtrlIDTRANSPARENT                      318
#define visCtrlIDALLSTYLESLABEL                   400
#define visCtrlIDTEXTSTYLELABEL                   401
#define visCtrlIDLINESTYLELABEL                   402
#define visCtrlIDFILLSTYLELABEL                   403
#define visCtrlIDZOOMLABEL                        404
#define visCtrlIDFONTLABEL                        405
#define visCtrlIDPOINTSIZELABEL                   406
#define visCtrlIDLEFTCOLORLABEL                   407
#define visCtrlIDRIGHTCOLORLABEL                  408
#define visCtrlIDSTATUSLABEL                      409
#define visCtrlIDPREVIEWLABEL                     410
#define visCtrlIDSTATUSREADOUT                    500
#define visCtrlIDSTATUSMSG_1                      501
#define visCtrlIDSTATUSMSG_2                      502
#define visCtrlIDSTATUSMSG_3                      503
#define visCtrlIDSTATUSMSG_4                      504
#define visCtrlIDSTATUSMSG_5                      505
#define visCtrlIDSTATUSMSG_6                      506
#define visCtrlIDSTATUSMSG_7                      507
#define visCtrlIDSTATUSMSG_8                      508
#define visCtrlIDSTATUSMSG_9                      509
#define visCtrlIDSPLINETOOL                       79
#define visCtrlIDSPELLING                         100
#define visCtrlIDFORMATPAINTER                    101
#define visCtrlIDHELPMODE                         102
#define visCtrlIDLAYERPROPERTIES                  103
#define visCtrlIDLAYOUTSHAPES                     104
#define visCtrlIDINSERTHYPERLINK                  105
#define visCtrlIDSEARCHTHEWEB                     106
#define visCtrlIDGOBACK                           107
#define visCtrlIDGOFORWARD                        108
#define visCtrlIDWEBTOOLBAR                       109
#define visCtrlIDSHAPEEXPL                        110
#define visCtrlIDCUSTPROP                         111
#define visCtrlIDROTATETEXT                       112
#define visCtrlIDBULLETS                          113
#define visCtrlIDDECRINDENT                       114
#define visCtrlIDINCRINDENT                       115
#define visCtrlIDDECRPARA                         116
#define visCtrlIDINCRPARA                         117
#define visCtrlIDINSERTCONTROL                    118
#define visCtrlIDDESIGNMODE                       119
#define visCtrlIDSHAPESHEET                       120
#define visCtrlIDSHAPELAYER                       247
#define visCtrlIDGOTOPAGE                         207
#define visCtrlIDLINECOLORS                       241
#define visCtrlIDLINEWEIGHTS                      242
#define visCtrlIDLINEPATTERNS                     243
#define visCtrlIDFILLCOLORS                       244
#define visCtrlIDFILLPATTERNS                     245
#define visCtrlIDTEXTCOLORS                       246
#define visCtrlIDMACROS                           121
#define visCtrlIDVBEDITOR                         122
#define visCtrlIDSHAPELAYERCOMBO                  208
#define visCtrlIDSHAPELAYERLIST                   228
#define visCtrlIDALIGNSHAPES                      260
#define visCtrlIDDISTRIBUTESHAPES                 261
#define visCtrlIDMSG_PAGES                        510

// Toolbar and Status Bar icon identifiers.
#define visIconIXNEW                              0
#define visIconIXOPEN                             1
#define visIconIXOPENSTENCIL                      2
#define visIconIXSAVE                             3
#define visIconIXPRINT                            4
#define visIconIXPRINTPREVIEW                     5
#define visIconIXCUT                              6
#define visIconIXCOPY                             7
#define visIconIXPASTE                            8
#define visIconIXCLEAR                            9
#define visIconIXUNDO                             10
#define visIconIXREDO                             11
#define visIconIXREPEAT                           12
#define visIconIXPREVIOUSPAGE                     13
#define visIconIXNEXTPAGE                         14
#define visIconIXZOOMOUT                          15
#define visIconIXZOOMIN                           16
#define visIconIXZOOM100                          17
#define visIconIXFLIPHORIZONTAL                   18
#define visIconIXFLIPVERTICAL                     19
#define visIconIXPOINTERTOOL                      20
#define visIconIXPENCILTOOL                       21
#define visIconIXLINETOOL                         22
#define visIconIXQTRARCTOOL                       23
#define visIconIXRECTANGLETOOL                    24
#define visIconIXOVALTOOL                         25
#define visIconIXSTAMPTOOL                        26
#define visIconIXTEXTOOL                          27
#define visIconIXROTATETOOL                       28
#define visIconIXCROP                             29
#define visIconIXCONNECTIONPTTOOL                 30
#define visIconIXSNAP                             31
#define visIconIXGLUE                             32
#define visIconIXRULER                            33
#define visIconIXGRID                             34
#define visIconIXGUIDE                            35
#define visIconIXCONNECTIONPOINTS                 36
#define visIconIXROTATECLOCKWISE                  37
#define visIconIXROTATECOUNTERCLOCKWISE           38
#define visIconIXNEWWINDOW                        39
#define visIconIXCORNERSTYLE                      40
#define visIconIXLINEEND                          41
#define visIconIXSHADOWSTYLE                      42
#define visIconIXFILLCOLOR                        43
#define visIconIXLINECOLOR                        44
#define visIconIXLINEWEIGHT                       45
#define visIconIXLINEPATTERN                      46
#define visIconIXFILLPATTERN                      47
#define visIconIXPOINTSIZEDOWN                    48
#define visIconIXPOINTSIZEUP                      49
#define visIconIXBOLD                             50
#define visIconIXITALIC                           51
#define visIconIXUNDERLINE                        52
#define visIconIXSUPERSCRIPT                      53
#define visIconIXSUBSCRIPT                        54
#define visIconIXTEXTCOLOR                        55
#define visIconIXTEXTALIGNLEFT                    56
#define visIconIXTEXTALIGNCENTER                  57
#define visIconIXTEXTALIGNRIGHT                   58
#define visIconIXTEXTALIGNJUSTIFY                 59
#define visIconIXTEXTALIGNTOP                     60
#define visIconIXTEXTALIGNMIDDLE                  61
#define visIconIXTEXTALIGNBOTTOM                  62
#define visIconIXALIGN                            63
#define visIconIXALIGNLEFT                        64
#define visIconIXALIGNCENTER                      65
#define visIconIXALIGNRIGHT                       66
#define visIconIXALIGNTOP                         67
#define visIconIXALIGNMIDDLE                      68
#define visIconIXALIGNBOTTOM                      69
#define visIconIXDISTRIBUTE                       70
#define visIconIXDHORZ_EQSPACE                    71
#define visIconIXDHORZ_CENTER                     72
#define visIconIXDVERT_EQSPACE                    73
#define visIconIXDVERT_MIDDLE                     74
#define visIconIXCONNECTSHAPES                    75
#define visIconIXFIRSTPAGE                        76
#define visIconIXLASTPAGE                         77
#define visIconIXPAGEBREAKS                       78
#define visIconIXSPLINETOOL                       79
#define visIconIXICONNAME                         80
#define visIconIXICONONLY                         81
#define visIconIXNAMEONLY                         82
#define visIconIXARRANGE                          83
#define visIconIXCANCEL                           84
#define visIconIXACCEPT                           85
#define visIconIXICONPENCIL                       86
#define visIconIXICONBUCKET                       87
#define visIconIXICONLASSO                        88
#define visIconIXICONSELNET                       89
#define visIconIXBRINGFRONT                       90
#define visIconIXSENDBACK                         91
#define visIconIXGROUP                            92
#define visIconIXUNGROUP                          93
#define visIconIXCASCADE                          94
#define visIconIXTILE                             95
#define visIconIXCONNECTORTOOL                    96
#define visIconIXTEXTBLOCKTOOL                    97
#define visIconIXWHOLEPAGE                        98
#define visIconIXSINGLETILE                       99
#define visIconIXSPELLING                         100
#define visIconIXFORMATPAINTER                    101
#define visIconIXHELPMODE                         102
#define visIconIXLAYERPROPERTIES                  103
#define visIconIXLAYOUTSHAPES                     104
#define visIconIXINSERTHYPERLINK                  105
#define visIconIXSEARCHTHEWEB                     106
#define visIconIXGOBACK                           107
#define visIconIXGOFORWARD                        108
#define visIconIXWEBTOOLBAR                       109
#define visIconIXSHAPEEXPL                        110
#define visIconIXCUSTPROP                         111
#define visIconIXROTATETEXT                       112
#define visIconIXBULLETS                          113
#define visIconIXDECRINDENT                       114
#define visIconIXINCRINDENT                       115
#define visIconIXDECRPARA                         116
#define visIconIXINCRPARA                         117
#define visIconIXINSERTCONTROL                    118
#define visIconIXDESIGNMODE                       119
#define visIconIXSHAPESHEET                       120
#define visIconIXMACROS                           121
#define visIconIXVBEDITOR                         122

// Toolbar and Status Bar string identifiers.
#define visStrIDBASESTRINGID                      2000
#define visStrIDALLSTYLES                         2000
#define visStrIDTEXTSTYLE                         2001
#define visStrIDLINESTYLE                         2002
#define visStrIDFILLSTYLE                         2003
#define visStrIDZOOM                              2004
#define visStrIDFONT                              2005
#define visStrIDPOINTSIZE                         2006
#define visStrIDLEFTCOLOR                         2007
#define visStrIDRIGHTCOLOR                        2008
#define visStrIDSTATUS                            2009
#define visStrIDPRINTPREVIEW                      2010
#define visStrIDTEXTEDIT                          2011
#define visStrIDCLOSE                             2050
#define visStrIDNONE                              2300
#define visStrIDCHANGE                            2301
#define visStrIDSPACE                             2302
#define visStrIDREADY                             2320
#define visStrIDWAIT                              2321
#define visStrIDDRAG                              2322
#define visStrIDDRAW                              2323
#define visStrIDEDIT                              2324
#define visStrIDMOVE                              2325
#define visStrIDSIZE                              2326
#define visStrIDROTATE                            2327
#define visStrIDCROP                              2328
#define visStrIDSCROLL                            2329
#define visStrIDADD                               2330
#define visStrIDEXTEND                            2331
#define visStrIDCOPY                              2332
#define visStrIDLINECOLORS                        2051
#define visStrIDLINEWEIGHTS                       2052
#define visStrIDLINEPATTERNS                      2053
#define visStrIDFILLCOLORS                        2054
#define visStrIDFILLPATTERNS                      2055
#define visStrIDTEXTCOLORS                        2056
#define visStrIDSHADOWS                           2057
#define visStrIDLINEENDS                          2058
#define visStrIDCORNERS                           2059
#define visStrIDNOSHADOW                          2060

#endif /* _VISCONST_H */
