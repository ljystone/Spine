#pragma once
#import <msdatsrc.tlb> no_namespace  
#import <mschrt20.ocx> no_namespace 

#include "afxwin.h"
#include "CDMSChart.h"
#include "CVcPlot.h"  
#include "CVcAxis.h"  
#include "CVcCategoryScale.h"
#include "CVcDataPointLabel.h"
#include "CVcSeries.h"  
#include "CVcPen.h"  
#include "CVcSeriesCollection.h"
#include "CVcColor.h"  
#include "CVcDataGrid.h"  
#include "CVcBackdrop.h"  
#include "CVcFill.h"  
#include "CVcBrush.h"  
#include "CVcDataPoints.h"  
#include "CVcDataPoint.h"  
#include "CVcValueScale.h"
#include "CVcAxisTitle.h" 
#include "mschart1.h"
#include "CVcTitle.h"
#include "CVcFont.h"
#include "CVcLegend.h"
#include "CVcMarker.h"
#include "CVcLabels.h"
#include "CVcLabel.h"
#include "CVBDataObject.h"
#include "CVcPlotBase.h"
#include "CVcStatLine.h"
// CReportHistogramDlg dialog

class CReportHistogramDlg : public CDialog
{
	DECLARE_DYNAMIC(CReportHistogramDlg)
	private:
    float m_fMaxValue;

	float m_dwGZMAVGSwing[4];           //��״��ƽ���ڷ�
	float m_dwGZMCEFANGVEL[4];          //��״��෽����
	float m_dwGZMGOGOffset[4];          //ƽ�����Ķ�״��ƫ����
	float m_fLMaxPresKneeJointTor[4];   //��ϥ����������
	float m_fRMaxPresKneeJointTor[4];   //��ϥ����������	
	float m_fLeftPower[4];              //����֫��������
	float m_fRightPower[4];             //����֫��������
	float m_fEditLLimbMaxAcc[4];        //����֫�����ٶȣ���Ϊ����֫�����仯�����ֵ
	float m_fEditRLimbMaxAcc[4];        //����֫�����ٶȣ���Ϊ����֫�����仯�����ֵ

	float m_fLKneeJointMax[4];			//��ϥ���Ƕ�
	float m_fRKneeJointMax[4];			//��ϥ���Ƕ�

	float m_fLTBQSPressureMax[4];			//ͬ����������
	float m_fRTBQSPressureMax[4];			//ͬ���Ҳ������
	float m_fLTBQSPressureMean[4];			//ͬ�����ƽ������
	float m_fRTBQSPressureMean[4];			//ͬ���Ҳ�ƽ������
	float m_fLJTQSPressureMax[4];			//������������
	float m_fRJTQSPressureMax[4];			//�����Ҳ������
	float m_fLJTQSPressureMean[4];			//�������ƽ������
	float m_fRJTQSPressureMean[4];			//�����Ҳ�ƽ������

	CString         m_strHisFilePath01; //��һ��ͼƬ�ļ�����
	CString         m_strHisFilePath02; //�ڶ���ͼƬ�ļ�����
	CString         m_strHisFilePath03; //������ͼƬ�ļ�����
	CString         m_strHisFilePath04; //���ĸ�ͼƬ�ļ�����
	CString         m_strHisFile01;     //��һ��ͼƬ�ļ�����
	CString         m_strHisFile02;     //�ڶ���ͼƬ�ļ�����
	CString         m_strHisFile03;     //������ͼƬ�ļ�����
	CString         m_strHisFile04;     //���ĸ�ͼƬ�ļ�����
    CString         m_strFileDataTime01;
    CString         m_strFileDataTime02;
    CString         m_strFileDataTime03;
    CString         m_strFileDataTime04;
	
	
private:
	void ReadData();
	void ShowChart(); 
	void InitDrawChart(); 
	void InitChart();
	void DrawChart();
	void Clear();

// Construction
public:

    CString m_strBmpFileName;
	//CCopyScreenToBitmap m_ObjectWriteBmp;
	CReportHistogramDlg(CWnd* pParent = NULL);   // standard constructor
	void SizeChange(CWnd *pWnd);


public:
	
	virtual ~CReportHistogramDlg();
	int		m_FlagJtce;
	CButton m_btnShowHistogram;
	
	
// Dialog Data
	enum { IDD = IDD_REPORT_HISTOGRAM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBtnGraph1();
	afx_msg void OnBtnGraph2();
	afx_msg void OnBtnGraph3();
	afx_msg void OnBtnGraph4();
	afx_msg void OnBtnReturn();
	afx_msg void OnBtnSaveBmp();
	afx_msg void OnBtnShow();
	afx_msg void OnRadioDlxcs();
	afx_msg void OnRadioJtce();
	afx_msg void OnRadioJtqsce();
	afx_msg void OnRadioTbqsce();
	afx_msg void OnRadioYdxhis();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	


	



	CMschart1 m_Chart;
	virtual BOOL OnInitDialog();
	CStatic m_ctrlShowWnd;
};
