#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CMschart1 包装类

class CMschart1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMschart1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x3A2B370C, 0xBA0A, 0x11D1, { 0xB1, 0x37, 0x0, 0x0, 0xF8, 0x75, 0x3F, 0x5D } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    VtOk = 0,
    VtFail = 1000,
    VtErrorDeletingUsedObject = 1001,
    VtErrorDeletingDeletedObject = 1002,
    VtErrorCorruptData = 1003,
    VtErrorNotImplemented = 1004,
    VtErrorNoMemory = 1100,
    VtErrorInvalidArgument = 1101,
    VtErrorNotFound = 1102,
    VtErrorTooSmall = 1103,
    VtErrorInvalidRequest = 1104,
    VtErrorStreamIo = 1105,
    VtErrorUserIo = 1106,
    VtErrorCorruptArchive = 1107,
    VtErrorArchiveVersion = 1108,
    VtErrorArchiveTypeMismatch = 1109,
    VtErrorArchivePointerMismatch = 1110,
    VtErrorCannotOpenFile = 1111,
    VtErrorUnableToLoadString = 1112,
    VtErrorBufferTooSmall = 1113,
    VtErrorCopyingObject = 1114,
    VtErrorDuplicateObject = 1115,
    VtErrorActionCanceled = 1116,
    VtErrorInvalidIndex = 1117,
    VtErrorInvalidTypeConversion = 1118,
    VtErrorInvalidObject = 1119,
    VtErrorCreateWindow = 1120,
    VtErrorOSVersion = 1121,
    VtErrorLoadPicture = 1122,
    VtErrorInvalidSyntax = 1200,
    VtErrorIdentifierTooBig = 1201,
    VtErrorUnrecongizedFunction = 1202,
    VtErrorUnrecongizedSymbol = 1203,
    VtErrorUnexpectedEOS = 1204,
    VtErrorDuplicateSymbol = 1205,
    VtErrorDisplay = 1500,
    VtErrorInvalidFontName = 1501,
    VtErrorInvalidFont = 1502,
    VtErrorNoDisplayResources = 1503,
    VtErrorDefaultFontSubstituted = 1504,
    VtChError = 2000,
    VtChErrorInvalidHandle = 2001,
    VtChErrorNoData = 2002,
    VtChErrorInvalidSeriesNumber = 2003,
    VtChErrorInvalidAxis = 2004,
    VtChErrorRestrictedVersion = 2005,
    InvalidPropertyValue = 380,
    GetNotSupported = 394,
    SetNotSupported = 383,
    InvalidProcedureCall = 5,
    InvalidObjectUse = 425,
    WrongClipboardFormat = 461,
    DataObjectLocked = 672,
    ExpectedAnArgument = 673,
    RecursiveOleDrag = 674,
    FormatNotByteArray = 675,
    DataNotSetForFormat = 676
}ErrorConstants;
enum
{
    chOLEDropNone = 0,
    chOLEDropManual = 1,
    chOLEDropAutomatic = 2
}OLEDropConstants;
enum
{
    chOLEDragManual = 0,
    chOLEDragAutomatic = 1
}OLEDragConstants;
enum
{
    VtHorizontalAlignmentLeft = 0,
    VtHorizontalAlignmentRight = 1,
    VtHorizontalAlignmentCenter = 2,
    VtHorizontalAlignmentFill = 3,
    VtHorizontalAlignmentFlush = 4
}VtHorizontalAlignment;
enum
{
    VtVerticalAlignmentTop = 0,
    VtVerticalAlignmentBottom = 1,
    VtVerticalAlignmentCenter = 2
}VtVerticalAlignment;
enum
{
    VtOrientationHorizontal = 0,
    VtOrientationVertical = 1,
    VtOrientationUp = 2,
    VtOrientationDown = 3
}VtOrientation;
enum
{
    VtSortTypeNone = 0,
    VtSortTypeAscending = 1,
    VtSortTypeDescending = 2
}VtSortType;
enum
{
    VtAngleUnitsDegrees = 0,
    VtAngleUnitsRadians = 1,
    VtAngleUnitsGrads = 2
}VtAngleUnits;
enum
{
    VtPrintScaleTypeActual = 0,
    VtPrintScaleTypeFitted = 1,
    VtPrintScaleTypeStretched = 2
}VtPrintScaleType;
enum
{
    VtPrintOrientationPortrait = 0,
    VtPrintOrientationLandscape = 1
}VtPrintOrientation;
enum
{
    VtFontStyleBold = 1,
    VtFontStyleItalic = 2,
    VtFontStyleOutline = 4
}VtFontStyle;
enum
{
    VtFontEffectStrikeThrough = 256,
    VtFontEffectUnderline = 512
}VtFontEffect;
enum
{
    VtBrushStyleNull = 0,
    VtBrushStyleSolid = 1,
    VtBrushStylePattern = 2,
    VtBrushStyleHatched = 3
}VtBrushStyle;
enum
{
    VtBrushPattern94Percent = 0,
    VtBrushPattern88Percent = 1,
    VtBrushPattern75Percent = 2,
    VtBrushPattern50Percent = 3,
    VtBrushPattern25Percent = 4,
    VtBrushPatternBoldHorizontal = 5,
    VtBrushPatternBoldVertical = 6,
    VtBrushPatternBoldDownDiagonal = 7,
    VtBrushPatternBoldUpDiagonal = 8,
    VtBrushPatternChecks = 9,
    VtBrushPatternWeave = 10,
    VtBrushPatternHorizontal = 11,
    VtBrushPatternVertical = 12,
    VtBrushPatternDownDiagonal = 13,
    VtBrushPatternUpDiagonal = 14,
    VtBrushPatternGrid = 15,
    VtBrushPatternTrellis = 16,
    VtBrushPatternInvertedTrellis = 17,
    VtBrushPatternCount = 18
}VtBrushPatterns;
enum
{
    VtBrushHatchHorizontal = 0,
    VtBrushHatchVertical = 1,
    VtBrushHatchDownDiagonal = 2,
    VtBrushHatchUpDiagonal = 3,
    VtBrushHatchCross = 4,
    VtBrushHatchDiagonalCross = 5,
    VtBrushHatchCount = 6
}VtBrushHatches;
enum
{
    VtShadowStyleNull = 0,
    VtShadowStyleDrop = 1
}VtShadowStyle;
enum
{
    VtPenStyleNull = 0,
    VtPenStyleSolid = 1,
    VtPenStyleDashed = 2,
    VtPenStyleDotted = 3,
    VtPenStyleDashDot = 4,
    VtPenStyleDashDotDot = 5,
    VtPenStyleDitted = 6,
    VtPenStyleDashDit = 7,
    VtPenStyleDashDitDit = 8,
    VtPenStyleNative = 9
}VtPenStyle;
enum
{
    VtPenJoinMiter = 0,
    VtPenJoinRound = 1,
    VtPenJoinBevel = 2
}VtPenJoin;
enum
{
    VtPenCapButt = 0,
    VtPenCapRound = 1,
    VtPenCapSquare = 2
}VtPenCap;
enum
{
    VtFrameStyleNull = 0,
    VtFrameStyleSingleLine = 1,
    VtFrameStyleDoubleLine = 2,
    VtFrameStyleThickInner = 3,
    VtFrameStyleThickOuter = 4
}VtFrameStyle;
enum
{
    VtPictureTypeNull = 0,
    VtPictureTypeBitmap = 1,
    VtPictureTypeVector = 2,
    VtPictureTypeBMP = 3,
    VtPictureTypeWMF = 4
}VtPictureType;
enum
{
    VtPictureOptionNoSizeHeader = 1,
    VtPictureOptionTextAsCurves = 2
}VtPictureOption;
enum
{
    VtPictureMapTypeActual = 0,
    VtPictureMapTypeFitted = 1,
    VtPictureMapTypeStretched = 2,
    VtPictureMapTypeTiled = 3,
    VtPictureMapTypeCropFitted = 4,
    VtPictureMapTypeHorizontalTile = 5,
    VtPictureMapTypeVerticalTile = 6
}VtPictureMapType;
enum
{
    VtGradientStyleHorizontal = 0,
    VtGradientStyleVertical = 1,
    VtGradientStyleRectangle = 2,
    VtGradientStyleOval = 3
}VtGradientStyle;
enum
{
    VtFillStyleNull = 0,
    VtFillStyleBrush = 1,
    VtFillStyleGradient = 2
}VtFillStyle;
enum
{
    VtMarkerStyleDash = 0,
    VtMarkerStylePlus = 1,
    VtMarkerStyleX = 2,
    VtMarkerStyleStar = 3,
    VtMarkerStyleCircle = 4,
    VtMarkerStyleSquare = 5,
    VtMarkerStyleDiamond = 6,
    VtMarkerStyleUpTriangle = 7,
    VtMarkerStyleDownTriangle = 8,
    VtMarkerStyleFilledCircle = 9,
    VtMarkerStyleFilledSquare = 10,
    VtMarkerStyleFilledDiamond = 11,
    VtMarkerStyleFilledUpTriangle = 12,
    VtMarkerStyleFilledDownTriangle = 13,
    VtMarkerStyle3dBall = 14,
    VtMarkerStyleNull = 15,
    VtMarkerStyleCount = 16
}VtMarkerStyle;
enum
{
    VtProjectionTypePerspective = 0,
    VtProjectionTypeOblique = 1,
    VtProjectionTypeOrthogonal = 2,
    VtProjectionTypeFrontal = 3,
    VtProjectionTypeOverhead = 4
}VtProjectionType;
enum
{
    VtSmoothingTypeNone = 0,
    VtSmoothingTypeQuadraticBSpline = 1,
    VtSmoothingTypeCubicBSpline = 2
}VtSmoothingType;
enum
{
    VtDcTypeNull = 0,
    VtDcTypeDisplay = 1,
    VtDcTypePrinter = 2,
    VtDcTypeMetafile = 3
}VtDcType;
enum
{
    VtTextOutputTypeHardware = 0,
    VtTextOutputTypePolygon = 1
}VtTextOutputType;
enum
{
    VtTextLengthTypeVirtual = 0,
    VtTextLengthTypeDevice = 1
}VtTextLengthType;
enum
{
    VtChChartType3dBar = 0,
    VtChChartType2dBar = 1,
    VtChChartType3dLine = 2,
    VtChChartType2dLine = 3,
    VtChChartType3dArea = 4,
    VtChChartType2dArea = 5,
    VtChChartType3dStep = 6,
    VtChChartType2dStep = 7,
    VtChChartType3dCombination = 8,
    VtChChartType2dCombination = 9,
    VtChChartType3dHorizontalBar = 10,
    VtChChartType2dHorizontalBar = 11,
    VtChChartType3dClusteredBar = 12,
    VtChChartType3dPie = 13,
    VtChChartType2dPie = 14,
    VtChChartType3dDoughnut = 15,
    VtChChartType2dXY = 16,
    VtChChartType2dPolar = 17,
    VtChChartType2dRadar = 18,
    VtChChartType2dBubble = 19,
    VtChChartType2dHiLo = 20,
    VtChChartType2dGantt = 21,
    VtChChartType3dGantt = 22,
    VtChChartType3dSurface = 23,
    VtChChartType2dContour = 24,
    VtChChartType3dScatter = 25,
    VtChChartType3dXYZ = 26,
    VtChChartTypeCount = 27
}VtChChartType;
enum
{
    VtChSeriesTypeVaries = -2,
    VtChSeriesTypeDefault = -1,
    VtChSeriesType3dBar = 0,
    VtChSeriesType2dBar = 1,
    VtChSeriesType3dHorizontalBar = 2,
    VtChSeriesType2dHorizontalBar = 3,
    VtChSeriesType3dClusteredBar = 4,
    VtChSeriesType3dLine = 5,
    VtChSeriesType2dLine = 6,
    VtChSeriesType3dArea = 7,
    VtChSeriesType2dArea = 8,
    VtChSeriesType3dStep = 9,
    VtChSeriesType2dStep = 10,
    VtChSeriesType2dXY = 11,
    VtChSeriesType2dPolar = 12,
    VtChSeriesType2dRadarLine = 13,
    VtChSeriesType2dRadarArea = 14,
    VtChSeriesType2dBubble = 15,
    VtChSeriesType2dHiLo = 16,
    VtChSeriesType2dHLC = 17,
    VtChSeriesType2dHLCRight = 18,
    VtChSeriesType2dOHLC = 19,
    VtChSeriesType2dOHLCBar = 20,
    VtChSeriesType2dGantt = 21,
    VtChSeriesType3dGantt = 22,
    VtChSeriesType3dPie = 23,
    VtChSeriesType2dPie = 24,
    VtChSeriesType3dDoughnut = 25,
    VtChSeriesType2dDates = 26,
    VtChSeriesType3dBarHiLo = 27,
    VtChSeriesType2dBarHiLo = 28,
    VtChSeriesType3dHorizontalBarHiLo = 29,
    VtChSeriesType2dHorizontalBarHiLo = 30,
    VtChSeriesType3dClusteredBarHiLo = 31,
    VtChSeriesType3dSurface = 32,
    VtChSeriesType2dContour = 33,
    VtChSeriesType3dXYZ = 34,
    VtChSeriesTypeCount = 35
}VtChSeriesType;
enum
{
    VtChPartTypeChart = 0,
    VtChPartTypeTitle = 1,
    VtChPartTypeFootnote = 2,
    VtChPartTypeLegend = 3,
    VtChPartTypePlot = 4,
    VtChPartTypeSeries = 5,
    VtChPartTypeSeriesLabel = 6,
    VtChPartTypePoint = 7,
    VtChPartTypePointLabel = 8,
    VtChPartTypeAxis = 9,
    VtChPartTypeAxisLabel = 10,
    VtChPartTypeAxisTitle = 11,
    VtChPartTypeSeriesName = 12,
    VtChPartTypePointName = 13,
    VtChPartTypeCount = 14
}VtChPartType;
enum
{
    VtChLocationTypeTopLeft = 0,
    VtChLocationTypeTop = 1,
    VtChLocationTypeTopRight = 2,
    VtChLocationTypeLeft = 3,
    VtChLocationTypeRight = 4,
    VtChLocationTypeBottomLeft = 5,
    VtChLocationTypeBottom = 6,
    VtChLocationTypeBottomRight = 7,
    VtChLocationTypeCustom = 8
}VtChLocationType;
enum
{
    VtChLabelComponentValue = 1,
    VtChLabelComponentPercent = 2,
    VtChLabelComponentSeriesName = 4,
    VtChLabelComponentPointName = 8
}VtChLabelComponent;
enum
{
    VtChLabelLineStyleNone = 0,
    VtChLabelLineStyleStraight = 1,
    VtChLabelLineStyleBent = 2
}VtChLabelLineStyle;
enum
{
    VtChLabelLocationTypeNone = 0,
    VtChLabelLocationTypeAbovePoint = 1,
    VtChLabelLocationTypeBelowPoint = 2,
    VtChLabelLocationTypeCenter = 3,
    VtChLabelLocationTypeBase = 4,
    VtChLabelLocationTypeInside = 5,
    VtChLabelLocationTypeOutside = 6,
    VtChLabelLocationTypeLeft = 7,
    VtChLabelLocationTypeRight = 8
}VtChLabelLocationType;
enum
{
    VtChSubPlotLabelLocationTypeNone = 0,
    VtChSubPlotLabelLocationTypeAbove = 1,
    VtChSubPlotLabelLocationTypeBelow = 2,
    VtChSubPlotLabelLocationTypeCenter = 3
}VtChSubPlotLabelLocationType;
enum
{
    VtChPieWeightBasisNone = 0,
    VtChPieWeightBasisTotal = 1,
    VtChPieWeightBasisSeries = 2
}VtChPieWeightBasis;
enum
{
    VtChPieWeightStyleArea = 0,
    VtChPieWeightStyleDiameter = 1
}VtChPieWeightStyle;
enum
{
    VtChAxisIdX = 0,
    VtChAxisIdY = 1,
    VtChAxisIdY2 = 2,
    VtChAxisIdZ = 3,
    VtChAxisIdNone = 4
}VtChAxisId;
enum
{
    VtChDateIntervalTypeNone = 0,
    VtChDateIntervalTypeDaily = 1,
    VtChDateIntervalTypeWeekly = 2,
    VtChDateIntervalTypeSemimonthly = 3,
    VtChDateIntervalTypeMonthly = 4,
    VtChDateIntervalTypeYearly = 5
}VtChDateIntervalType;
enum
{
    VtChScaleTypeLinear = 0,
    VtChScaleTypeLogarithmic = 1,
    VtChScaleTypePercent = 2
}VtChScaleType;
enum
{
    VtChPercentAxisBasisMaxChart = 0,
    VtChPercentAxisBasisMaxRow = 1,
    VtChPercentAxisBasisMaxColumn = 2,
    VtChPercentAxisBasisSumChart = 3,
    VtChPercentAxisBasisSumRow = 4,
    VtChPercentAxisBasisSumColumn = 5
}VtChPercentAxisBasis;
enum
{
    VtChAxisTickStyleNone = 0,
    VtChAxisTickStyleCenter = 1,
    VtChAxisTickStyleInside = 2,
    VtChAxisTickStyleOutside = 3
}VtChAxisTickStyle;
enum
{
    VtChStatsMinimum = 1,
    VtChStatsMaximum = 2,
    VtChStatsMean = 4,
    VtChStatsStddev = 8,
    VtChStatsRegression = 16
}VtChStats;
enum
{
    VtChNoDisplay = 0,
    VtChDisplayPlot = 1,
    VtChLayoutPlot = 2,
    VtChDisplayLegend = 4,
    VtChLayoutLegend = 8,
    VtChLayoutSeries = 16,
    VtChPositionSection = 32
}VtChUpdateFlags;
enum
{
    VtChMouseFlagShiftKeyDown = 4,
    VtChMouseFlagControlKeyDown = 8
}VtChMouseFlag;
enum
{
    VtChSsLinkModeOff = 0,
    VtChSsLinkModeOn = 1,
    VtChSsLinkModeAutoParse = 2
}VtChSsLinkMode;
enum
{
    VtChDrawModeDraw = 0,
    VtChDrawModeBlit = 1
}VtChDrawMode;
enum
{
    VtChContourColorTypeAutomatic = 0,
    VtChContourColorTypeGradient = 1,
    VtChContourColorTypeManual = 2
}VtChContourColorType;
enum
{
    VtChContourDisplayTypeCBands = 0,
    VtChContourDisplayTypeCLines = 1
}VtChContourDisplayType;
enum
{
    VtChSurfaceBaseTypePedestal = 0,
    VtChSurfaceBaseTypeStandard = 1,
    VtChSurfaceBaseTypeStandardWithCBands = 2,
    VtChSurfaceBaseTypeStandardWithCLines = 3
}VtChSurfaceBaseType;
enum
{
    VtChSurfaceDisplayTypeNone = 0,
    VtChSurfaceDisplayTypeCBands = 1,
    VtChSurfaceDisplayTypeCLines = 2,
    VtChSurfaceDisplayTypeSolid = 3,
    VtChSurfaceDisplayTypeSolidWithCLines = 4
}VtChSurfaceDisplayType;
enum
{
    VtChSurfaceProjectionTypeNone = 0,
    VtChSurfaceProjectionTypeCBands = 1,
    VtChSurfaceProjectionTypeCLines = 2
}VtChSurfaceProjectionType;
enum
{
    VtChSurfaceWireframeTypeNone = 0,
    VtChSurfaceWireframeTypeMajor = 1,
    VtChSurfaceWireframeTypeMajorAndMinor = 2
}VtChSurfaceWireframeType;
enum
{
    VtBorderStyleNone = 0,
    VtBorderStyleFixedSingle = 1
}VtBorderStyle;
enum
{
    VtMousePointerDefault = 0,
    VtMousePointerArrow = 1,
    VtMousePointerCross = 2,
    VtMousePointerIbeam = 3,
    VtMousePointerIcon = 4,
    VtMousePointerSize = 5,
    VtMousePointerSizeNESW = 6,
    VtMousePointerSizeNS = 7,
    VtMousePointerSizeNWSE = 8,
    VtMousePointerSizeWE = 9,
    VtMousePointerUpArrow = 10,
    VtMousePointerHourGlass = 11,
    VtMousePointerNoDrop = 12,
    VtMousePointerArrowHourGlass = 13,
    VtMousePointerArrowQuestion = 14,
    VtMousePointerSizeAll = 15
}VtMousePointer;


// 操作
public:

// _DMSChart

// Functions
//

	BOOL get_AutoIncrement()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoIncrement(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_RandomFill()
	{
		BOOL result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_RandomFill(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_chartType()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_chartType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_Column()
	{
		short result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_Column(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_ColumnCount()
	{
		short result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_ColumnCount(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ColumnLabel()
	{
		CString result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ColumnLabel(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_ColumnLabelCount()
	{
		short result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_ColumnLabelCount(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_ColumnLabelIndex()
	{
		short result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_ColumnLabelIndex(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Data()
	{
		CString result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Data(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_FootnoteText()
	{
		CString result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_FootnoteText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Repaint()
	{
		BOOL result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Repaint(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_Row()
	{
		short result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_Row(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_RowCount()
	{
		short result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_RowCount(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_RowLabel()
	{
		CString result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_RowLabel(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_RowLabelCount()
	{
		short result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_RowLabelCount(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_RowLabelIndex()
	{
		short result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_RowLabelIndex(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_SeriesColumn()
	{
		short result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_SeriesColumn(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SeriesType()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SeriesType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowLegend()
	{
		BOOL result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowLegend(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_DrawMode()
	{
		long result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DrawMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BorderStyle()
	{
		long result;
		InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BorderStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_hWnd()
	{
		long result;
		InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Title()
	{
		LPDISPATCH result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Footnote()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_TitleText()
	{
		CString result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_TitleText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Stacking()
	{
		BOOL result;
		InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Stacking(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TextLengthType()
	{
		long result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TextLengthType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AllowSelections()
	{
		BOOL result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AllowSelections(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AllowSeriesSelection()
	{
		BOOL result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AllowSeriesSelection(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AllowDynamicRotation()
	{
		BOOL result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AllowDynamicRotation(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_ActiveSeriesCount()
	{
		short result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Backdrop()
	{
		LPDISPATCH result;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Legend()
	{
		LPDISPATCH result;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_DataGrid()
	{
		LPDISPATCH result;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Plot()
	{
		LPDISPATCH result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_AllowDithering()
	{
		BOOL result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AllowDithering(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DoSetCursor()
	{
		BOOL result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DoSetCursor(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Chart3d()
	{
		BOOL result;
		InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	VARIANT get_ChartData()
	{
		VARIANT result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_ChartData(VARIANT newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	long get_Chart()
	{
		long result;
		InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_MousePointer()
	{
		long result;
		InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MousePointer(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Refresh()
	{
		InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EditPaste()
	{
		InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EditCopy()
	{
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Layout()
	{
		InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ToDefaults()
	{
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SelectPart(short part, short index1, short index2, short index3, short index4)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, parms, part, index1, index2, index3, index4);
	}
	void GetSelectedPart(short * part, short * index1, short * index2, short * index3, short * index4)
	{
		static BYTE parms[] = VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, part, index1, index2, index3, index4);
	}
	void TwipsToChartPart(long xVal, long yVal, short * part, short * index1, short * index2, short * index3, short * index4)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xVal, yVal, part, index1, index2, index3, index4);
	}
	long get_OLEDragMode()
	{
		long result;
		InvokeHelper(0x60e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_OLEDragMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x60e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_OLEDropMode()
	{
		long result;
		InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_OLEDropMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void OLEDrag()
	{
		InvokeHelper(0x610, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPUNKNOWN get_DataSource()
	{
		LPUNKNOWN result;
		InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	void putref_DataSource(LPUNKNOWN newValue)
	{
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x47, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_DataMember()
	{
		CString result;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_DataMember(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x4b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

// Properties
//



};
