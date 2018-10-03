
// mchartDlg.h : ͷ�ļ�
//

#pragma once

#import <msdatsrc.tlb> no_namespace  
#import <mschrt20.ocx> no_namespace 

#include "CDMSChart.h"
#include "CVcPlot.h"  
#include "CVcAxis.h"  
#include "CVcValueScale.h"  
#include "CVcSeriesCollection.h"  
#include "CVcSeries.h"  
#include "CVcPen.h"  
#include "CVcCategoryScale.h"  
#include "CVcColor.h"  
#include "CVcDataGrid.h"  
#include "CVcBackdrop.h"  
#include "CVcFill.h"  
#include "CVcBrush.h"  
#include "CVcDataPoints.h"  
#include "CVcDataPoint.h"  
#include "CVcDataPointLabel.h"  
#include "CVcAxisTitle.h" 
#include "mschart1.h"
#include "CVcTitle.h"
#include "CVcFont.h"
#include "CVcLegend.h"
#include "CVcMarker.h"
#include "CVcLabels.h"
#include "CVcLabel.h"
#include "CVcSeriesMarker.h"


// CmchartDlg �Ի���
class CmchartDlg : public CDialogEx
{
// ����
public:
	CmchartDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MCHART_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CMschart1 m_chart;

	CArray<double,double> m_arrary;


	void showData();


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMschart1 m_chartt;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_EVENTSINK_MAP()
	void OLEStartDragMschart1(LPDISPATCH* Data, long* AllowedEffects);
	void MouseMoveMschart1(short Button, short Shift, long X, long Y);
};
