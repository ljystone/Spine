
// mchartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mchart.h"
#include "mchartDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmchartDlg 对话框




CmchartDlg::CmchartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmchartDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmchartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCHART1, m_chartt);
}

BEGIN_MESSAGE_MAP(CmchartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CmchartDlg 消息处理程序

BOOL CmchartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_chartt.put_TitleText(_T("aaaaa"));

	CVcTitle vctitle;
	CVcFont	 vcFont;
	CVcColor vcColor;
	vctitle = m_chartt.get_Title();
	vcFont = vctitle.get_VtFont();
	vcColor = vcFont.get_VtColor();
	vcColor.Set(0,255,0);
	vcFont.put_Size(20);

	CVcBackdrop vcbackdrop;
	CVcFill vcfill;
	vcbackdrop = m_chartt.get_Backdrop();
	vcfill = vcbackdrop.get_Fill();
	vcfill.put_Style(1);

	CVcBrush vcbrush;
	vcbrush = vcfill.get_Brush();
	vcColor = vcbrush.get_FillColor();
	vcColor.Set(100,100,100);


	m_chartt.put_RowCount(15);
	m_chartt.put_Row(1);
	m_chartt.put_RowLabel((LPCTSTR)(_T("12")));

	m_chartt.put_Row(2);
	m_chartt.put_RowLabel((LPCTSTR)(_T("24")));

	/*for(int i = 1; i <= m_chartt.get_RowCount(); i ++)
	{
		CVcDataGrid vcDataGrid = m_chartt.get_DataGrid();
		vcDataGrid.SetData(i,1,rand() % 200,0);
	}*/

//	m_chartt.put_SeriesType(11);

	m_chartt.put_Stacking(TRUE);


	VARIANT var;

	CVcPlot vcplot;
	CVcAxis vcaxis;
	CVcAxisTitle vcAxistitle;

	vcplot = m_chartt.get_Plot();
	vcaxis = vcplot.get_Axis(0,var);
	vcAxistitle = vcaxis.get_AxisTitle();
	vcAxistitle.put_Text(_T("时间(s)"));

	vcaxis = vcplot.get_Axis(1,var);
	vcAxistitle = vcaxis.get_AxisTitle();
	vcAxistitle.put_Text(_T("点数"));
	
	CVcPlot vcPlot =  m_chartt.get_Plot();
	CVcAxis vcAxis = vcPlot.get_Axis(0,var);
	CVcCategoryScale vccat = vcAxis.get_CategoryScale();
	vccat.put_Auto(FALSE);
	vccat.put_DivisionsPerLabel(1);
	vccat.put_DivisionsPerTick(1);

	m_chartt.put_ColumnCount(1);

	vcAxis = vcPlot.get_Axis(1,var);
	CVcValueScale vcvalue = vcAxis.get_ValueScale();
	vcvalue.put_MajorDivision(25);
	vcvalue.put_Maximum(100);
	vcvalue.put_Minimum(0);


	CVcSeriesCollection vcseriescollection;
	vcseriescollection = vcplot.get_SeriesCollection();
	CVcSeries vcseries =  vcseriescollection.get_Item(1);

	

	CVcPen vcpen = vcseries.get_Pen();
	vcColor = vcpen.get_VtColor();
	vcColor.Set(255,0,0);
	vcpen.put_Width(25);





	CVcDataPoints datapoints;
	CVcDataPoint datatpont;
	datapoints = vcseries.get_DataPoints();
	CVcDataPointLabel vcdatapointslabel;
	datatpont = datapoints.get_Item(-1);
	vcdatapointslabel = datatpont.get_DataPointLabel();
	vcdatapointslabel.put_LocationType(1);
	



	CVcSeriesMarker vcseriesmarker;
	vcseriesmarker = vcseries.get_SeriesMarker();
	vcseriesmarker.put_Auto(FALSE);

	



	vcFont = vcdatapointslabel.get_VtFont();
	vcColor = vcFont.get_VtColor();
	vcColor.Set(255,255,0);

		
	CVcMarker vcmarker = datatpont.get_Marker();
	vcmarker.put_Size(150);
	vcmarker.put_Visible(TRUE);
	
	vcmarker.put_Style(10);

	

	vcColor = vcmarker.get_FillColor();
//	vcpen = vcmarker.get_Pen();
//	vcColor = vcpen.get_VtColor();
	vcColor.Set(0,255,255);

	vcpen = vcmarker.get_Pen();
	vcColor = vcpen.get_VtColor();
	vcColor.Set(0,255,255);



	vcpen = vcAxis.get_Pen();
	vcColor = vcpen.get_VtColor();
	vcColor.Set(0,255,0);


	CVcLabels vclabels;
	vclabels = vcAxis.get_Labels();
	CVcLabel vclabel;
	vclabel = vclabels.get_Item(1);
	vcFont = vclabel.get_VtFont();
	vcColor = vcFont.get_VtColor();
	vcColor.Set(255,255,0);

	

	vcAxis = vcplot.get_Axis(1,var);
	vcvalue = vcAxis.get_ValueScale();
	vcvalue.put_Auto(FALSE);
	vcvalue.put_Maximum(300);
	vcvalue.put_Minimum(-100);
	vcvalue.put_MajorDivision(20);
	vcvalue.put_MinorDivision(1);


	m_arrary.SetSize(15);
	int count = m_arrary.GetCount();
	for(int i = 0; i < m_arrary.GetCount(); i ++)
	{
		m_arrary[i] = rand() % 300;
	}

	CRgn rgn;
	m_chartt.GetUpdateRgn(&rgn);

	for(int i = 1; i <= m_chartt.get_RowCount(); i ++)
	{
		CVcDataGrid vcDataGrid = m_chartt.get_DataGrid();
		vcDataGrid.SetData(i,1,m_arrary[i - 1],0);
	}

	
	

	//SetTimer(1,500,NULL);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmchartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmchartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmchartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmchartDlg::showData()
{
	m_chartt.SetRedraw(FALSE);

	CRgn rgn;
	m_chartt.GetUpdateRgn(&rgn);

	for(int i = 1; i <= m_chartt.get_RowCount(); i ++)
	{
		CVcDataGrid vcDataGrid = m_chartt.get_DataGrid();
		vcDataGrid.SetData(i,1,m_arrary[i - 1],0);
	}

	m_chartt.SetRedraw(TRUE);
	m_chartt.InvalidateRgn(&rgn,FALSE);
}



void CmchartDlg::OnTimer(UINT_PTR nIDEvent)
{
//	

	if(m_arrary.GetSize() == 15)
	{
		m_arrary.RemoveAt(0);

		int size = m_arrary.GetSize();

		m_arrary.Add(rand() % 300);
		
	}
	else
	{
		int size = m_arrary.GetSize();
		m_arrary[size- 1] = rand() % 300;

	}

	showData();

//	m_chartt.put_RowCount(1);
//	m_chartt.put_RowCount(15);
	

	CDialogEx::OnTimer(nIDEvent);
}
BEGIN_EVENTSINK_MAP(CmchartDlg, CDialogEx)
	ON_EVENT(CmchartDlg, IDC_MSCHART1, 1550, CmchartDlg::OLEStartDragMschart1, VTS_PDISPATCH VTS_PI4)
	ON_EVENT(CmchartDlg, IDC_MSCHART1, DISPID_MOUSEMOVE, CmchartDlg::MouseMoveMschart1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CmchartDlg::OLEStartDragMschart1(LPDISPATCH* Data, long* AllowedEffects)
{
	// TODO: 在此处添加消息处理程序代码
}


void CmchartDlg::MouseMoveMschart1(short Button, short Shift, long X, long Y)
{
	CString ss;
	short whichPart = 0;
	short whichSeries = 0;
	short whichNumber = 0;
	short nIndex3 = 0;
	short nIndex4 = 0;
	m_chartt.TwipsToChartPart(X,Y,&whichPart,&whichSeries,&whichNumber,&nIndex3,&nIndex4);
	ss.Format(_T("x = %d y = %d whichpart = %d\n"),X,Y,whichPart);
	
	
		TRACE(ss);
}
