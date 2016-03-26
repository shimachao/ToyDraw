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

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "afxtoolbarimages.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelect();
	afx_msg void OnSelectElement();
	afx_msg void OnSelectSquare();
	afx_msg void OnSelectAll();
	afx_msg void OnUpdateSelect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectElement(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectSquare(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectAll(CCmdUI *pCmdUI);
private:
	// 记载了选择按钮的哪个子项处于选择状态
	int m_SelectIndex;
	CMFCToolBarImages m_LineWidthImages;
public:
//	void CreateLineWidthGallery(void);
	afx_msg void OnElementType();
	afx_msg void OnLineType();
	afx_msg void OnLineWidth();
	afx_msg void OnColorOne();
	afx_msg void OnColorTwo();
};


