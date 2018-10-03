
// ReportTeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportPrint.h"
#include "ReportPrintDlg.h"
#include "ReportHistogramDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CReportTeDlg dialog



CReportTeDlg::CReportTeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReportTeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strTodayDate      = _T("");
	m_strCode           = _T("");
	m_strName           = _T("");
	m_strGender         = _T("");
	m_strAge            = _T("");
	m_uThighLength      = 0;
	m_uCrusLength       = 0;
	m_strWeight         = _T("");
	m_strSide           = _T("");
	m_TimeValue         = 0;
	//}}AFX_DATA_INIT

	m_strBmpFilePath01  = _T(""); //��һ��ͼƬ�ļ�����
	m_strBmpFilePath02  = _T(""); //�ڶ���ͼƬ�ļ�����
	m_strBmpFilePath03  = _T(""); //������ͼƬ�ļ�����
	m_strBmpFilePath04  = _T(""); //���ĸ�ͼƬ�ļ�����
	m_strBmpFile01      = _T(""); //��һ��ͼƬ�ļ�����
	m_strBmpFile02      = _T(""); //�ڶ���ͼƬ�ļ�����
	m_strBmpFile03      = _T(""); //������ͼƬ�ļ�����
	m_strBmpFile04      = _T(""); //���ĸ�ͼƬ�ļ�����

	m_strSelectDate     = _T("");
}

void CReportTeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_01, m_ctrlDateTime);
	DDX_Control(pDX, IDC_EDIT_REPORT_DATA, m_cReportData);
	DDX_Text(pDX, IDC_EDIT_TODAY_DATE, m_strTodayDate);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_GENDER, m_strGender);
	DDX_Text(pDX, IDC_EDIT_AGE, m_strAge);
	DDX_Text(pDX, IDC_EDIT_THIGH_LENGTH, m_uThighLength);
	DDX_Text(pDX, IDC_EDIT_CRUS_LENGTH, m_uCrusLength);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_strWeight);
	DDX_Text(pDX, IDC_EDIT_SIDE, m_strSide);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_01, m_TimeValue);
}

BEGIN_MESSAGE_MAP(CReportTeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BTN_GRAPH1, &CReportTeDlg::OnBtnGraph1)
	ON_BN_CLICKED(IDC_BTN_GRAPH2, &CReportTeDlg::OnBtnGraph2)
	ON_BN_CLICKED(IDC_BTN_GRAPH3, &CReportTeDlg::OnBtnGraph3)
	ON_BN_CLICKED(IDC_BTN_GRAPH4, &CReportTeDlg::OnBtnGraph4)
	ON_BN_CLICKED(IDC_BTN_HISTOGRAM, &CReportTeDlg::OnBtnHistogram)
	ON_BN_CLICKED(IDC_BTN_OPEN_REPORT, &CReportTeDlg::OnBtnOpenReport)
	ON_BN_CLICKED(IDC_BTN_PRINT_REPORT, &CReportTeDlg::OnBtnPrintReport)
	ON_BN_CLICKED(IDOK, &CReportTeDlg::OnOk)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_01, &CReportTeDlg::OnDtnDatetimechangeDatetimepicker01)
END_MESSAGE_MAP()


// CReportTeDlg message handlers

BOOL CReportTeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SYSTEMTIME st;
	CString strDate;
	GetLocalTime(&st);

	strDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	m_strTodayDate=strDate;
	UpdateData(false);
	CTime t(st, 0 );
	m_ctrlDateTime.SetTime( &t );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReportTeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReportTeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReportTeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CReportTeDlg::ReadReportData()
{
	CFile          DataFile;
	CFileException e;
	DWORD          dwDataSize;
	CString        strData;
	CString        m_strReportName;

	m_strReportName	 = 	"c:\test.txt";

	if( m_strReportName == _T(""))
		return;
	if( DataFile.Open( m_strReportName,CFile::modeRead , &e ) )
	{
		dwDataSize = DataFile.GetLength( );
		char *pBuf = new char[dwDataSize+1];
		DataFile.Read( pBuf, dwDataSize );
		pBuf[dwDataSize] = '\0';
		strData.Format("%s",pBuf);
		m_cReportData.SetWindowText(strData );
		delete []pBuf;

		DataFile.Close( );
	}
	return;
}

void CReportTeDlg::ReadReportFile(CString strFileName)
{
	CFile          DataFile;
	CFileException e;
	DWORD          dwDataSize;
	CString        strData;

	if( strFileName == _T(""))
		return;
	if( DataFile.Open( strFileName,CFile::modeRead , &e ) )
	{
		dwDataSize = DataFile.GetLength( );
		char *pBuf = new char[dwDataSize+1];
		DataFile.Read( pBuf, dwDataSize );
		pBuf[dwDataSize] = '\0';
		strData.Format("%s",pBuf);
	
		m_cReportData.SetWindowText(strData );
		
		delete []pBuf;

		DataFile.Close( );
	}
	return;
}

void CReportTeDlg::OnBtnGraph1()
{
	// TODO: Add your control notification handler code here
}


void CReportTeDlg::OnBtnGraph2()
{
	// TODO: Add your control notification handler code here
}


void CReportTeDlg::OnBtnGraph3()
{
	// TODO: Add your control notification handler code here
}


void CReportTeDlg::OnBtnGraph4()
{
	// TODO: Add your control notification handler code here
}




void CReportTeDlg::OnBtnHistogram()
{
	// TODO: Add your control notification handler code here
	//CReportHistogramDlg	Histo;
	//Histo.DoModal();
	WinExec("ReportHistogramDlg.exe", SW_SHOW);
}


void CReportTeDlg::OnBtnOpenReport()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	// int     nPathFlag;
	//CString strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath;

	//if( m_strSelectDate == _T("") )
	//	m_strSelectDate = m_strTodayDate;

	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//	return;   
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + m_strCode;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//{
	//	MessageBox("����Ŀǰû�б����κ���Ϣ!", "��Ϣ��ʾ", MB_ICONWARNING);
	//	return;   
	//}
	//strReporPath = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + m_strCode + "\\" + m_strSelectDate;
	//nPathFlag  = _chdir( strReporPath );
	//if( nPathFlag == -1 )                        //Ŀ¼������
	//{
	//	MessageBox("��ѡ���ڲ���û�б��汨����Ϣ!", "��Ϣ��ʾ", MB_ICONWARNING);
	//	return;   
	//}
	 // CString strDataPathini=((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + m_strCode+((CBalanceSysApp*)AfxGetApp())->m_strDate+"\n"+
		                     // +((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + m_strCode+"\n";	                       
	//m_strbtnBmpFileName[0]=m_strDataPath+m_strCode+m_strDate
	//m_strbtnBmpFileName[1]=m_strDataPath+m_strCode
	//m_strBmpFileName = ((CBalanceSysApp*)AfxGetApp())->m_strDataPath + "\\" + m_strCode + "\\" + m_strDate+"\n";
	TCHAR szBuf[MAX_PATH];
	CString m_strSystemPath,m_strbtnBmpFileName,m_strBmpFileName;
	ZeroMemory(szBuf,MAX_PATH);
	if( GetCurrentDirectory(MAX_PATH,szBuf) > 0 )
	{
		m_strSystemPath.Format("%s",szBuf);      //ϵͳִ���ļ�·��
	}
	//file.Open((m_strSystemPath+"\\"+"Datapath.ini"),CFile::modeRead);
	CFile cfile;
	//�����ļ�
	
	cfile.Open((m_strSystemPath+"\\"+"Datapath.ini"),CFile::modeCreate|CFile::modeWrite);
	m_strbtnBmpFileName.Format("%s\n",m_strSystemPath);
	cfile.Write(m_strbtnBmpFileName,m_strbtnBmpFileName.GetLength());
	m_strBmpFileName=m_strSystemPath.Left(m_strSystemPath.ReverseFind('/\\'));
	cfile.Write(m_strBmpFileName,m_strBmpFileName.GetLength());
	cfile.Close();							

	CString strFileName = _T("");

	CFileDialog   FileDlg( TRUE,NULL,"�����ļ�",NULL,"�����ļ�(*.rep)|*.rep",NULL);   
	
	if( FileDlg.DoModal() == IDOK)
	{
		strFileName = FileDlg.GetPathName( );
		ReadReportFile( strFileName);
	}
	MessageBox(strFileName);
	return;
}


void CReportTeDlg::OnBtnPrintReport()
{

	CBookmark0 bookmark;
	CRange range;
	CApplication wordApp; 
	
	CString strTem0,strTem1,m_strSystemPath;

	TCHAR szBuf[MAX_PATH];
  
	
	ZeroMemory(szBuf,MAX_PATH);

	if( GetCurrentDirectory(MAX_PATH,szBuf) > 0 )
	{
		m_strSystemPath.Format("%s",szBuf);      //ϵͳִ���ļ�·��
	}
	AfxMessageBox(m_strSystemPath+"\\"+"Template.docx");
	COleVariant dot(_T(m_strSystemPath+"\\"+"Template.docx"));

	int LineCount=0;
	if ( !wordApp.CreateDispatch(_T("Word.Application")) ) // ʵ����wordApp�������г�ʼ��
	{
		AfxMessageBox(_T("����û�а�װword��Ʒ��"));
		return;
	}
	COleVariant	covZero((short)0),covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR), covDocxType((short)0);
	// wordApp
	wordApp.put_Visible(TRUE);
	CString wordVersion = wordApp.get_Version();
	CDocuments docxs = wordApp.get_Documents();
	CDocument0 docx = docxs.Add(dot, covOptional, covOptional, covOptional);
	CBookmarks  bookmarks = docx.get_Bookmarks();

	CStdioFile file;
	file.Open("21-40-7.rep",CFile::modeRead);
	CString szLine = "";
    CString ambstr = "";
	size_t pos;
	//CFile cfile;
	//�����ļ�
	//cfile.Open("6.txt",CFile::modeCreate|CFile::modeWrite);
	//���ж�ȡ�ļ�����д�뱨��
	while( file.ReadString( szLine ))
	{   
		
		//strTem0.Format("l%d",1);
		//���ģ���ĵ��ı�ǩ���ñ�ǩ������д���rep�ļ�����һ�µģ��������ܱ�֤������д����ͳһ�ļ�¼����
		if (""!=szLine)
		{
			 strTem0=szLine.Left(szLine.Find(":"));
			// MessageBox(strTem0);
		//���ݱ�ǩ������ģ���ĵ��ж�λ����Ҫ�����λ��
	       if(bookmark = bookmarks.Item(&_variant_t(_T(strTem0))))
			{
			//MessageBox(strTem0);
			range = bookmark.get_Range();
			////��������д��rep �ļ�ʱʹ�õĸ�ʽ�ǡ���������12334��������pos�����Ҫ���ҵ�����Ҫ�ó�������
			pos = szLine.GetLength()-szLine.Find(":")-1;  

			ambstr = szLine.Right(pos); 
			//MessageBox(ambstr);
			////cfile.Write(szLine,strlen(szLine));
			////��ֵд���ĵ���ǩ��
			range.put_Text(ambstr);
		    }
			//else
			//{
			//}
			
		}
		else if(szLine="")
		{
          continue;
		}
		
		
		
	}
	file.Close();
	CString strSavePath = _T("H:\\Template1.docx");
	//strSavePath += _T("\\Template1.docx");
	docx.SaveAs(COleVariant(strSavePath), covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);

	//// �˳�wordӦ��
	docx.Close(covFalse, covOptional, covOptional);
	wordApp.Quit(covOptional, covOptional, covOptional);
	range.ReleaseDispatch();
	bookmarks.ReleaseDispatch();
	wordApp.ReleaseDispatch();
	bookmark.ReleaseDispatch();
    docxs.ReleaseDispatch();
   
	AfxMessageBox(_T("Template1.docx���ɳɹ���"));

}


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CReportTeDlg::OnOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CReportTeDlg::OnDtnDatetimechangeDatetimepicker01(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData( true );
	m_strSelectDate.Format("%4d-%2d-%2d",m_TimeValue.GetYear(),m_TimeValue.GetMonth(),m_TimeValue.GetDay( )) ;
	UpdateData(false);
	*pResult = 0;
}
