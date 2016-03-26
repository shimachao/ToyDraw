// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// ToyDrawView.h : CToyDrawView 类的接口
//

#pragma once
#include "InteractDlg.h"
#include "ToySG.h"
class CToyDrawView : public CScrollView
{
protected: // 仅从序列化创建
	CToyDrawView();
	DECLARE_DYNCREATE(CToyDrawView)

// 特性
public:
	CToyDrawDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CToyDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
public:
	afx_msg void OnMove(int x, int y);
private:
	//三种状态：选择、绘图、擦除ing
	enum MainStatus{MAIN_STATUS_SELECT,MAIN_STATUS_SELECTED,MAIN_STATUS_DRAW,MAIN_STATUS_ERASE};
	MainStatus	m_MainStatus;

	//何种选择方式
	enum SelectType{SELECT_ELEMENT,SELECT_SQURE,SELECT_ALL};
	SelectType	m_SelectType;

	//绘图状态的子状态：是否正在绘制一个图形
	bool m_IsDrawingAGraphic;

	//当前要绘制的图形：直线、贝塞尔曲线、矩形、椭圆、多边形
	enum Graph{LINE,BEZIER,RECTANGLE,ELLIPSE,POLYGON};
	Graph	m_Graph;

	//当前选择的线型、线宽、颜色都由画笔表示
	Pen			m_Pen;
	CPen		m_CPen;
	COLORREF	m_CurrentColor1;//当前颜色一
	COLORREF	m_CurrentColor2;//当前颜色二
	POINT		m_OriginPoint;	//绘图的起始点
	POINT		m_TemOriginPoint;	//用户交互效果的绘图的起始点
	POINT		m_PrePoint;
	POINT		m_TemPrePoint;//用于交互效果

	//为绘制多边形准备的私有变量
	int		m_EndNum;
	POINT	m_points[20];
	POINT	m_Tempoints[20];
	//为绘制贝塞尔曲线准备的私有变量
	int		m_BezierCount;
	POINT	m_first_end;
	POINT	m_second_end;
	POINT	m_first_control;
	POINT	m_second_control;

	//移动图形使用的私有变量
	POINT	m_PrePointForMove;
	//滚动条位置记录
	UINT	m_hPos;
	UINT	m_vPos;
	//视图的放大倍数
	REAL	m_Sf;
	BOOL	m_IsGrid;//是否显示网格
	CSize	m_ViewSize;//画布大小
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
//	afx_msg LRESULT OnSelect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGraph(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLinetype(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLineWidth(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorOne(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorTwo(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnMainStatusSelect(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	afx_msg void OnZoom();
	afx_msg void OnShrink();
	afx_msg void OnOriginalSize();
	afx_msg void OnLinewidthMore();
	afx_msg void OnCheckGrid();
	afx_msg void OnUpdateCheckGrid(CCmdUI *pCmdUI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnViewResize();
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDelete();
};

#ifndef _DEBUG  // ToyDrawView.cpp 中的调试版本
inline CToyDrawDoc* CToyDrawView::GetDocument() const
   { return reinterpret_cast<CToyDrawDoc*>(m_pDocument); }
#endif

