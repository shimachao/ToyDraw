// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ToyDrawView.h : CToyDrawView ��Ľӿ�
//

#pragma once
#include "InteractDlg.h"
#include "ToySG.h"
class CToyDrawView : public CScrollView
{
protected: // �������л�����
	CToyDrawView();
	DECLARE_DYNCREATE(CToyDrawView)

// ����
public:
	CToyDrawDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CToyDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
public:
	afx_msg void OnMove(int x, int y);
private:
	//����״̬��ѡ�񡢻�ͼ������ing
	enum MainStatus{MAIN_STATUS_SELECT,MAIN_STATUS_SELECTED,MAIN_STATUS_DRAW,MAIN_STATUS_ERASE};
	MainStatus	m_MainStatus;

	//����ѡ��ʽ
	enum SelectType{SELECT_ELEMENT,SELECT_SQURE,SELECT_ALL};
	SelectType	m_SelectType;

	//��ͼ״̬����״̬���Ƿ����ڻ���һ��ͼ��
	bool m_IsDrawingAGraphic;

	//��ǰҪ���Ƶ�ͼ�Σ�ֱ�ߡ����������ߡ����Ρ���Բ�������
	enum Graph{LINE,BEZIER,RECTANGLE,ELLIPSE,POLYGON};
	Graph	m_Graph;

	//��ǰѡ������͡��߿���ɫ���ɻ��ʱ�ʾ
	Pen			m_Pen;
	CPen		m_CPen;
	COLORREF	m_CurrentColor1;//��ǰ��ɫһ
	COLORREF	m_CurrentColor2;//��ǰ��ɫ��
	POINT		m_OriginPoint;	//��ͼ����ʼ��
	POINT		m_TemOriginPoint;	//�û�����Ч���Ļ�ͼ����ʼ��
	POINT		m_PrePoint;
	POINT		m_TemPrePoint;//���ڽ���Ч��

	//Ϊ���ƶ����׼����˽�б���
	int		m_EndNum;
	POINT	m_points[20];
	POINT	m_Tempoints[20];
	//Ϊ���Ʊ���������׼����˽�б���
	int		m_BezierCount;
	POINT	m_first_end;
	POINT	m_second_end;
	POINT	m_first_control;
	POINT	m_second_control;

	//�ƶ�ͼ��ʹ�õ�˽�б���
	POINT	m_PrePointForMove;
	//������λ�ü�¼
	UINT	m_hPos;
	UINT	m_vPos;
	//��ͼ�ķŴ���
	REAL	m_Sf;
	BOOL	m_IsGrid;//�Ƿ���ʾ����
	CSize	m_ViewSize;//������С
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

#ifndef _DEBUG  // ToyDrawView.cpp �еĵ��԰汾
inline CToyDrawDoc* CToyDrawView::GetDocument() const
   { return reinterpret_cast<CToyDrawDoc*>(m_pDocument); }
#endif

