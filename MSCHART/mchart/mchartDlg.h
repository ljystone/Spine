
// mchartDlg.h : 头文件
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


// CmchartDlg 对话框
class CmchartDlg : public CDialogEx
{
// 构造
public:
	CmchartDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MCHART_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CMschart1 m_chart;

	CArray<double,double> m_arrary;


	void showData();


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
