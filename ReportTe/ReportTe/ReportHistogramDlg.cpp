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
		m_dwGZMAVGSwing[i]         = 0.0f;  //��״��ƽ���ڷ�
		m_dwGZMCEFANGVEL[i]        = 0.0f;  //��״��෽����
		m_dwGZMGOGOffset[i]        = 0.0f;  //ƽ�����Ķ�״��ƫ����
		m_fLMaxPresKneeJointTor[i] = 0.0f;  //��ϥ����������
		m_fRMaxPresKneeJointTor[i] = 0.0f;  //��ϥ����������	
		m_fLeftPower[i]            = 0.0f;  //����֫��������
		m_fRightPower[i]           = 0.0f;  //����֫��������
		m_fEditLLimbMaxAcc[i]      = 0.0f;  
		m_fEditRLimbMaxAcc[i]      = 0.0f;  
		m_fLKneeJointMax[i]		   = 0.0f;	//��ϥ���Ƕ�z
		m_fRKneeJointMax[i]		   = 0.0f;	//��ϥ���Ƕ�

		m_fLTBQSPressureMax[i]	   = 0.0f;			//ͬ����������
		m_fRTBQSPressureMax[i]	   = 0.0f;			//ͬ���Ҳ������
		m_fLTBQSPressureMean[i]	   = 0.0f;			//ͬ�����ƽ������
		m_fRTBQSPressureMean[i]	   = 0.0f;			//ͬ���Ҳ�ƽ������
		m_fLJTQSPressureMax[i]	   = 0.0f;			//������������
		m_fRJTQSPressureMax[i]	   = 0.0f;			//�����Ҳ������
		m_fLJTQSPressureMean[i]	   = 0.0f;			//�������ƽ������
		m_fRJTQSPressureMean[i]	   = 0.0f;			//�����Ҳ�ƽ������
	}

	m_strHisFilePath01 = _T(""); //��һ��ͼƬ�ļ�����
	m_strHisFilePath02 = _T(""); //�ڶ���ͼƬ�ļ�����
	m_strHisFilePath03 = _T(""); //������ͼƬ�ļ�����
	m_strHisFilePath04 = _T(""); //���ĸ�ͼƬ�ļ�����
	m_strHisFile01 = _T("");     //��һ��ͼƬ�ļ�����
	m_strHisFile02 = _T("");     //�ڶ���ͼƬ�ļ�����
	m_strHisFile03 = _T("");     //������ͼƬ�ļ�����
	m_strHisFile04 = _T("");     //���ĸ�ͼƬ�ļ�����

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
	m_Chart.put_TitleText("����ֱ��ͼ����");
	m_Chart.put_Enabled( FALSE );
	// ��������ı䱳��ɫ
	((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).put_Style(1);
	((CVcColor)((CVcBrush)((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).get_Brush()).get_FillColor()).Set(255, 255, 255);

	// 4������	
	m_Chart.put_ColumnCount(4); 

	// ��ʾͼ��
	m_Chart.put_ShowLegend(TRUE);
	m_Chart.put_Column(1);
	m_Chart.put_ColumnLabel((LPCTSTR)"ͼ��1");
	m_Chart.put_Column(2);
	m_Chart.put_ColumnLabel((LPCTSTR)"ͼ��2");
	m_Chart.put_Column(3);
	m_Chart.put_ColumnLabel((LPCTSTR)"ͼ��3");
	m_Chart.put_Column(4);
	m_Chart.put_ColumnLabel((LPCTSTR)"ͼ��4");

	VARIANT var;
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// ���Զ���עY��̶�
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum(100);	// Y�����̶�
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y����С�̶�
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y��̶�5�ȷ�
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// ÿ�̶�һ���̶���
	((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y������

	// ��ɫ
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
	((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);

	//// �߿�(�Ե���ͼ��Ч)
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
	//if( !m_Chart.Create("ֱ��ͼ��ʾ", WS_CHILD| WS_VISIBLE, rect, &m_ctrlShowWnd, 10))
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
	((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_Auto(FALSE);			// ���Զ���עX��̶�
	((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerLabel(1);// ÿ�̶�һ����ע
	((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerTick(1);// ÿ�̶�һ���̶���
	((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_AxisTitle()).put_Text("");	        // X������
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
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//{
	//	MessageBox("����Ŀǰû�б����κ���Ϣ!", "��Ϣ��ʾ", MB_ICONWARNING);
	//	return;   
	//}

	//CString strFileName = _T("");

	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.his)|*.his",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.dyn)|*.dyn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.kin)|*.kin",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.syn)|*.syn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.alt)|*.alt",NULL);   
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
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//{
	//	MessageBox("����Ŀǰû�б����κ���Ϣ!", "��Ϣ��ʾ", MB_ICONWARNING);
	//	return;   
	//}
	//
	//CString strFileName = _T("");
	//
	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.his)|*.his",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.dyn)|*.dyn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.kin)|*.kin",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.syn)|*.syn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.alt)|*.alt",NULL);   
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
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//{
	//	MessageBox("����Ŀǰû�б����κ���Ϣ!", "��Ϣ��ʾ", MB_ICONWARNING);
	//	return;   
	//}
	//
	//CString strFileName = _T("");

	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.his)|*.his",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.dyn)|*.dyn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.kin)|*.kin",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.syn)|*.syn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.alt)|*.alt",NULL);   
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
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//{
	//	MessageBox("����Ŀǰû�б����κ���Ϣ!", "��Ϣ��ʾ", MB_ICONWARNING);
	//	return;   
	//}
	//
	//CString strFileName = _T("");
	//
	//if ( m_FlagJtce == 0 )
	//{
	//	CFileDialog   FileDlg(TRUE,"(*.his)|*.his",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.his)|*.his",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.dyn)|*.dyn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.dyn)|*.dyn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.kin)|*.kin",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.kin)|*.kin",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.syn)|*.syn",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.syn)|*.syn",NULL);   
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
	//	CFileDialog   FileDlg(TRUE,"(*.alt)|*.alt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ֱ��ͼ�ļ� (*.alt)|*.alt",NULL);   
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
	m_strHisFilePath01 = _T(""); //��һ��ͼƬ�ļ�����
	m_strHisFilePath02 = _T(""); //�ڶ���ͼƬ�ļ�����
	m_strHisFilePath03 = _T(""); //������ͼƬ�ļ�����
	m_strHisFilePath04 = _T(""); //���ĸ�ͼƬ�ļ�����
	m_strHisFile01 = _T("");     //��һ��ͼƬ�ļ�����
	m_strHisFile02 = _T("");     //�ڶ���ͼƬ�ļ�����
	m_strHisFile03 = _T("");     //������ͼƬ�ļ�����
	m_strHisFile04 = _T("");     //���ĸ�ͼƬ�ļ�����
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
	//	SYSTEMTIME st;     //st�������溯����ȡ��ʱ����Ϣ
	//CString strDate;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	//GetLocalTime(&st);
	//strDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	//
	////����bmp��ʽѵ��ͼ��
	//RECT rect;
	//CDC  * pGraphDC = m_ctrlShowWnd.GetDC();

	////ͼ���ļ�����
	//int     nPathFlag;
	//m_strBmpFileName = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath 
	//				   + "\\" + ((CBalanceSysApp*)AfxGetApp())->m_strCode
	//				   + '\\' + ((CBalanceSysApp*)AfxGetApp())->m_strDate;
	//nPathFlag  = _chdir( m_strBmpFileName );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//	CreateDirectory (m_strBmpFileName, NULL);   //����Ŀ¼

	//if ( m_FlagJtce == 0 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "��̬����ֱ��ͼ" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 1 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "����ѧ����ֱ��ͼ" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 2 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "�˶�ѧ����ֱ��ͼ" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 3 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "ͬ��������Բ���ֱ��ͼ" + ".bmp" ;
	//}
	//if ( m_FlagJtce == 4 )
	//{
	//	m_strBmpFileName = m_strBmpFileName + "\\" + strDate + "����������Բ���ֱ��ͼ" + ".bmp" ;
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
	m_FlagJtce = 1;	//����ѧ����
	Clear();

	InitChart();//��ʼ��ֱ��ͼ
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioJtce()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 0;	//��̬���Բ���
	Clear();

	InitChart();//��ʼ��ֱ��ͼ
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioJtqsce()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 4;	//����������Բ���
	Clear();

	InitChart();//��ʼ��ֱ��ͼ
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioTbqsce()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 3;	//ͬ��������Բ���
	Clear();

	InitChart();//��ʼ��ֱ��ͼ
	m_Chart.put_chartType(1);	
	InitDrawChart();
}


void CReportHistogramDlg::OnRadioYdxhis()
{
	// TODO: Add your control notification handler code here
	m_FlagJtce = 2;	//�˶�ѧ����
	Clear();
	InitChart();//��ʼ��ֱ��ͼ
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
	dc.FillRect(&rect,&brush);  //��FillRect��Ա�������ñ�ˢ���ָ������
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
		return hbrStatic ; //���ظ�ˢ	
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

	pWnd->GetClientRect(rectEdit);            //����ı������,���Ͻ�����(0,0)   
	SizeX=rectEdit.right;
	SizeY=rectEdit.bottom;
	pWnd->ClientToScreen(rectEdit);                  //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������   
	GetClientRect(rectDlg);                    //��öԻ������,���Ͻ�����(0,0)   
	ClientToScreen(rectDlg);                   //ת������Ļ����,���Ͻ�����Ϊ�Ի�������Ļ������   

	nX=rectEdit.left-rectDlg.left;             //���ǵĲΪ�ı����ڶԻ����е�X����   
	nY=rectEdit.top-rectDlg.top;               //���ǵĲΪ�ı����ڶԻ����е�Y����   

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
	//	m_dwGZMAVGSwing[i]         = 0.0f;  //��״��ƽ���ڷ�
	//	m_dwGZMCEFANGVEL[i]        = 0.0f;  //��״��෽����
	//	m_dwGZMGOGOffset[i]        = 0.0f;  //ƽ�����Ķ�״��ƫ����
	//	m_fLMaxPresKneeJointTor[i] = 0.0f;  //��ϥ����������
	//	m_fRMaxPresKneeJointTor[i] = 0.0f;  //��ϥ����������	
	//	m_fLeftPower[i]            = 0.0f;  //����֫��������
	//	m_fRightPower[i]           = 0.0f;  //����֫��������
	//	m_fEditLLimbMaxAcc[i]      = 0.0f;  
	//	m_fEditRLimbMaxAcc[i]      = 0.0f;  
	//	m_fLKneeJointMax[i]		   = 0.0f;	//��ϥ���Ƕ�
	//	m_fRKneeJointMax[i]		   = 0.0f;	//��ϥ���Ƕ�

	//	m_fLTBQSPressureMax[i]	   = 0.0f;			//ͬ����������
	//	m_fRTBQSPressureMax[i]	   = 0.0f;			//ͬ���Ҳ������
	//	m_fLTBQSPressureMean[i]	   = 0.0f;			//ͬ�����ƽ������
	//	m_fRTBQSPressureMean[i]	   = 0.0f;			//ͬ���Ҳ�ƽ������
	//	m_fLJTQSPressureMax[i]	   = 0.0f;			//������������
	//	m_fRJTQSPressureMax[i]	   = 0.0f;			//�����Ҳ������
	//	m_fLJTQSPressureMean[i]	   = 0.0f;			//�������ƽ������
	//	m_fRJTQSPressureMean[i]	   = 0.0f;			//�����Ҳ�ƽ������
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
	//			fDataFile.Read( &m_dwGZMAVGSwing[0], sizeof(float ) ); //��״��ƽ���ڷ�
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[0], sizeof(float) ); //��״��෽����
	//			fDataFile.Read( &m_dwGZMGOGOffset[0], sizeof(float) ); //ƽ�����Ķ�״��ƫ����
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[0] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[0]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[0] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[0]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[0] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[0]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[0], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[0], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fLeftPower[0], sizeof(float) ); //����֫��������
	//			fDataFile.Read( &m_fRightPower[0], sizeof(float) ); //����֫��������
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
	//			fDataFile.Read( &m_fLKneeJointMax[0], sizeof(float)); //��ϥ���Ƕ�
	//			fDataFile.Read( &m_fRKneeJointMax[0], sizeof(float)); //��ϥ���Ƕ�
	//			fDataFile.Read( &m_fEditLLimbMaxAcc[0], sizeof(float)); //����֫�����仯�����ֵ
	//			fDataFile.Read( &m_fEditRLimbMaxAcc[0], sizeof(float)); //����֫�����仯�����ֵ

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
	//			fDataFile.Read( &m_fLTBQSPressureMax[0], sizeof(float) ); //ͬ����������
	//			fDataFile.Read( &m_fRTBQSPressureMax[0], sizeof(float) ); //ͬ���Ҳ������
	//			fDataFile.Read( &m_fLTBQSPressureMean[0], sizeof(float) ); //ͬ�����ƽ������
	//			fDataFile.Read( &m_fRTBQSPressureMean[0], sizeof(float) ); //ͬ���Ҳ�ƽ������

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
	//			fDataFile.Read( &m_fLJTQSPressureMax[0], sizeof(float) ); //������������
	//			fDataFile.Read( &m_fRJTQSPressureMax[0], sizeof(float) ); //�����Ҳ������
	//			fDataFile.Read( &m_fLJTQSPressureMean[0], sizeof(float) ); //�������ƽ������
	//			fDataFile.Read( &m_fRJTQSPressureMean[0], sizeof(float) ); //�����Ҳ�ƽ������
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
	//			fDataFile.Read( &m_dwGZMAVGSwing[1], sizeof(float) ); //��״��ƽ���ڷ�
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[1], sizeof(float) );//��״��෽����
	//			fDataFile.Read( &m_dwGZMGOGOffset[1], sizeof(float) );//ƽ�����Ķ�״��ƫ����
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[1] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[1]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[1] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[1]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[1] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[1]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[1], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[1], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fLeftPower[1], sizeof(float) ); //����֫��������
	//			fDataFile.Read( &m_fRightPower[1], sizeof(float) ); //����֫��������
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
	//			fDataFile.Read( &m_fLKneeJointMax[1], sizeof(float)); //��ϥ���Ƕ�
	//			fDataFile.Read( &m_fRKneeJointMax[1], sizeof(float)); //��ϥ���Ƕ�
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
	//			fDataFile.Read( &m_fLTBQSPressureMax[1], sizeof(float) ); //ͬ����������
	//			fDataFile.Read( &m_fRTBQSPressureMax[1], sizeof(float) ); //ͬ���Ҳ������
	//			fDataFile.Read( &m_fLTBQSPressureMean[1], sizeof(float) ); //ͬ�����ƽ������
	//			fDataFile.Read( &m_fRTBQSPressureMean[1], sizeof(float) ); //ͬ���Ҳ�ƽ������
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
	//			fDataFile.Read( &m_fLJTQSPressureMax[1], sizeof(float) ); //������������
	//			fDataFile.Read( &m_fRJTQSPressureMax[1], sizeof(float) ); //�����Ҳ������
	//			fDataFile.Read( &m_fLJTQSPressureMean[1], sizeof(float) ); //�������ƽ������
	//			fDataFile.Read( &m_fRJTQSPressureMean[1], sizeof(float) ); //�����Ҳ�ƽ������
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
	//			fDataFile.Read( &m_dwGZMAVGSwing[2], sizeof(float) ); //��״��ƽ���ڷ�
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[2], sizeof(float) );//��״��෽����
	//			fDataFile.Read( &m_dwGZMGOGOffset[2], sizeof(float) );//ƽ�����Ķ�״��ƫ����
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[2] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[2]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[2] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[2]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[2] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[2]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[2], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[2], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fLeftPower[2], sizeof(float) ); //����֫��������
	//			fDataFile.Read( &m_fRightPower[2], sizeof(float) ); //����֫��������
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
	//			fDataFile.Read( &m_fLKneeJointMax[2], sizeof(float)); //��ϥ���Ƕ�
	//			fDataFile.Read( &m_fRKneeJointMax[2], sizeof(float)); //��ϥ���Ƕ�
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
	//			fDataFile.Read( &m_fLTBQSPressureMax[2], sizeof(float) ); //ͬ����������
	//			fDataFile.Read( &m_fRTBQSPressureMax[2], sizeof(float) ); //ͬ���Ҳ������
	//			fDataFile.Read( &m_fLTBQSPressureMean[2], sizeof(float) ); //ͬ�����ƽ������
	//			fDataFile.Read( &m_fRTBQSPressureMean[2], sizeof(float) ); //ͬ���Ҳ�ƽ������
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
	//			fDataFile.Read( &m_fLJTQSPressureMax[2], sizeof(float) ); //������������
	//			fDataFile.Read( &m_fRJTQSPressureMax[2], sizeof(float) ); //�����Ҳ������
	//			fDataFile.Read( &m_fLJTQSPressureMean[2], sizeof(float) ); //�������ƽ������
	//			fDataFile.Read( &m_fRJTQSPressureMean[2], sizeof(float) ); //�����Ҳ�ƽ������
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
	//			fDataFile.Read( &m_dwGZMAVGSwing[3], sizeof(float) ); //��״��ƽ���ڷ�
	//			fDataFile.Read( &m_dwGZMCEFANGVEL[3], sizeof(float) );//��״��෽����
	//			fDataFile.Read( &m_dwGZMGOGOffset[3], sizeof(float) );//ƽ�����Ķ�״��ƫ����
	//			if( m_fMaxValue <= fabs( m_dwGZMAVGSwing[3] ) )
	//				m_fMaxValue = m_dwGZMAVGSwing[3]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMCEFANGVEL[3] ) )
	//				m_fMaxValue = m_dwGZMCEFANGVEL[3]; 
	//			if( m_fMaxValue <= fabs( m_dwGZMGOGOffset[3] ) )
	//				m_fMaxValue = m_dwGZMGOGOffset[3]; 
	//		}
	//		else if ( m_FlagJtce == 1 )
	//		{
	//			fDataFile.Read( &m_fLMaxPresKneeJointTor[3], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fRMaxPresKneeJointTor[3], sizeof(float) ); //��ϥ����������
	//			fDataFile.Read( &m_fLeftPower[3], sizeof(float) ); //����֫��������
	//			fDataFile.Read( &m_fRightPower[3], sizeof(float) ); //����֫��������
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
	//			fDataFile.Read( &m_fLKneeJointMax[3], sizeof(float)); //��ϥ���Ƕ�
	//			fDataFile.Read( &m_fRKneeJointMax[3], sizeof(float)); //��ϥ���Ƕ�
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
	//			fDataFile.Read( &m_fLTBQSPressureMax[3], sizeof(float) ); //ͬ����������
	//			fDataFile.Read( &m_fRTBQSPressureMax[3], sizeof(float) ); //ͬ���Ҳ������
	//			fDataFile.Read( &m_fLTBQSPressureMean[3], sizeof(float) ); //ͬ�����ƽ������
	//			fDataFile.Read( &m_fRTBQSPressureMean[3], sizeof(float) ); //ͬ���Ҳ�ƽ������
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
	//			fDataFile.Read( &m_fLJTQSPressureMax[3], sizeof(float) ); //������������
	//			fDataFile.Read( &m_fRJTQSPressureMax[3], sizeof(float) ); //�����Ҳ������
	//			fDataFile.Read( &m_fLJTQSPressureMean[3], sizeof(float) ); //�������ƽ������
	//			fDataFile.Read( &m_fRJTQSPressureMean[3], sizeof(float) ); //�����Ҳ�ƽ������
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
	//((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_Auto(FALSE);			// ���Զ���עX��̶�
	//((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerLabel(1);// ÿ�̶�һ����ע
	//((CVcCategoryScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_CategoryScale()).put_DivisionsPerTick(1);// ÿ�̶�һ���̶���
	//((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(0,var)).get_AxisTitle()).put_Text("ѵ������");	        // X������
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
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);	 //��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);	 //��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0); //����֫��������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//����֫��������
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath01 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime01);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLKneeJointMax[i]), 0);	//��ϥ���Ƕ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRKneeJointMax[i]), 0);	//��ϥ���Ƕ�
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
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);	//ͬ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);	//ͬ���Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//ͬ�����ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//ͬ���Ҳ�ƽ������
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath01 != "" )
	//			{
	//	
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime01);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);	//������������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);	//�����Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//�������ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//�����Ҳ�ƽ������
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
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);	//��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);	//��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//����֫��������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//����֫��������
	//			}
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLKneeJointMax[i]), 0);//��ϥ���Ƕ�����
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRKneeJointMax[i]), 0);//��ϥ���Ƕ�����
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fEditLLimbMaxAcc[i]), 0);//����֫�����ٶ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fEditRLimbMaxAcc[i]), 0);
	//			}
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);//ͬ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);//ͬ���Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//ͬ�����ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//ͬ���Ҳ�ƽ������
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath02 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime02);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);//������������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);//�����Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//�������ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//�����Ҳ�ƽ������
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
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);//��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);//��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//����֫��������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//����֫��������
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//				
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLKneeJointMax[i]), 0);//��ϥ���Ƕ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRKneeJointMax[i]), 0);//��ϥ���Ƕ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fEditLLimbMaxAcc[i]), 0);//����֫�����ٶ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fEditRLimbMaxAcc[i]), 0);//����֫�����ٶ�
	//			}
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);//ͬ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);//ͬ���Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//ͬ�����ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//ͬ���Ҳ�ƽ������
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath03 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime03);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);//������������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);//�����Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//�������ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//�����Ҳ�ƽ������
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
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);//��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);//��ϥ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//����֫��������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//����֫��������
	//			}
	//		}
	//		else if ( m_FlagJtce == 2 )
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLMaxPresKneeJointTor[i]), 0);//��ϥ���Ƕ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRMaxPresKneeJointTor[i]), 0);//��ϥ���Ƕ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLeftPower[i]), 0);//����֫�����ٶ�
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRightPower[i]), 0);//����֫�����ٶ�
	//			}
	//		}
	//		else if ( m_FlagJtce == 3 )
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{
	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLTBQSPressureMax[i]), 0);//ͬ����������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRTBQSPressureMax[i]), 0);//ͬ���Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLTBQSPressureMean[i]), 0);//ͬ�����ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRTBQSPressureMean[i]), 0);//ͬ���Ҳ�ƽ������
	//			}
	//		}
	//		else
	//		{
	//			if( m_strHisFilePath04 != "" )
	//			{

	//				m_Chart.put_Row(i+1);
	//				m_Chart.put_RowLabel((LPCTSTR)m_strFileDataTime04);
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 1, fabs(m_fLJTQSPressureMax[i]), 0);//������������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 2, fabs(m_fRJTQSPressureMax[i]), 0);//�����Ҳ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 3, fabs(m_fLJTQSPressureMean[i]), 0);//�������ƽ������
	//				((CVcDataGrid)m_Chart.get_DataGrid()).SetData(i+1, 4, fabs(m_fRJTQSPressureMean[i]), 0);//�����Ҳ�ƽ������
	//			}
	//		}
	//		break;
	//	}
	//	
	//m_Chart.Refresh();	
}
void CReportHistogramDlg::ShowChart() 
{
	//	// ��������ı䱳��ɫ
		((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).put_Style(1);
		((CVcColor)((CVcBrush)((CVcFill)((CVcBackdrop)m_Chart.get_Backdrop()).get_Fill()).get_Brush()).get_FillColor()).Set(255, 255, 255);
		if ( m_FlagJtce == 0 )//��̬����ͼ
		{		
			// ���ñ���
			m_Chart.put_TitleText("��̬����ֱ��ͼ����");
			// 3������
			m_Chart.put_ColumnCount(3); 
	
			// ��ʾͼ��
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"��״��ƽ���ڷ�(cm)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"��״��෽����(cm/s)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"ƽ�����Ķ�״��ƫ����(cm)");
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// ���Զ���עY��̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y�����̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y����С�̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y��̶�5�ȷ�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// ÿ�̶�һ���̶���
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y������
	
	
			// ��ɫ
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			
			// �߿�(�Ե���ͼ��Ч)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
			// 0: ����ʾ	1: ��ʾ����״ͼ��
			// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
	
		}
		else if ( m_FlagJtce == 1 ) //����ѧ����
		{
			
			// ���ñ���
			m_Chart.put_TitleText("����ѧ����ֱ��ͼ����");
			// 3������
			m_Chart.put_ColumnCount(4); 
	
			// ��ʾͼ��
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"��ϥ����������(N.m)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"��ϥ����������(N.m)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"����֫��������(J/s)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"����֫��������(J/s)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// ���Զ���עY��̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y�����̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y����С�̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y��̶�5�ȷ�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// ÿ�̶�һ���̶���
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y������
	
			// ��ɫ
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// �߿�(�Ե���ͼ��Ч)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
			// 0: ����ʾ	1: ��ʾ����״ͼ��
			// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
	
		}
		else if ( m_FlagJtce == 2 )//�˶�ѧ����
		{
			// ���ñ���
			m_Chart.put_TitleText("�˶�ѧ����ֱ��ͼ����");
			// 3������
			m_Chart.put_ColumnCount(4); 
	
			// ��ʾͼ��
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"����֫�������(kg)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"����֫�������(kg)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"����֫���仯���ֵ(kg/s)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"����֫���仯���ֵ(kg/s)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// ���Զ���עY��̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y�����̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y����С�̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y��̶�5�ȷ�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// ÿ�̶�һ���̶���
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y������
	
			// ��ɫ
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// �߿�(�Ե���ͼ��Ч)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
			// 0: ����ʾ	1: ��ʾ����״ͼ��
			// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
		}
		else if ( m_FlagJtce == 3 ) //ͬ��������Բ���
		{
			// ���ñ���
			m_Chart.put_TitleText("ͬ��������Բ���ֱ��ͼ����");
			// 3������
			m_Chart.put_ColumnCount(4); 
	
			// ��ʾͼ��
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"��������(����)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"�Ҳ������(����)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"���ƽ������(����)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"�Ҳ�ƽ������(����)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// ���Զ���עY��̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y�����̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y����С�̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y��̶�5�ȷ�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// ÿ�̶�һ���̶���
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y������
	
			// ��ɫ
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// �߿�(�Ե���ͼ��Ч)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
			// 0: ����ʾ	1: ��ʾ����״ͼ��
			// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
		}
		else if ( m_FlagJtce == 4 ) //����������Բ���
		{
			// ���ñ���
			m_Chart.put_TitleText("����������Բ���ֱ��ͼ����");
			// 3������
			m_Chart.put_ColumnCount(4); 
	
			// ��ʾͼ��
			m_Chart.put_ShowLegend(TRUE);
			m_Chart.put_Column(1);
			m_Chart.put_ColumnLabel((LPCTSTR)"��������(����)");
			m_Chart.put_Column(2);
			m_Chart.put_ColumnLabel((LPCTSTR)"�Ҳ������(����)");
			m_Chart.put_Column(3);
			m_Chart.put_ColumnLabel((LPCTSTR)"���ƽ������(����)");
			m_Chart.put_Column(4);
			m_Chart.put_ColumnLabel((LPCTSTR)"�Ҳ�ƽ������(����)");
	
	
			VARIANT var;
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Auto(FALSE);	// ���Զ���עY��̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Maximum((int)m_fMaxValue + 2);	// Y�����̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_Minimum(0);		// Y����С�̶�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MajorDivision(10);	// Y��̶�5�ȷ�
			((CVcValueScale)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_ValueScale()).put_MinorDivision(1);	// ÿ�̶�һ���̶���
			((CVcAxisTitle)((CVcAxis)((CVcPlot)m_Chart.get_Plot()).get_Axis(1,var)).get_AxisTitle()).put_Text("");	        // Y������
			// ��ɫ
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).Set(0, 0, 255);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).Set(255, 0, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 0);
			((CVcColor)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).Set(0, 255, 255);
			// �߿�(�Ե���ͼ��Ч)
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_Pen()).get_VtColor()).put_Width(50);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_Pen()).get_VtColor()).put_Width(100);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
			((CVcStatLine)((CVcPen)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_Pen()).get_VtColor()).put_Width(2);
	
	
			// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
			// 0: ����ʾ	1: ��ʾ����״ͼ��
			// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(1)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(2)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(3)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
			((CVcDataPointLabel)((CVcDataPoint)((CVcSeriesCollection)((CVcSeries)((CVcSeriesCollection)((CVcPlot)m_Chart.get_Plot()).get_SeriesCollection()).get_Item(4)).get_DataPoints()).get_Item(-1)).get_DataPointLabel()).put_LocationType(1);
		}
}
