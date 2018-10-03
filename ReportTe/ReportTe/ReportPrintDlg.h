
// ReportTeDlg.h : header file
//

#pragma once


// CReportTeDlg dialog
class CReportTeDlg : public CDialogEx
{
// Construction
public:
	CString         m_strBmpFilePath01; //第一个图片文件名称
	CString         m_strBmpFilePath02; //第二个图片文件名称
	CString         m_strBmpFilePath03; //第三个图片文件名称
	CString         m_strBmpFilePath04; //第四个图片文件名称
	CString         m_strBmpFile01;     //第一个图片文件名称
	CString         m_strBmpFile02;     //第二个图片文件名称
	CString         m_strBmpFile03;     //第三个图片文件名称
	CString         m_strBmpFile04;     //第四个图片文件名称

public:
	CReportTeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REPORTTE_DIALOG };
	CDateTimeCtrl	m_ctrlDateTime;
	CEdit	        m_cReportData;
	CString	        m_strTodayDate;
	CString	        m_strCode;
	CString	        m_strName;
	CString	        m_strGender;
	CString	        m_strAge;
	UINT	        m_uThighLength;
	UINT	        m_uCrusLength;
	CString	        m_strWeight;
	CString	        m_strSide;
	CTime	        m_TimeValue;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnGraph1();
	afx_msg void OnBtnGraph2();
	afx_msg void OnBtnGraph3();
	afx_msg void OnBtnGraph4();
	afx_msg void OnBtnHistogram();
	afx_msg void OnBtnOpenReport();
	afx_msg void OnBtnPrintReport();
	afx_msg void OnOk();
	afx_msg void OnDtnDatetimechangeDatetimepicker01(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CString m_strSelectDate;
	void ReadReportFile(CString strFileName);
	void ReadReportData( );
};
