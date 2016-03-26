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

// ToyDrawView.cpp : CToyDrawView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ToyDraw.h"
#endif

#include "ToyDrawDoc.h"
#include "ToyDrawView.h"
#include "LineWidthDlg.h"
#include "SetViewSizeDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CToyDrawView

IMPLEMENT_DYNCREATE(CToyDrawView, CScrollView)

BEGIN_MESSAGE_MAP(CToyDrawView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//ON_MESSAGE(WM_SELECT, &CToyDrawView::OnSelect)
	ON_MESSAGE(WM_GRAPH, &CToyDrawView::OnGraph)
	ON_MESSAGE(WM_LINETYPE, &CToyDrawView::OnLinetype)
	ON_MESSAGE(WM_LINE_WIDTH, &CToyDrawView::OnLineWidth)
	ON_MESSAGE(WM_COLOR_ONE, &CToyDrawView::OnColorOne)
	ON_MESSAGE(WM_COLOR_TWO, &CToyDrawView::OnColorTwo)
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(WM_MAIN_STATUS_SELECT, &CToyDrawView::OnMainStatusSelect)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ZOOM, &CToyDrawView::OnZoom)
	ON_COMMAND(ID_SHRINK, &CToyDrawView::OnShrink)
	ON_COMMAND(ID_ORIGINAL_SIZE, &CToyDrawView::OnOriginalSize)
	ON_COMMAND(ID_LINEWIDTH_MORE, &CToyDrawView::OnLinewidthMore)
	ON_COMMAND(ID_CHECK_GRID, &CToyDrawView::OnCheckGrid)
	ON_UPDATE_COMMAND_UI(ID_CHECK_GRID, &CToyDrawView::OnUpdateCheckGrid)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_VIEW_RESIZE, &CToyDrawView::OnViewResize)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_DELETE, &CToyDrawView::OnDelete)
END_MESSAGE_MAP()

// CToyDrawView ����/����

CToyDrawView::CToyDrawView()
	:m_CurrentColor1(0),m_CurrentColor2(0xFFFFFF),m_Pen(Color(0,0,0)),
	m_MainStatus(MAIN_STATUS_DRAW),m_IsDrawingAGraphic(false),m_Graph(LINE),m_EndNum(0),m_BezierCount(0),
	m_hPos(0),m_vPos(0),m_Sf(1.0),m_IsGrid(FALSE)
{
	m_Pen.SetDashStyle((DashStyle)0);
	m_CPen.CreatePen(0,1,0xFFFFFF);
}

CToyDrawView::~CToyDrawView()
{
}

// CToyDrawView ����

void CToyDrawView::OnDraw(CDC* pDC)
{
	CToyDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//��û�����С
	SIZE viewSize = GetDocument()->GetCanvasSize();
	viewSize.cx *= m_Sf;
	viewSize.cy *= m_Sf;
	POINT org={0,0};
	CRect rect(org,viewSize);
	//��ù�����λ��
	CPoint pos(0,0);
	pos = GetScrollPosition();
	pos.x *= m_Sf;
	pos.x *= m_Sf;
	rect.OffsetRect(pos);
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);

	CBitmap memBmp;
	CRect clientRect;
	GetClientRect(&clientRect);
	memBmp.CreateCompatibleBitmap(pDC,clientRect.Width(),clientRect.Height());
	CBitmap* pOldBmp = memDC.SelectObject(&memBmp);
	//����ջ���
	memDC.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	Graphics* pg = Graphics::FromHDC(memDC.GetSafeHdc());
	//��������
	if (m_IsGrid)
	{//���m_IsGrid��Ҫ��������
		Pen pen(Color(200,200,200),1);
		int width = rect.Width();
		int height = rect.Height();
		int i,j;
		for (i = 0; i < width; i+=50)
		{
			pg->DrawLine(&pen,i,0,i,height);
		}
		for (j = 0; j < height; j+=50)
		{
			pg->DrawLine(&pen,0,j,width,j);
		}
	}
	//���ù⻬�̶�
	pg->SetSmoothingMode(SmoothingModeAntiAlias);
	//ƽ������ԭ��
	pg->TranslateTransform(-pos.x*m_Sf,-pos.y*m_Sf);
	//�����ڴ��ͼ�ķŴ���
	pg->ScaleTransform(m_Sf,m_Sf);
	//�ڴ��ͼ
	pDoc->GetGraphList()->Draw(pg);
	//���ƻ�����С����
	/*Pen pen(Color(255,0,0),2);
	pen.SetDashStyle(DashStyleDot);
	int width = viewSize.cx;
	int height = viewSize.cy;
	pg->DrawRectangle(&pen,0,0,width,height);*/

	//������������Ե�Ŀͻ������
	memDC.FillSolidRect(rect.Width(),0,clientRect.Width(),clientRect.Height(),RGB(212,221,235));
	memDC.FillSolidRect(0,rect.Height(),rect.Width(),clientRect.Height(),RGB(212,221,235));
	//һ���Խ��ڴ��л��ƺõ�ͼ���Ƶ���ͼdc��
	pDC->BitBlt(0,0,clientRect.Width(),clientRect.Height(),&memDC,0,0,SRCCOPY);

	delete pg;
	memDC.SelectObject(pOldBmp);
	memBmp.DeleteObject();
	memDC.DeleteDC();
}


void CToyDrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CToyDrawView ���

#ifdef _DEBUG
void CToyDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CToyDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToyDrawDoc* CToyDrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToyDrawDoc)));
	return (CToyDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CToyDrawView ��Ϣ�������


void CToyDrawView::OnMove(int x, int y)
{
	CView::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
	RECT rect;
	GetWindowRect(&rect);

	//m_InteractDlg.MoveWindow(&rect);
}


void CToyDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//TRACE("OnLButtonDown:%d %d\n",point.x,point.y);
	CPoint tempoint(point);
	CPoint scroPos = GetScrollPosition();
	
	point.Offset(scroPos);
	tempoint.Offset(scroPos);
	point.x /= m_Sf;
	point.y /= m_Sf;
	//TRACE("OnLButtonDown:%d %d\n",point.x,point.y);
	if (m_MainStatus == MAIN_STATUS_DRAW)
	{
		SetCapture();
		RECT rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);
		ClipCursor(&rect);

		m_OriginPoint = point;
		m_TemOriginPoint = tempoint;
		m_PrePoint = point;
		m_TemPrePoint = tempoint;
		m_IsDrawingAGraphic = true;
		if (POLYGON == m_Graph )
		{
			m_points[m_EndNum] = point;
			m_Tempoints[m_EndNum] = tempoint;
			if (m_EndNum < 20)
			{
				m_EndNum++;
			}
			else
			{
				MessageBox(L"����εı߲��ܳ���20");
			}
			TRACE("m_EndNum == %d\n",m_EndNum);
		}
		else if (BEZIER == m_Graph)
		{
			Graphics *pGraphics = Graphics::FromHWND(m_hWnd);
			Pen whitPen(Color(255,255,255),m_Pen.GetWidth());
			CGraph *pGraph = NULL;
			switch(m_BezierCount)
			{
			case 0:
				m_first_end = point;
				m_BezierCount++;
				break;

			case 1:
				m_second_end = point;
				m_BezierCount++;
				break;

			case 2:
				m_first_control = point;
				m_BezierCount++;

				pGraphics->TranslateTransform(-scroPos.x,-scroPos.y);
				pGraphics->ScaleTransform(m_Sf,m_Sf);
				pGraphics->DrawLine(&whitPen,m_first_end.x,m_first_end.y,m_second_end.x,m_second_end.y);
				pGraphics->DrawBezier(&m_Pen,m_first_end.x,m_first_end.y,m_first_control.x,m_first_control.y,
					m_first_control.x,m_first_control.y,m_second_end.x,m_second_end.y);

				break;

			case 3:
				m_second_control = point;
				m_BezierCount++;
				
				//���������߻��ƽ�����������ߵ�doc��״̬����
				pGraph = new ToySG::CBezierCurve(m_first_end,m_second_end,m_first_control,m_second_control);
				pGraph->SetLineType(m_Pen.GetDashStyle());
				pGraph->SetLineWidth(m_Pen.GetWidth());
				pGraph->SetLineColor(m_CurrentColor1);
				GetDocument()->AddGraph(pGraph);
				m_BezierCount = 0;
				ReleaseCapture();
				ClipCursor(NULL);
				break;

			default:
				TRACE("m_BezierCount�Ѿ�>=4,m_BezierCount = %d\n",m_BezierCount);
				break;
			}
		}
	}
	else if (m_MainStatus == MAIN_STATUS_SELECT || m_MainStatus == MAIN_STATUS_SELECTED)
	{
		if (GetDocument()->GetGraphList()->IsHit(point))
		{//ѡ����һ��ͼ��
			m_MainStatus = MAIN_STATUS_SELECTED;
			m_PrePointForMove = point;
			TRACE("m_MainStatus = MAIN_STATUS_SELECTED:213\n");
		}
		else
		{
			m_MainStatus = MAIN_STATUS_SELECT;
		}
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CToyDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
//	TRACE("OnLButtonUp:%d %d\n",point.x,point.y);
	CPoint scroPos = GetScrollPosition();
	
	point.Offset(scroPos);
	point.x /= m_Sf;
	point.y /= m_Sf;
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (MAIN_STATUS_DRAW == m_MainStatus && true == m_IsDrawingAGraphic)
	{
		CGraph *pGraph = NULL;

		switch(m_Graph)
		{
		case LINE:
			pGraph = new ToySG::CLine(m_OriginPoint,point);
			break;

			/*case BEZIER:
			TRACE0("TODO Add bzaier");
			break;*/

		case RECTANGLE:
			pGraph = new ToySG::CRectangle(m_OriginPoint,point);
			break;

		case ELLIPSE:
			pGraph = new ToySG::CEllipse(m_OriginPoint,point);
			break;
		}
		if (pGraph != NULL)
		{
			pGraph->SetLineType(m_Pen.GetDashStyle());
			pGraph->SetLineWidth(m_Pen.GetWidth());
			pGraph->SetLineColor(m_CurrentColor1);
			GetDocument()->AddGraph(pGraph);

			m_IsDrawingAGraphic = false;

			ReleaseCapture();
			ClipCursor(NULL);
		}
	}
	CView::OnLButtonUp(nFlags, point);
}


void CToyDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	//TRACE("OnMouseMove:%d %d\n",point.x,point.y);
	
	if ((m_MainStatus == MAIN_STATUS_DRAW) && (m_IsDrawingAGraphic == true))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		if (m_MainStatus != MAIN_STATUS_DRAW)
		{
			MessageBox(L"m_MainStatus != MAIN_STATUS_DRAWȥ������draw");
		}
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&point);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOTXORPEN);

		CPen newPen,*pOldPen;
		newPen.CreatePen(m_Pen.GetDashStyle(),m_Pen.GetWidth(),m_CurrentColor1);
		pOldPen = dc.SelectObject(&newPen);

		//dc.ScaleViewportExt();
		switch(m_Graph)
		{
		case LINE:
			dc.MoveTo(m_TemOriginPoint);
			dc.LineTo(m_TemPrePoint);

			dc.MoveTo(m_TemOriginPoint);
			dc.LineTo(point);
			break;

		case BEZIER:
			if (m_BezierCount == 1)
			{
				dc.MoveTo(m_TemOriginPoint);
				dc.LineTo(m_TemPrePoint);

				dc.MoveTo(m_TemOriginPoint);
				dc.LineTo(point);
			}
			break;

		case RECTANGLE:
			dc.Rectangle(m_TemOriginPoint.x,m_TemOriginPoint.y,m_TemPrePoint.x,m_TemPrePoint.y);
			dc.Rectangle(m_TemOriginPoint.x,m_TemOriginPoint.y,point.x,point.y);
			break;

		case ELLIPSE:
			dc.Ellipse(m_TemOriginPoint.x,m_TemOriginPoint.y,m_TemPrePoint.x,m_TemPrePoint.y);
			dc.Ellipse(m_TemOriginPoint.x,m_TemOriginPoint.y,point.x,point.y);
			break;

		case POLYGON:
			if (m_EndNum > 0)
			{
				dc.MoveTo(m_Tempoints[m_EndNum-1]);
				dc.LineTo(m_TemPrePoint);
				dc.LineTo(m_Tempoints[0]);
				dc.LineTo(point);
				dc.LineTo(m_Tempoints[m_EndNum-1]);
			}
			
			break;
		}
		m_TemPrePoint = point;
		dc.SelectObject(pOldPen);
	}
	else if (m_MainStatus == MAIN_STATUS_SELECT)
	{
	}
	else if (m_MainStatus == MAIN_STATUS_ERASE)
	{
	}
	else if (m_MainStatus == MAIN_STATUS_SELECTED)
	{
		TRACE0("m_MainStatus == MAIN_STATUS_SELECTED\n");
		//�ж��������Ƿ��ڰ���״̬
		if (nFlags & MK_LBUTTON)
		{
			CPoint tempoint(point);
			CPoint scroPos = GetScrollPosition();
			point.Offset(scroPos);
			point.x /= m_Sf;
			point.y /= m_Sf;
			int dx = point.x - m_PrePointForMove.x;
			int dy = point.y - m_PrePointForMove.y;
			//ƽ��ѡ�е�ͼ��
			GetDocument()->MoveSelectedGraph(dx,dy);
			m_PrePointForMove = point;
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}


void CToyDrawView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint scroPos = GetScrollPosition();
	point.x /= m_Sf;
	point.y /= m_Sf;
	point.Offset(scroPos);
	// ������ڻ��ƶ���Σ����ʾ����λ������
	if (m_Graph == POLYGON && MAIN_STATUS_DRAW == m_MainStatus && m_EndNum > 0)
	{
		Point *pPoints = new Point[m_EndNum];
		for(int i = 0; i < m_EndNum; i++)
		{
			pPoints[i].X = m_points[i].x;
			pPoints[i].Y = m_points[i].y;
		}
		CGraph *pGraph = new ToySG::CPolygon(m_EndNum,pPoints);
		pGraph->SetLineType(m_Pen.GetDashStyle());
		pGraph->SetLineWidth(m_Pen.GetWidth());
		pGraph->SetLineColor(m_CurrentColor1);
		GetDocument()->AddGraph(pGraph);
		m_EndNum = 0;

		m_IsDrawingAGraphic = false;
		ReleaseCapture();
		ClipCursor(NULL);
	}

	CView::OnRButtonDown(nFlags, point);
}


void CToyDrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	/*ClientToScreen(&point);
	OnContextMenu(this, point);
	CPoint scroPos = GetScrollPosition();
	point.x /= m_Sf;
	point.y /= m_Sf;
	point.Offset(scroPos);*/
}


//afx_msg LRESULT CToyDrawView::OnSelect(WPARAM wParam, LPARAM lParam)
//{
//	switch(wParam)
//	{
//	case 1:
//		m_SelectType = SELECT_ELEMENT;
//		break;
//
//	case 2:
//		m_SelectType = SELECT_SQURE;
//		break;
//
//	case 3:
//		m_SelectType = SELECT_ALL;
//		break;
//	}
//
//	m_MainStatus = MAIN_STATUS_SELECT;
//	TRACE0("afx_msg LRESULT CToyDrawView::OnSelect(WPARAM wParam, LPARAM lParam)\nm_MainStatus = MAIN_STATUS_SELECT\n");
//	return 0;
//}


afx_msg LRESULT CToyDrawView::OnGraph(WPARAM wParam, LPARAM lParam)
{
	m_Graph =(CToyDrawView::Graph)wParam;
	if (m_Graph == POLYGON)
	{
		m_EndNum = 0;
	}
	else if (BEZIER == m_Graph)
	{
		m_BezierCount = 0;
	}

	m_MainStatus = MAIN_STATUS_DRAW;
	GetDocument()->SelectNoGraph();
	return 0;
}


afx_msg LRESULT CToyDrawView::OnLinetype(WPARAM wParam, LPARAM lParam)
{
	m_Pen.SetDashStyle((DashStyle)wParam);

	if (m_MainStatus == MAIN_STATUS_SELECTED)
	{
		CGraph* pGraph = GetDocument()->GetSelectedGraph();
		if(pGraph != NULL)
		{
			pGraph->SetLineType((DashStyle)wParam);
			Invalidate();
		}	
	}
	
	return 0;
}


afx_msg LRESULT CToyDrawView::OnLineWidth(WPARAM wParam, LPARAM lParam)
{
	m_Pen.SetWidth((REAL)wParam + 1);

	if (m_MainStatus == MAIN_STATUS_SELECTED)
	{
		CGraph* pGraph = GetDocument()->GetSelectedGraph();
		if(pGraph != NULL)
		{
			pGraph->SetLineWidth((REAL)wParam + 1);
			Invalidate();
		}
	}
	return 0;
}


afx_msg LRESULT CToyDrawView::OnColorOne(WPARAM wParam, LPARAM lParam)
{
	m_CurrentColor1 = wParam;
	m_Pen.SetColor(Color(GetRValue(m_CurrentColor1),GetGValue(m_CurrentColor1),
		GetBValue(m_CurrentColor1)));

	if (m_MainStatus == MAIN_STATUS_SELECTED)
	{
		CGraph* pGraph = GetDocument()->GetSelectedGraph();
		if(pGraph != NULL)
		{
			pGraph->SetLineColor(wParam);
			Invalidate();
		}	
	}

	return 0;
}


afx_msg LRESULT CToyDrawView::OnColorTwo(WPARAM wParam, LPARAM lParam)
{
	m_CurrentColor2 = (COLORREF)wParam;
	
	return 0;
}



afx_msg LRESULT CToyDrawView::OnMainStatusSelect(WPARAM wParam, LPARAM lParam)
{
	m_MainStatus = MAIN_STATUS_SELECT;
	TRACE0("OnMainStatusSelect :m_MainStatus = MAIN_STATUS_SELECT:461\n");
	return 0;
}


BOOL CToyDrawView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}


void CToyDrawView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SIZE sizeTotal = GetDocument()->GetCanvasSize();
	sizeTotal.cx += 5*m_Sf;
	sizeTotal.cy += 5*m_Sf;
	//����ӳ��ģʽΪMM_TEXT
	SetScrollSizes(MM_TEXT, sizeTotal);
}


BOOL CToyDrawView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	// do the scroll
	if (!CScrollView::OnScrollBy(sizeScroll, bDoScroll))
		return FALSE;

	// update the position of any in-place active item
	if (bDoScroll)
	{
		//UpdateActiveItem();
		m_hPos = sizeScroll.cx;
		m_vPos = sizeScroll.cy;
		RedrawWindow();
	}
	return TRUE;
}


void CToyDrawView::OnZoom()
{
	// TODO: �ڴ���������������
	if (m_Sf < 3.0f)
	{
		m_Sf += 0.5;

		SIZE sizeTotal = GetDocument()->GetCanvasSize();
		sizeTotal.cx*=m_Sf;
		sizeTotal.cy*=m_Sf;
		sizeTotal.cx += 5*m_Sf;
		sizeTotal.cy +=5*m_Sf;
		SetScrollSizes(MM_TEXT, sizeTotal);

		RedrawWindow();
		TRACE("m_sf == %f\n",m_Sf);
	}
}


void CToyDrawView::OnShrink()
{
	// TODO: �ڴ���������������
	if (m_Sf > 0.5)
	{
		m_Sf -= 0.5;

		SIZE sizeTotal = GetDocument()->GetCanvasSize();
		sizeTotal.cx*=m_Sf;
		sizeTotal.cy*=m_Sf;
		sizeTotal.cx += 5*m_Sf;
		sizeTotal.cy +=5*m_Sf;
		SetScrollSizes(MM_TEXT, sizeTotal);
		RedrawWindow();
		TRACE("m_sf == %f\n",m_Sf);
	}
}


void CToyDrawView::OnOriginalSize()
{
	// TODO: �ڴ���������������
	if (m_Sf != 1.0f)
	{
		m_Sf = 1.0f;
		Invalidate();
		UpdateWindow();
		TRACE("m_sf == %f\n",m_Sf);
	}
}


void CToyDrawView::OnLinewidthMore()
{
	// TODO: �ڴ���������������
	CLineWidthDlg dlg;
	
	if (IDOK == dlg.DoModal())
	{
		m_Pen.SetWidth(dlg.m_LineWidth);

		if (m_MainStatus == MAIN_STATUS_SELECTED)
		{
			CGraph* pGraph = GetDocument()->GetSelectedGraph();
			if(pGraph != NULL)
			{
				pGraph->SetLineWidth(dlg.m_LineWidth);
				Invalidate();
			}
		}//if
	}//if
}


void CToyDrawView::OnCheckGrid()
{
	// TODO: �ڴ���������������
	TRACE("OnCheckGrid()\n");
	m_IsGrid = !m_IsGrid;
	Invalidate();
}


void CToyDrawView::OnUpdateCheckGrid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_IsGrid);
}


BOOL CToyDrawView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//
	if (m_MainStatus == MAIN_STATUS_SELECTED)
	{
		if (zDelta > 0)
		{//���Ϲ���,��ʾ�Ŵ�
			GetDocument()->ScaleGraph(1.1);
		}
		else
		{//���¹�������ʾ��С
			GetDocument()->ScaleGraph(0.9);
		}
	}
	else
	{
		if (zDelta > 0)
		{//���Ϲ���,��ʾ�Ŵ�
			OnZoom();
		}
		else
		{//���¹�������ʾ��С
			OnShrink();
		}
	}
	return TRUE;
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


void CToyDrawView::OnViewResize()
{
	CSetViewSizeDlg dlg;
	if (dlg.DoModal() == IDOK && dlg.m_cx != 0 && dlg.m_cy != 0)
	{
		SIZE s;
		s.cx = dlg.m_cx;
		s.cy = dlg.m_cy;
		GetDocument()->SetCanvasSize(s);

		//s.cx *= m_Sf;
		//s.cy *= m_Sf;
		//s.cx += 5;
		//s.cy += 5;
		////����ӳ��ģʽΪMM_TEXT
		SetScrollSizes(MM_TEXT,s);
		RedrawWindow();
	}
}



void CToyDrawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (VK_DELETE == nChar)
	{
		if (m_MainStatus == MAIN_STATUS_SELECTED)
		{
			GetDocument()->DeleteSelectedGraph();
			m_MainStatus = MAIN_STATUS_SELECT;
		}
	}
	
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CToyDrawView::OnDelete()
{
	if (m_MainStatus == MAIN_STATUS_SELECTED)
	{
		GetDocument()->DeleteSelectedGraph();
		m_MainStatus = MAIN_STATUS_SELECT;
	}
}
