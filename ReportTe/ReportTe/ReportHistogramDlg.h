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

	float m_dwGZMAVGSwing[4];           //额状面平均摆幅
	float m_dwGZMCEFANGVEL[4];          //额状面侧方摆速
	float m_dwGZMGOGOffset[4];          //平均重心额状面偏移量
	float m_fLMaxPresKneeJointTor[4];   //左膝最大承力力矩
	float m_fRMaxPresKneeJointTor[4];   //右膝最大承力力矩	
	float m_fLeftPower[4];              //左下肢做功功率
	float m_fRightPower[4];             //右下肢做功功率
	float m_fEditLLimbMaxAcc[4];        //左下肢最大加速度，改为左下肢顶力变化率最大值
	float m_fEditRLimbMaxAcc[4];        //右下肢最大加速度，改为右下肢顶力变化率最大值

	float m_fLKneeJointMax[4];			//左膝最大角度
	float m_fRKneeJointMax[4];			//右膝最大角度

	float m_fLTBQSPressureMax[4];			//同步左侧最大顶力
	float m_fRTBQSPressureMax[4];			//同步右侧最大顶力
	float m_fLTBQSPressureMean[4];			//同步左侧平均顶力
	float m_fRTBQSPressureMean[4];			//同步右侧平均顶力
	float m_fLJTQSPressureMax[4];			//交替左侧最大顶力
	float m_fRJTQSPressureMax[4];			//交替右侧最大顶力
	float m_fLJTQSPressureMean[4];			//交替左侧平均顶力
	float m_fRJTQSPressureMean[4];			//交替右侧平均顶力

	CString         m_strHisFilePath01; //第一个图片文件名称
	CString         m_strHisFilePath02; //第二个图片文件名称
	CString         m_strHisFilePath03; //第三个图片文件名称
	CString         m_strHisFilePath04; //第四个图片文件名称
	CString         m_strHisFile01;     //第一个图片文件名称
	CString         m_strHisFile02;     //第二个图片文件名称
	CString         m_strHisFile03;     //第三个图片文件名称
	CString         m_strHisFile04;     //第四个图片文件名称
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
