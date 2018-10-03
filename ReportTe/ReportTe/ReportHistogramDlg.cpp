// ReportHistogramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportPrint.h"
#include "ReportHistogramDlg.h"
#include "afxdialogex.h"


// CReportHistogramDlg dialog

IMPLEMENT_DYNAMIC(CReportHistogramDlg, CDialog)

	CReportHistogramDlg::CReportHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportHistogramDlg::IDD, pParent)
	, m_FlagJtce(0)
	, m_Chart()
{
	for (int i=0;i<4;i++)
	{
		m_dwGZMAVGSwing[i]         = 0.0f;  //额状面平均摆幅
		m_dwGZMCEFANGVEL[i]        = 0.0f;  //额状面侧方摆速
		m_dwGZMGOGOffset[i]        = 0.0f;  //平均重心额状面偏移量
		m_fLMaxPresKneeJointTor[i] = 0.0f;  //左膝最大承力力矩
		m_fRMaxPresKneeJointTor[i] = 0.0f;  //右膝最大承力力矩	
		m_fLeftPower[i]            = 0.0f;  //左下肢做功功率
		m_fRightPower[i]           = 0.0f;  //右下肢做功功率
		m_fEditLLimbMaxAcc[i]      = 0.0f;  
		m_fEditRLimbMaxAcc[i]      = 0.0f;  
		m_fLKneeJointMax[i]		   = 0.0f;	//左膝最大角度z
		m_fRKneeJointMax[i]		   = 0.0f;	//右膝最大角度

		m_fLTBQSPressureMax[i]	   = 0.0f;			//同步左侧最大顶力
		m_fRTBQSPressureMax[i]	   = 0.0f;			//同步右侧最大顶力
		m_fLTBQSPressureMean[i]	   = 0.0f;			//同步左侧平均顶力
		m_fRTBQSPressureMean[i]	   = 0.0f;			//同步右侧平均顶力
		m_fLJTQSPressureMax[i]	   = 0.0f;			//交替左侧最大顶力
		m_fRJTQSPressureMax[i]	   = 0.0f;			//交替右侧最大顶力
		m_fLJTQSPressureMean[i]	   = 0.0f;			//交替左侧平均顶力
		m_fRJTQSPressureMean[i]	   = 0.0f;			//交替右侧平均顶力
	}

	m_strHisFilePath01 = _T(""); //第一个图片文件名称
	m_strHisFilePath02 = _T(""); //第二个图片文件名称
	m_strHisFilePath03 = _T(""); //第三个图片文件名称
	m_strHisFilePath04 = _T(""); //第四个图片文件名称
	m_strHisFile01 = _T("");     //第一个图片文件名称
	m_strHisFile02 = _T("");     //第二个图片文件名称
	m_strHisFile03 = _T("");     //第三个图片文件名称
	m_strHisFile04 = _T("");     //第四个图片文件名称

}

CReportHistogramDlg::~CReportHistogramDlg()
{
}

void CReportHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SHOW, m_btnShowHistogram);
	DDX_Radio(pDX, IDC_RADIO_JTCE, m_FlagJtce);

	//  DDX_Control(pDX, IDC_MSCHART, m_chartt);
	DDX_Control(pDX, IDC_MSCHART, m_Chart);

}


BEGIN_MESSAGE_MAP(CReportHistogramDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_GRAPH1, &CReportHistogramDlg::OnBtnGraph1)
	ON_BN_CLICKED(IDC_BTN_GRAPH2, &CReportHistogramDlg::OnBtnGraph2)
	ON_BN_CLICKED(IDC_BTN_GRAPH3, &CReportHistogramDlg::OnBtnGraph3)
	ON_BN_CLICKED(IDC_BTN_GRAPH4, &CReportHistogramDlg::OnBtnGraph4)
	ON_BN_CLICKED(IDC_BTN_RETURN, &CReportHistogramDlg::OnBtnReturn)
	ON_BN_CLICKED(IDC_BTN_SAVE_BMP, &CReportHistogramDlg::OnBtnSaveBmp)
	ON_BN_CLICKED(IDC_BTN_SHOW, &CReportHistogramDlg::OnBtnShow)
	ON_BN_CLICKED(IDC_RADIO_DLXCS, &CReportHistogramDlg::OnRadioDlxcs)
	ON_BN_CLICKED(IDC_RADIO_JTCE, &CReportHistogramDlg::OnRadioJtce)
	ON_BN_CLICKED(IDC_RADIO_JTQSCE, &CReportHistogramDlg::OnRadioJtqsce)
	ON_BN_CLICKED(IDC_RADIO_TBQSCE, &CReportHistogramDlg::OnRadioTbqsce)
	ON_BN_CLICKED(IDC_RADIO_YDXHIS, &CReportHistogramDlg::OnRadioYdxhis)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CReportHistogramDlg message handlers
void CReportHistogramDlg::InitChart() 
{
	m_Chart.put_TitleText("参数直方图报告");
	m_Chart.put_Enabled( FALSE );
	// 下面两句改变背景色
	((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).put_Style(1);
	((CVcColor)((CVcBrush)((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).get_Brush()).get_FillColor()).Set(255, 255, 255);

	// 4条曲线	
	m_Chart.put_ColumnCount(4); 

	// 显示图例
	m_Chart.put_ShowLegend(TRUE);
	m_Chart.put_Column(1);
	m_Chart.put_ColumnLabel((LPCTSTR)"图例1");
	m_Chart.put_Column(2);
	m_Chart.put_ColumnLabel((LPCTSTR)"图例2");
	m_Chart.put_Column(3);
	m_Chart.put_ColumnLabel((LPCTSTR)"图例3");
	m_Chart.put_Column(4);
	m_Chart.put_ColumnLabel((LPCTSTR)"图例4");

	VARIANT var;
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// 不自动标注Y轴刻度
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum(100);	// Y轴最大刻度
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y轴最小刻度
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y轴刻度5等分
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// 每刻度一个刻度线
	((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y轴名称

	// 线色
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);

	//// 线宽(对点线图有效)
	((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
	((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
	((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);


	((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
	((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
	((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
	((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);

}
BOOL CReportHistogramDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	//CRect rect;

	//m_ctrlShowWnd.GetClientRect( &rect );
	//if( !m_Chart.Create("直方图显示", WS_CHILD| WS_VISIBLE, rect, &m_ctrlShowWnd, 10))
	//	return false;

	InitChart();	
	m_Chart.put_chartType(1);	
	InitDrawChart();	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CReportHistogramDlg::InitDrawChart() 
{
	int nRowCount = 4;
	m_Chart.put_RowCount(nRowCount);

	VARIANT var;
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_Auto(FALSE);			// 不自动标注X轴刻度
	((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerLabel(1);// 每刻度一个标注
	((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerTick(1);// 每刻度一个刻度线
	((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_AxisTitle()).put_Text("");	        // X轴名称
	for(int row = 1; row <= nRowCount; ++row)
	{	
		m_Chart.put_Row(row);
		m_Chart.put_RowLabel((LPCTSTR)_T(""));
		((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 1, 0, 0);
		((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 2, 0, 0);
		((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 3, 0, 0);
		((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 4, 0, 0);

	}

	m_Chart.Refresh();	
}

void CReportHistogramDlg::OnBtnGraph1()
{
	// TODO: Add your control notification handler code here
	// int     nPathFlag;
	//CString strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath;
	//	
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//{
	//	MessageBox("病人目前没有保存任何信息!", "信息提示", MB_ICONWARNING);
	//	return;   
	//}

	//CString strFileName = _T("");

	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.his)|*.his",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath01 = FileDlg.GetPathName( );
	//		m_strHisFile01     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME1))->SetWindowText( m_strHisFile01 );
	//	}
	//}
	//else if ( m_FlagJtce == 1 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.dyn)|*.dyn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath01 = FileDlg.GetPathName( );
	//		m_strHisFile01     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME1))->SetWindowText( m_strHisFile01 );
	//	}
	//}
	//else if ( m_FlagJtce == 2 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.kin)|*.kin",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath01 = FileDlg.GetPathName( );
	//		m_strHisFile01     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME1))->SetWindowText( m_strHisFile01 );
	//	}
	//}
	//else if ( m_FlagJtce == 3 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.syn)|*.syn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath01 = FileDlg.GetPathName( );
	//		m_strHisFile01     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME1))->SetWindowText( m_strHisFile01 );
	//	}
	//}
	//else if ( m_FlagJtce == 4 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.alt)|*.alt",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath01 = FileDlg.GetPathName( );
	//		m_strHisFile01     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME1))->SetWindowText( m_strHisFile01 );
	//	}
	//}
}


void CReportHistogramDlg::OnBtnGraph2()
{
	// TODO: Add your control notification handler code here
	//  int     nPathFlag;
	//CString strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath;
	//
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//{
	//	MessageBox("病人目前没有保存任何信息!", "信息提示", MB_ICONWARNING);
	//	return;   
	//}
	//
	//CString strFileName = _T("");
	//
	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.his)|*.his",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath02 = FileDlg.GetPathName( );
	//		m_strHisFile02     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME2))->SetWindowText( m_strHisFile02 );
	//	}
	//}
	//else if ( m_FlagJtce == 1 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.dyn)|*.dyn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath02 = FileDlg.GetPathName( );
	//		m_strHisFile02     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME2))->SetWindowText( m_strHisFile02 );
	//	}
	//}
	//else if ( m_FlagJtce == 2 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.kin)|*.kin",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath02 = FileDlg.GetPathName( );
	//		m_strHisFile02     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME2))->SetWindowText( m_strHisFile02 );
	//	}
	//}
	//else if ( m_FlagJtce == 3 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.syn)|*.syn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath02 = FileDlg.GetPathName( );
	//		m_strHisFile02     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME2))->SetWindowText( m_strHisFile02 );
	//	}
	//}
	//else if ( m_FlagJtce == 4 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.alt)|*.alt",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath02 = FileDlg.GetPathName( );
	//		m_strHisFile02     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME2))->SetWindowText( m_strHisFile02 );
	//	}
	//}
}


void CReportHistogramDlg::OnBtnGraph3()
{
	// TODO: Add your control notification handler code here
	// int     nPathFlag;
	//CString strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath;
	//
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//{
	//	MessageBox("病人目前没有保存任何信息!", "信息提示", MB_ICONWARNING);
	//	return;   
	//}
	//
	//CString strFileName = _T("");

	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.his)|*.his",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath03 = FileDlg.GetPathName( );
	//		m_strHisFile03     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME3))->SetWindowText( m_strHisFile03 );
	//	}
	//}
	//else if ( m_FlagJtce == 1 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.dyn)|*.dyn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath03 = FileDlg.GetPathName( );
	//		m_strHisFile03     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME3))->SetWindowText( m_strHisFile03 );
	//	}
	//}
	//else if ( m_FlagJtce == 2 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.kin)|*.kin",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath03 = FileDlg.GetPathName( );
	//		m_strHisFile03     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME3))->SetWindowText( m_strHisFile03 );
	//	}
	//}
	//else if ( m_FlagJtce == 3 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.syn)|*.syn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath03 = FileDlg.GetPathName( );
	//		m_strHisFile03     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME3))->SetWindowText( m_strHisFile03 );
	//	}
	//}
	//else if ( m_FlagJtce == 4 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.alt)|*.alt",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath03 = FileDlg.GetPathName( );
	//		m_strHisFile03     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME3))->SetWindowText( m_strHisFile03 );
	//	}
	//}
}


void CReportHistogramDlg::OnBtnGraph4()
{
	// TODO: Add your control notification handler code here
	// int     nPathFlag;
	//CString strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath;
	//
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //目录不存在
	//{
	//	MessageBox("病人目前没有保存任何信息!", "信息提示", MB_ICONWARNING);
	//	return;   
	//}
	//
	//CString strFileName = _T("");
	//
	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.his)|*.his",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath04 = FileDlg.GetPathName( );
	//		m_strHisFile04     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME4))->SetWindowText( m_strHisFile04 );
	//	}
	//}
	//else if ( m_FlagJtce == 1 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.dyn)|*.dyn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath04 = FileDlg.GetPathName( );
	//		m_strHisFile04     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME4))->SetWindowText( m_strHisFile04 );
	//	}
	//}
	//else if ( m_FlagJtce == 2 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.kin)|*.kin",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath04 = FileDlg.GetPathName( );
	//		m_strHisFile04     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME4))->SetWindowText( m_strHisFile04 );
	//	}
	//}
	//else if ( m_FlagJtce == 3 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.syn)|*.syn",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath04 = FileDlg.GetPathName( );
	//		m_strHisFile04     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME4))->SetWindowText( m_strHisFile04 );
	//	}
	//}
	//else if ( m_FlagJtce == 4 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"直方图文件 (*.alt)|*.alt",NULL);   
	//	FileDlg.m_ofn.lpstrInitialDir = strReporPath;   
	//	if( FileDlg.DoModal() == IDOK)
	//	{
	//		m_strHisFilePath04 = FileDlg.GetPathName( );
	//		m_strHisFile04     = FileDlg.GetFileName();
	//		((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME4))->SetWindowText( m_strHisFile04 );
	//	}
	//}
}
void CReportHistogramDlg::Clear()
{
	m_strHisFilePath01 = _T(""); //第一个图片文件名称
	m_strHisFilePath02 = _T(""); //第二个图片文件名称
	m_strHisFilePath03 = _T(""); //第三个图片文件名称
	m_strHisFilePath04 = _T(""); //第四个图片文件名称
	m_strHisFile01 = _T("");     //第一个图片文件名称
	m_strHisFile02 = _T("");     //第二个图片文件名称
	m_strHisFile03 = _T("");     //第三个图片文件名称
	m_strHisFile04 = _T("");     //第四个图片文件名称
	((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME1))->SetWindowText( m_strHisFile01 );
	((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME2))->SetWindowText( m_strHisFile02 );
	((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME3))->SetWindowText( m_strHisFile03 );
	((CEdit *) GetDlgItem(IDC_EDIT_GRAPHNAME4))->SetWindowText( m_strHisFile04 );
}

void CReportHistogramDlg::OnBtnReturn()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CReportHistogramDlg::OnBtnSaveBmp()
{
	// TODO: Add your control notification handler code here
	//	SYSTEMTIME st;     //st用来保存函数获取的时间信息
	//CString strDate;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	//GetLocalTime(&st);
	//strDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	//
	////生成bmp格式训练图形
	//RECT rect;
	//CDC  * pGraphDC = m_ctrlShowWnd.GetDC();

	////图像文件名称
	//int     nPathFlag;
	//m_strBmpFileName = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath 
	//				   + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode
	//				   + '\\' + ((CBalanceSysApp*)AfxGetApp())->m_strDate;
	//nPathFlag  = _chdir( m_strBmpFileName );
	//if( nPathFlag == -1 )                        //目录不存在
	//	CreateDirectory (m_strBmpFileName, NULL);   //创建目录

	//if ( m_FlagJtce == 0 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "静态参数直方图" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 1 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "动力学参数直方图" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 2 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "运动学参数直方图" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 3 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "同步屈伸测试参数直方图" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 4 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "交替屈伸测试参数直方图" + ".bmp" ;
	//}

	//   m_ctrlShowWnd.GetClientRect( &rect);
	//   m_ObjectWriteBmp.SaveRectToBitmap( pGraphDC, &rect,(LPSTR)m_strBmpFileName.GetBuffer(0) );
	//
	//ReleaseDC( pGraphDC );
}


void CReportHistogramDlg::OnBtnShow()
{
	// TODO: Add your control notification handler code here
	ReadData();
	ShowChart();	
	m_Chart.put_chartType(1);	
	DrawChart();		
}


void CReportHistogramDlg::OnRadioDlxcs()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 1;	//动力学参数
	Clear();

	InitChart();//初始化直方图
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioJtce()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 0;	//静态测试参数
	Clear();

	InitChart();//初始化直方图
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioJtqsce()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 4;	//交替屈伸测试参数
	Clear();

	InitChart();//初始化直方图
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioTbqsce()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 3;	//同步屈伸测试参数
	Clear();

	InitChart();//初始化直方图
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioYdxhis()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 2;	//运动学参数
	Clear();
	InitChart();//初始化直方图
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

	CRect rect;
	GetClientRect(&rect);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	this->GetClientRect(&rect);
	dc.FillRect(&rect,&brush);  //用FillRect成员函数利用笔刷填充指定区域
	brush.DeleteObject();	
	// Do not call CDialog::OnPaint() for painting messages
}


HBRUSH CReportHistogramDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	static HBRUSH hbrStatic = ::CreateSolidBrush( RGB(255, 255, 255) );
	if ( nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkColor( RGB(255, 255, 255) );
		return hbrStatic ; //返回该刷	
	}	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
void CReportHistogramDlg::SizeChange(CWnd *pWnd)
{

	int x,y;
	CRect     rectEdit,rectDlg;   
	int     nX,nY,SizeX,SizeY;
	CRect crt;	

	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);

	pWnd->GetClientRect(rectEdit);            //获得文本框矩形,左上角坐标(0,0)   
	SizeX=rectEdit.right;
	SizeY=rectEdit.bottom;
	pWnd->ClientToScreen(rectEdit);                  //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标   
	GetClientRect(rectDlg);                    //获得对话框矩形,左上角坐标(0,0)   
	ClientToScreen(rectDlg);                   //转换到屏幕坐标,左上角坐标为对话框在屏幕的坐标   

	nX=rectEdit.left-rectDlg.left;             //他们的差即为文本框在对话框中的X坐标   
	nY=rectEdit.top-rectDlg.top;               //他们的差即为文本框在对话框中的Y坐标   

	crt.left = nX*x/1024;
	crt.right=crt.left+SizeX*x/1024;
	crt.top= nY*y/907;
	crt.bottom=crt.top+SizeY*y/907;
	pWnd->MoveWindow(crt);

}
void CReportHistogramDlg::ReadData()
{
	//m_fMaxValue = 0.0f;
	//for (int i=0;i<4;i++)
	//{
	//	m_dwGZMAVGSwing[i]         = 0.0f;  //额状面平均摆幅
	//	m_dwGZMCEFANGVEL[i]        = 0.0f;  //额状面侧方摆速
	//	m_dwGZMGOGOffset[i]        = 0.0f;  //平均重心额状面偏移量
	//	m_fLMaxPresKneeJointTor[i] = 0.0f;  //左膝最大承力力矩
	//	m_fRMaxPresKneeJointTor[i] = 0.0f;  //右膝最大承力力矩	
	//	m_fLeftPower[i]            = 0.0f;  //左下肢做功功率
	//	m_fRightPower[i]           = 0.0f;  //右下肢做功功率
	//	m_fEditLLimbMaxAcc[i]      = 0.0f;  
	//	m_fEditRLimbMaxAcc[i]      = 0.0f;  
	//	m_fLKneeJointMax[i]		   = 0.0f;	//左膝最大角度
	//	m_fRKneeJointMax[i]		   = 0.0f;	//右膝最大角度

	//	m_fLTBQSPressureMax[i]	   = 0.0f;			//同步左侧最大顶力
	//	m_fRTBQSPressureMax[i]	   = 0.0f;			//同步右侧最大顶力
	//	m_fLTBQSPressureMean[i]	   = 0.0f;			//同步左侧平均顶力
	//	m_fRTBQSPressureMean[i]	   = 0.0f;			//同步右侧平均顶力
	//	m_fLJTQSPressureMax[i]	   = 0.0f;			//交替左侧最大顶力
	//	m_fRJTQSPressureMax[i]	   = 0.0f;			//交替右侧最大顶力
	//	m_fLJTQSPressureMean[i]	   = 0.0f;			//交替左侧平均顶力
	//	m_fRJTQSPressureMean[i]	   = 0.0f;			//交替右侧平均顶力
	//}

	//   m_strFileDataTime01 = _T("");
	//   m_strFileDataTime02 = _T("");
	//   m_strFileDataTime03 = _T("");
	//   m_strFileDataTime04 = _T("");

	//CFile fDataFile;
	//CFileException fileException;
	//CFileStatus rStatus; 
	//CTime       cFileDataTime;

	//if( m_strHisFilePath01 != "" )
	//{
	//	if( fDataFile.Open( m_strHisFilePath01,CFile::modeRead, &fileException ) )
	//	{
	//		if ( m_FlagJtce == 0 )
	//		{
	//			fDataFile.Read( &m_dwGZMAVGSwing[0], sizeof(float ) ); //额状面平均摆幅
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[0], sizeof(float) ); //额状面侧方摆速
	//			fDataFile.Read( &m_dwGZMGOGOffset[0], sizeof(float) ); //平均重心额状面偏移量
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[0] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[0]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[0] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[0]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[0] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[0]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[0], sizeof(float) ); //左膝最大承力力矩
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[0], sizeof(float) ); //右膝最大承力力矩
	//			fDataFile.Read( &m_fLeftPower[0], sizeof(float) ); //左下肢做功功率
	//			fDataFile.Read( &m_fRightPower[0], sizeof(float) ); //右下肢做功功率
	//			if( m_fMaxValue <= fabs( m_fLMaxPresKneeJointTor[0] ) )
	//				m_fMaxValue = m_fLMaxPresKneeJointTor[0]; 
	//			if( m_fMaxValue <= fabs( m_fRMaxPresKneeJointTor[0] ) )
	//				m_fMaxValue = m_fRMaxPresKneeJointTor[0]; 
	//			if( m_fMaxValue <= fabs( m_fLeftPower[0] ) )
	//				m_fMaxValue = m_fLeftPower[0]; 
	//			if( m_fMaxValue <= fabs( m_fRightPower[0] ) )
	//				m_fMaxValue = m_fRightPower[0]; 
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			fDataFile.Read( &m_fLKneeJointMax[0], sizeof(float)); //左膝最大角度
	//			fDataFile.Read( &m_fRKneeJointMax[0], sizeof(float)); //右膝最大角度
	//			fDataFile.Read( &m_fEditLLimbMaxAcc[0], sizeof(float)); //左下肢顶力变化率最大值
	//			fDataFile.Read( &m_fEditRLimbMaxAcc[0], sizeof(float)); //右下肢顶力变化率最大值

	//			if( m_fMaxValue <= fabs( m_fLKneeJointMax[0] ) )
	//				m_fMaxValue = m_fLKneeJointMax[0]; 
	//			if( m_fMaxValue <= fabs( m_fRKneeJointMax[0] ) )
	//				m_fMaxValue = m_fRKneeJointMax[0]; 
	//			if( m_fMaxValue <= fabs( m_fEditLLimbMaxAcc[0] ) )
	//				m_fMaxValue = m_fEditLLimbMaxAcc[0]; 
	//			if( m_fMaxValue <= fabs( m_fEditRLimbMaxAcc[0] ) )
	//				m_fMaxValue = m_fEditRLimbMaxAcc[0]; 
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			fDataFile.Read( &m_fLTBQSPressureMax[0], sizeof(float) ); //同步左侧最大顶力
	//			fDataFile.Read( &m_fRTBQSPressureMax[0], sizeof(float) ); //同步右侧最大顶力
	//			fDataFile.Read( &m_fLTBQSPressureMean[0], sizeof(float) ); //同步左侧平均顶力
	//			fDataFile.Read( &m_fRTBQSPressureMean[0], sizeof(float) ); //同步右侧平均顶力

	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMax[0] ) )
	//				m_fMaxValue = m_fLTBQSPressureMax[0]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMax[0] ) )
	//				m_fMaxValue = m_fRTBQSPressureMax[0]; 
	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMean[0] ) )
	//				m_fMaxValue = m_fLTBQSPressureMean[0]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMean[0] ) )
	//				m_fMaxValue = m_fRTBQSPressureMean[0]; 
	//		}
	//		else
	//		{
	//			fDataFile.Read( &m_fLJTQSPressureMax[0], sizeof(float) ); //交替左侧最大顶力
	//			fDataFile.Read( &m_fRJTQSPressureMax[0], sizeof(float) ); //交替右侧最大顶力
	//			fDataFile.Read( &m_fLJTQSPressureMean[0], sizeof(float) ); //交替左侧平均顶力
	//			fDataFile.Read( &m_fRJTQSPressureMean[0], sizeof(float) ); //交替右侧平均顶力
	//		
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMax[0] ) )
	//				m_fMaxValue = m_fLJTQSPressureMax[0]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMax[0] ) )
	//				m_fMaxValue = m_fRJTQSPressureMax[0]; 
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMean[0] ) )
	//				m_fMaxValue = m_fLJTQSPressureMean[0]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMean[0] ) )
	//				m_fMaxValue = m_fRJTQSPressureMean[0]; 				
	//		}
	//		fDataFile.GetStatus( rStatus );
	//		cFileDataTime = rStatus.m_ctime;
	//		m_strFileDataTime01.Format( "%d-%d-%d %d:%d",cFileDataTime.GetYear(),cFileDataTime.GetMonth(),cFileDataTime.GetDay(),
	//                                      cFileDataTime.GetHour(),cFileDataTime.GetMinute() );
	//		fDataFile.Close( );
	//	}
	//}
	//if( m_strHisFilePath02 != "" )
	//{
	//	if( fDataFile.Open( m_strHisFilePath02,CFile::modeRead, &fileException ) )
	//	{
	//		if ( m_FlagJtce == 0 )
	//		{
	//			fDataFile.Read( &m_dwGZMAVGSwing[1], sizeof(float) ); //额状面平均摆幅
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[1], sizeof(float) );//额状面侧方摆速
	//			fDataFile.Read( &m_dwGZMGOGOffset[1], sizeof(float) );//平均重心额状面偏移量
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[1] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[1]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[1] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[1]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[1] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[1]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[1], sizeof(float) ); //左膝最大承力力矩
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[1], sizeof(float) ); //右膝最大承力力矩
	//			fDataFile.Read( &m_fLeftPower[1], sizeof(float) ); //左下肢做功功率
	//			fDataFile.Read( &m_fRightPower[1], sizeof(float) ); //右下肢做功功率
	//			if( m_fMaxValue <= fabs( m_fLMaxPresKneeJointTor[1] ) )
	//				m_fMaxValue = m_fLMaxPresKneeJointTor[1]; 
	//			if( m_fMaxValue <= fabs( m_fRMaxPresKneeJointTor[1] ) )
	//				m_fMaxValue = m_fRMaxPresKneeJointTor[1]; 
	//			if( m_fMaxValue <= fabs( m_fLeftPower[1] ) )
	//				m_fMaxValue = m_fLeftPower[1]; 
	//			if( m_fMaxValue <= fabs( m_fRightPower[1] ) )
	//				m_fMaxValue = m_fRightPower[1]; 
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			fDataFile.Read( &m_fLKneeJointMax[1], sizeof(float)); //左膝最大角度
	//			fDataFile.Read( &m_fRKneeJointMax[1], sizeof(float)); //右膝最大角度
	//			fDataFile.Read( &m_fEditLLimbMaxAcc[1], sizeof(float) ); 
	//			fDataFile.Read( &m_fEditRLimbMaxAcc[1], sizeof(float) ); 
	//			if( m_fMaxValue <= fabs( m_fLKneeJointMax[1] ) )
	//				m_fMaxValue = m_fLKneeJointMax[1]; 
	//			if( m_fMaxValue <= fabs( m_fRKneeJointMax[1] ) )
	//				m_fMaxValue = m_fRKneeJointMax[1]; 
	//			if( m_fMaxValue <= fabs( m_fEditLLimbMaxAcc[1] ) )
	//				m_fMaxValue = m_fEditLLimbMaxAcc[1]; 
	//			if( m_fMaxValue <= fabs( m_fEditRLimbMaxAcc[1] ) )
	//				m_fMaxValue = m_fEditRLimbMaxAcc[1]; 
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			fDataFile.Read( &m_fLTBQSPressureMax[1], sizeof(float) ); //同步左侧最大顶力
	//			fDataFile.Read( &m_fRTBQSPressureMax[1], sizeof(float) ); //同步右侧最大顶力
	//			fDataFile.Read( &m_fLTBQSPressureMean[1], sizeof(float) ); //同步左侧平均顶力
	//			fDataFile.Read( &m_fRTBQSPressureMean[1], sizeof(float) ); //同步右侧平均顶力
	//			
	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMax[1] ) )
	//				m_fMaxValue = m_fLTBQSPressureMax[1]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMax[1] ) )
	//				m_fMaxValue = m_fRTBQSPressureMax[1]; 
	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMean[1] ) )
	//				m_fMaxValue = m_fLTBQSPressureMean[1]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMean[1] ) )
	//				m_fMaxValue = m_fRTBQSPressureMean[1]; 
	//		}
	//		else
	//		{
	//			fDataFile.Read( &m_fLJTQSPressureMax[1], sizeof(float) ); //交替左侧最大顶力
	//			fDataFile.Read( &m_fRJTQSPressureMax[1], sizeof(float) ); //交替右侧最大顶力
	//			fDataFile.Read( &m_fLJTQSPressureMean[1], sizeof(float) ); //交替左侧平均顶力
	//			fDataFile.Read( &m_fRJTQSPressureMean[1], sizeof(float) ); //交替右侧平均顶力
	//			
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMax[1] ) )
	//				m_fMaxValue = m_fLJTQSPressureMax[1]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMax[1] ) )
	//				m_fMaxValue = m_fRJTQSPressureMax[1]; 
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMean[1] ) )
	//				m_fMaxValue = m_fLJTQSPressureMean[1]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMean[1] ) )
	//				m_fMaxValue = m_fRJTQSPressureMean[1]; 				
	//		}
	//		fDataFile.GetStatus( rStatus );
	//		cFileDataTime = rStatus.m_ctime;
	//		m_strFileDataTime02.Format( "%d-%d-%d %d:%d",cFileDataTime.GetYear(),cFileDataTime.GetMonth(),cFileDataTime.GetDay(),
	//			                        cFileDataTime.GetHour(),cFileDataTime.GetMinute() );
	//		fDataFile.Close( );
	//	}
	//}			
	//if( m_strHisFilePath03 != "" )
	//{
	//	if( fDataFile.Open( m_strHisFilePath03,CFile::modeRead, &fileException ) )
	//	{
	//		if ( m_FlagJtce == 0 )
	//		{
	//			fDataFile.Read( &m_dwGZMAVGSwing[2], sizeof(float) ); //额状面平均摆幅
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[2], sizeof(float) );//额状面侧方摆速
	//			fDataFile.Read( &m_dwGZMGOGOffset[2], sizeof(float) );//平均重心额状面偏移量
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[2] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[2]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[2] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[2]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[2] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[2]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[2], sizeof(float) ); //左膝最大承力力矩
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[2], sizeof(float) ); //右膝最大承力力矩
	//			fDataFile.Read( &m_fLeftPower[2], sizeof(float) ); //左下肢做功功率
	//			fDataFile.Read( &m_fRightPower[2], sizeof(float) ); //右下肢做功功率
	//			if( m_fMaxValue <= fabs( m_fLMaxPresKneeJointTor[2] ) )
	//				m_fMaxValue = m_fLMaxPresKneeJointTor[2]; 
	//			if( m_fMaxValue <= fabs( m_fRMaxPresKneeJointTor[2] ) )
	//				m_fMaxValue = m_fRMaxPresKneeJointTor[2]; 
	//			if( m_fMaxValue <= fabs( m_fLeftPower[2] ) )
	//				m_fMaxValue = m_fLeftPower[2]; 
	//			if( m_fMaxValue <= fabs( m_fRightPower[2] ) )
	//				m_fMaxValue = m_fRightPower[2]; 
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			fDataFile.Read( &m_fLKneeJointMax[2], sizeof(float)); //左膝最大角度
	//			fDataFile.Read( &m_fRKneeJointMax[2], sizeof(float)); //右膝最大角度
	//			fDataFile.Read( &m_fEditLLimbMaxAcc[2], sizeof(float) ); 
	//			fDataFile.Read( &m_fEditRLimbMaxAcc[2], sizeof(float) ); 
	//			if( m_fMaxValue <= fabs( m_fLKneeJointMax[2] ) )
	//				m_fMaxValue = m_fLKneeJointMax[2]; 
	//			if( m_fMaxValue <= fabs( m_fRKneeJointMax[2] ) )
	//				m_fMaxValue = m_fRKneeJointMax[2]; 
	//			if( m_fMaxValue <= fabs( m_fEditLLimbMaxAcc[2] ) )
	//				m_fMaxValue = m_fEditLLimbMaxAcc[2]; 
	//			if( m_fMaxValue <= fabs( m_fEditRLimbMaxAcc[2] ) )
	//				m_fMaxValue = m_fEditRLimbMaxAcc[2]; 
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			fDataFile.Read( &m_fLTBQSPressureMax[2], sizeof(float) ); //同步左侧最大顶力
	//			fDataFile.Read( &m_fRTBQSPressureMax[2], sizeof(float) ); //同步右侧最大顶力
	//			fDataFile.Read( &m_fLTBQSPressureMean[2], sizeof(float) ); //同步左侧平均顶力
	//			fDataFile.Read( &m_fRTBQSPressureMean[2], sizeof(float) ); //同步右侧平均顶力
	//			
	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMax[2] ) )
	//				m_fMaxValue = m_fLTBQSPressureMax[2]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMax[2] ) )
	//				m_fMaxValue = m_fRTBQSPressureMax[2]; 
	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMean[2] ) )
	//				m_fMaxValue = m_fLTBQSPressureMean[2]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMean[2] ) )
	//				m_fMaxValue = m_fRTBQSPressureMean[2]; 
	//		}
	//		else
	//		{
	//			fDataFile.Read( &m_fLJTQSPressureMax[2], sizeof(float) ); //交替左侧最大顶力
	//			fDataFile.Read( &m_fRJTQSPressureMax[2], sizeof(float) ); //交替右侧最大顶力
	//			fDataFile.Read( &m_fLJTQSPressureMean[2], sizeof(float) ); //交替左侧平均顶力
	//			fDataFile.Read( &m_fRJTQSPressureMean[2], sizeof(float) ); //交替右侧平均顶力
	//			
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMax[2] ) )
	//				m_fMaxValue = m_fLJTQSPressureMax[2]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMax[2] ) )
	//				m_fMaxValue = m_fRJTQSPressureMax[2]; 
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMean[2] ) )
	//				m_fMaxValue = m_fLJTQSPressureMean[2]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMean[2] ) )
	//				m_fMaxValue = m_fRJTQSPressureMean[2]; 				
	//		}
	//		fDataFile.GetStatus( rStatus );
	//		cFileDataTime = rStatus.m_ctime;
	//		m_strFileDataTime03.Format( "%d-%d-%d %d:%d",cFileDataTime.GetYear(),cFileDataTime.GetMonth(),cFileDataTime.GetDay(),
	//			                        cFileDataTime.GetHour(),cFileDataTime.GetMinute() );
	//		fDataFile.Close( );
	//	}
	//}
	//if( m_strHisFilePath04 != "" )
	//{		
	//	if( fDataFile.Open( m_strHisFilePath04,CFile::modeRead, &fileException ) )
	//	{
	//		if ( m_FlagJtce == 0 )
	//		{
	//			fDataFile.Read( &m_dwGZMAVGSwing[3], sizeof(float) ); //额状面平均摆幅
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[3], sizeof(float) );//额状面侧方摆速
	//			fDataFile.Read( &m_dwGZMGOGOffset[3], sizeof(float) );//平均重心额状面偏移量
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[3] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[3]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[3] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[3]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[3] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[3]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[3], sizeof(float) ); //左膝最大承力力矩
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[3], sizeof(float) ); //右膝最大承力力矩
	//			fDataFile.Read( &m_fLeftPower[3], sizeof(float) ); //左下肢做功功率
	//			fDataFile.Read( &m_fRightPower[3], sizeof(float) ); //右下肢做功功率
	//			if( m_fMaxValue <= fabs( m_fLMaxPresKneeJointTor[3] ) )
	//				m_fMaxValue = m_fLMaxPresKneeJointTor[3]; 
	//			if( m_fMaxValue <= fabs( m_fRMaxPresKneeJointTor[3] ) )
	//				m_fMaxValue = m_fRMaxPresKneeJointTor[3]; 
	//			if( m_fMaxValue <= fabs( m_fLeftPower[3] ) )
	//				m_fMaxValue = m_fLeftPower[3]; 
	//			if( m_fMaxValue <= fabs( m_fRightPower[3] ) )
	//				m_fMaxValue = m_fRightPower[3]; 
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			fDataFile.Read( &m_fLKneeJointMax[3], sizeof(float)); //左膝最大角度
	//			fDataFile.Read( &m_fRKneeJointMax[3], sizeof(float)); //右膝最大角度
	//			fDataFile.Read( &m_fEditLLimbMaxAcc[3], sizeof(float) ); 
	//			fDataFile.Read( &m_fEditRLimbMaxAcc[3], sizeof(float) ); 
	//			if( m_fMaxValue <= fabs( m_fLKneeJointMax[3] ) )
	//				m_fMaxValue = m_fLKneeJointMax[3]; 
	//			if( m_fMaxValue <= fabs( m_fRKneeJointMax[3] ) )
	//				m_fMaxValue = m_fRKneeJointMax[3]; 
	//			if( m_fMaxValue <= fabs( m_fEditLLimbMaxAcc[3] ) )
	//				m_fMaxValue = m_fEditLLimbMaxAcc[3]; 
	//			if( m_fMaxValue <= fabs( m_fEditRLimbMaxAcc[3] ) )
	//				m_fMaxValue = m_fEditRLimbMaxAcc[3]; 
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			fDataFile.Read( &m_fLTBQSPressureMax[3], sizeof(float) ); //同步左侧最大顶力
	//			fDataFile.Read( &m_fRTBQSPressureMax[3], sizeof(float) ); //同步右侧最大顶力
	//			fDataFile.Read( &m_fLTBQSPressureMean[3], sizeof(float) ); //同步左侧平均顶力
	//			fDataFile.Read( &m_fRTBQSPressureMean[3], sizeof(float) ); //同步右侧平均顶力
	//			
	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMax[3] ) )
	//				m_fMaxValue = m_fLTBQSPressureMax[3]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMax[3] ) )
	//				m_fMaxValue = m_fRTBQSPressureMax[3]; 
	//			if( m_fMaxValue <= fabs( m_fLTBQSPressureMean[3] ) )
	//				m_fMaxValue = m_fLTBQSPressureMean[3]; 
	//			if( m_fMaxValue <= fabs( m_fRTBQSPressureMean[3] ) )
	//				m_fMaxValue = m_fRTBQSPressureMean[3]; 
	//		}
	//		else
	//		{
	//			fDataFile.Read( &m_fLJTQSPressureMax[3], sizeof(float) ); //交替左侧最大顶力
	//			fDataFile.Read( &m_fRJTQSPressureMax[3], sizeof(float) ); //交替右侧最大顶力
	//			fDataFile.Read( &m_fLJTQSPressureMean[3], sizeof(float) ); //交替左侧平均顶力
	//			fDataFile.Read( &m_fRJTQSPressureMean[3], sizeof(float) ); //交替右侧平均顶力
	//			
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMax[3] ) )
	//				m_fMaxValue = m_fLJTQSPressureMax[3]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMax[3] ) )
	//				m_fMaxValue = m_fRJTQSPressureMax[3]; 
	//			if( m_fMaxValue <= fabs( m_fLJTQSPressureMean[3] ) )
	//				m_fMaxValue = m_fLJTQSPressureMean[3]; 
	//			if( m_fMaxValue <= fabs( m_fRJTQSPressureMean[3] ) )
	//				m_fMaxValue = m_fRJTQSPressureMean[3]; 				
	//		}
	//		fDataFile.GetStatus( rStatus );
	//		cFileDataTime = rStatus.m_ctime;
	//		m_strFileDataTime04.Format( "%d-%d-%d %d:%d",cFileDataTime.GetYear(),cFileDataTime.GetMonth(),cFileDataTime.GetDay(),
	//			                        cFileDataTime.GetHour(),cFileDataTime.GetMinute() );
	//		fDataFile.Close( );
	//	}
	//}
}
void CReportHistogramDlg::DrawChart() 
{
	//int nRowCount = 4;
	//m_Chart.put_RowCount(nRowCount);

	//VARIANT var;
	//((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_Auto(FALSE);			// 不自动标注X轴刻度
	//((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerLabel(1);// 每刻度一个标注
	//((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerTick(1);// 每刻度一个刻度线
	//((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_AxisTitle()).put_Text("训练日期");	        // X轴名称
	//for(int row = 1; row <= nRowCount; ++row)
	//{	
	//	m_Chart.put_Row(row);
	//	m_Chart.put_RowLabel((LPCTSTR)_T(""));
	//	((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 1, 0, 0);
	//	((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 2, 0, 0);
	//	((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 3, 0, 0);
	//	((CVcDataGrid)m_Chart.get_DataGrid()).SetData(row, 4, 0, 0);

	//}

	//m_Chart.Refresh();	

	//for( int i=0; i<4; i++ )
	//{
	//	switch( i )
	//	{
	//	case 0:
	//		if( m_FlagJtce == 0 )
	//		{
	//			if( m_strHisFilePath01 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime01);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_dwGZMAVGSwing[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_dwGZMCEFANGVEL[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_dwGZMGOGOffset[i]), 0);
	//			}
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			if( m_strHisFilePath01 != "" )
	//			{
	//			
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime01);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);	 //左膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);	 //右膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0); //左下肢做功功率
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//右下肢做功功率
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath01 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime01);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLKneeJointMax[i]), 0);	//左膝最大角度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRKneeJointMax[i]), 0);	//右膝最大角度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fEditLLimbMaxAcc[i]), 0); 
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fEditRLimbMaxAcc[i]), 0);
	//			}
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			if( m_strHisFilePath01 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime01);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);	//同步左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);	//同步右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//同步左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//同步右侧平均顶力
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath01 != "" )
	//			{
	//	
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime01);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);	//交替左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);	//交替右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//交替左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//交替右侧平均顶力
	//			}
	//		}
	//		break;
	//	case 1:
	//		if( m_FlagJtce == 0 )
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_dwGZMAVGSwing[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_dwGZMCEFANGVEL[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_dwGZMGOGOffset[i]), 0);
	//			}
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);	//左膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);	//右膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//左下肢做功功率
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//右下肢做功功率
	//			}
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLKneeJointMax[i]), 0);//左膝最大角度力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRKneeJointMax[i]), 0);//右膝最大角度力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fEditLLimbMaxAcc[i]), 0);//左下肢最大加速度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fEditRLimbMaxAcc[i]), 0);
	//			}
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);//同步左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);//同步右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//同步左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//同步右侧平均顶力
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);//交替左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);//交替右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//交替左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//交替右侧平均顶力
	//			}
	//		}
	//		break;
	//	case 2:
	//		if( m_FlagJtce == 0 )
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//			
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_dwGZMAVGSwing[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_dwGZMCEFANGVEL[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_dwGZMGOGOffset[i]), 0);
	//				
	//			}
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);//左膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);//右膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//左下肢做功功率
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//右下肢做功功率
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//				
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLKneeJointMax[i]), 0);//左膝最大角度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRKneeJointMax[i]), 0);//右膝最大角度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fEditLLimbMaxAcc[i]), 0);//左下肢最大加速度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fEditRLimbMaxAcc[i]), 0);//右下肢最大加速度
	//			}
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);//同步左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);//同步右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//同步左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//同步右侧平均顶力
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);//交替左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);//交替右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//交替左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//交替右侧平均顶力
	//			}
	//		}
	//		break;
	//	case 3:
	//		if( m_FlagJtce == 0 )
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{
	//				
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_dwGZMAVGSwing[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_dwGZMCEFANGVEL[i]), 0);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_dwGZMGOGOffset[i]), 0);
	//			}
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);//左膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);//右膝最大承力力矩
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//左下肢做功功率
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//右下肢做功功率
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);//左膝最大角度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);//右膝最大角度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//左下肢最大加速度
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//右下肢最大加速度
	//			}
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);//同步左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);//同步右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//同步左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//同步右侧平均顶力
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{

	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);//交替左侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);//交替右侧最大顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//交替左侧平均顶力
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//交替右侧平均顶力
	//			}
	//		}
	//		break;
	//	}
	//	
	//m_Chart.Refresh();	
}
void CReportHistogramDlg::ShowChart() 
{
	//	// 下面两句改变背景色
		((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).put_Style(1);
		((CVcColor)((CVcBrush)((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).get_Brush()).get_FillColor()).Set(255, 255, 255);
		if ( m_FlagJtce == 0 )//静态姿势图
		{		
			// 设置标题
			m_Chart.put_TitleText("静态参数直方图报告");
			// 3条曲线
			m_Chart.put_ColumnCount(3); 
	
			// 显示图例
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"额状面平均摆幅(cm)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"额状面侧方摆速(cm/s)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"平均重心额状面偏移量(cm)");
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// 不自动标注Y轴刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y轴最大刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y轴最小刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y轴刻度5等分
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// 每刻度一个刻度线
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y轴名称
	
	
			// 线色
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			
			// 线宽(对点线图有效)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
			// 0: 不显示	1: 显示在柱状图外
			// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
	
		}
		else if ( m_FlagJtce == 1 ) //动力学参数
		{
			
			// 设置标题
			m_Chart.put_TitleText("动力学参数直方图报告");
			// 3条曲线
			m_Chart.put_ColumnCount(4); 
	
			// 显示图例
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"左膝最大承力力矩(N.m)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"右膝最大承力力矩(N.m)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"左下肢做功功率(J/s)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"右下肢做功功率(J/s)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// 不自动标注Y轴刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y轴最大刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y轴最小刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y轴刻度5等分
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// 每刻度一个刻度线
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y轴名称
	
			// 线色
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// 线宽(对点线图有效)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
			// 0: 不显示	1: 显示在柱状图外
			// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
	
		}
		else if ( m_FlagJtce == 2 )//运动学参数
		{
			// 设置标题
			m_Chart.put_TitleText("运动学参数直方图报告");
			// 3条曲线
			m_Chart.put_ColumnCount(4); 
	
			// 显示图例
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"左下肢最大用力(kg)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"右下肢最大用力(kg)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"左下肢力变化最大值(kg/s)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"右下肢力变化最大值(kg/s)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// 不自动标注Y轴刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y轴最大刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y轴最小刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y轴刻度5等分
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// 每刻度一个刻度线
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y轴名称
	
			// 线色
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// 线宽(对点线图有效)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
			// 0: 不显示	1: 显示在柱状图外
			// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
		}
		else if ( m_FlagJtce == 3 ) //同步屈伸测试参数
		{
			// 设置标题
			m_Chart.put_TitleText("同步屈伸测试参数直方图报告");
			// 3条曲线
			m_Chart.put_ColumnCount(4); 
	
			// 显示图例
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"左侧最大顶力(公斤)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"右侧最大顶力(公斤)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"左侧平均顶力(公斤)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"右侧平均顶力(公斤)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// 不自动标注Y轴刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y轴最大刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y轴最小刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y轴刻度5等分
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// 每刻度一个刻度线
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y轴名称
	
			// 线色
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// 线宽(对点线图有效)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
			// 0: 不显示	1: 显示在柱状图外
			// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
		}
		else if ( m_FlagJtce == 4 ) //交替屈伸测试参数
		{
			// 设置标题
			m_Chart.put_TitleText("交替屈伸测试参数直方图报告");
			// 3条曲线
			m_Chart.put_ColumnCount(4); 
	
			// 显示图例
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"左侧最大顶力(公斤)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"右侧最大顶力(公斤)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"左侧平均顶力(公斤)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"右侧平均顶力(公斤)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// 不自动标注Y轴刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y轴最大刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y轴最小刻度
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y轴刻度5等分
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// 每刻度一个刻度线
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y轴名称
			// 线色
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// 线宽(对点线图有效)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
			// 0: 不显示	1: 显示在柱状图外
			// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
		}
}
