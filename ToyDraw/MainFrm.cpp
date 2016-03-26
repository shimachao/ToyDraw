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

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "ToyDraw.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_COMMAND(ID_SELECT_ELEMENT, &CMainFrame::OnSelectElement)
	ON_UPDATE_COMMAND_UI(ID_SELECT_ELEMENT, &CMainFrame::OnUpdateSelectElement)
	ON_COMMAND(ID_SELECT, &CMainFrame::OnSelect)
	ON_COMMAND(ID_SELECT, &CMainFrame::OnSelect)
	ON_COMMAND(ID_SELECT_ELEMENT, &CMainFrame::OnSelectElement)
	ON_COMMAND(ID_SELECT_SQUARE, &CMainFrame::OnSelectSquare)
	ON_COMMAND(ID_SELECT_ALL, &CMainFrame::OnSelectAll)
	ON_UPDATE_COMMAND_UI(ID_SELECT_ELEMENT, &CMainFrame::OnUpdateSelectElement)
	ON_UPDATE_COMMAND_UI(ID_SELECT_SQUARE, &CMainFrame::OnUpdateSelectSquare)
	ON_UPDATE_COMMAND_UI(ID_SELECT_ALL, &CMainFrame::OnUpdateSelectAll)
	ON_UPDATE_COMMAND_UI(ID_SELECT, &CMainFrame::OnUpdateSelect)
	ON_COMMAND(ID_ELEMENT_TYPE, &CMainFrame::OnElementType)
	ON_COMMAND(ID_LINE_TYPE, &CMainFrame::OnLineType)
	ON_COMMAND(ID_LINE_WIDTH, &CMainFrame::OnLineWidth)
	ON_COMMAND(ID_COLOR_ONE, &CMainFrame::OnColorOne)
	ON_COMMAND(ID_COLOR_TWO, &CMainFrame::OnColorTwo)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
	: m_SelectIndex(0)
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0); 
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// �������ڻ��������û�����Ԫ�ص��Ӿ�������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
	
	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	else
	{
		m_wndStatusBar.SetInformation(L"test");
	}
	
	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������


void CMainFrame::OnMoving(UINT fwSide, LPRECT pRect)
{
	CFrameWndEx::OnMoving(fwSide, pRect);

	GetActiveView()->PostMessage(WM_MOVE);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);
	CView *pView = GetActiveView();
	if (pView!=NULL && pView->m_hWnd != NULL)
	{
		pView->PostMessage(WM_MOVE);
	}
}


void CMainFrame::OnSelect()
{
	GetActiveView()->SendMessage(WM_MAIN_STATUS_SELECT);
}


void CMainFrame::OnSelectElement()
{
	//TRACE0("CMainFrame::OnSelectElement()\n");
	GetActiveView()->SendMessage(WM_SELECT,1);
	m_SelectIndex = 1;
	CMFCRibbonButton* pSelectButton = 
		DYNAMIC_DOWNCAST(CMFCRibbonButton,m_wndRibbonBar.FindByID(ID_SELECT));
	pSelectButton->SetImageIndex(1,TRUE);
}


void CMainFrame::OnSelectSquare()
{
	//TRACE0("CMainFrame::OnSelectSquare()\n");
	GetActiveView()->SendMessage(WM_SELECT,2);
	m_SelectIndex = 2;
	CMFCRibbonButton* pSelectButton = 
		DYNAMIC_DOWNCAST(CMFCRibbonButton,m_wndRibbonBar.FindByID(ID_SELECT));
	pSelectButton->SetImageIndex(5,TRUE);
}


void CMainFrame::OnSelectAll()
{
	//TRACE0("CMainFrame::OnSelectAll()\n");
	GetActiveView()->SendMessage(WM_SELECT,3);
	m_SelectIndex = 3;
	CMFCRibbonButton* pSelectButton = 
		DYNAMIC_DOWNCAST(CMFCRibbonButton,m_wndRibbonBar.FindByID(ID_SELECT));
	pSelectButton->SetImageIndex(4,TRUE);
}


void CMainFrame::OnUpdateSelect(CCmdUI *pCmdUI)
{
	//TRACE0("CMainFrame::OnUpdateSelect(CCmdUI *pCmdUI)\n");
	/*CMFCRibbonButton* pSelectButton = 
	DYNAMIC_DOWNCAST(CMFCRibbonButton,m_wndRibbonBar.FindByID(ID_SELECT));
	if (m_SelectIndex == 1)
	{
	pSelectButton->SetImageIndex(1,TRUE);
	}
	else if (m_SelectIndex == 2)
	{
	pSelectButton->SetImageIndex(4,TRUE);
	}
	else if (m_SelectIndex == 3)
	{
	pSelectButton->SetImageIndex(5,TRUE);
	}*/
}


void CMainFrame::OnUpdateSelectElement(CCmdUI *pCmdUI)
{
	//TRACE0("CMainFrame::OnUpdateSelectElement(CCmdUI *pCmdUI)\n");
	pCmdUI->SetCheck(m_SelectIndex == 1);
}


void CMainFrame::OnUpdateSelectSquare(CCmdUI *pCmdUI)
{
	//TRACE0("CMainFrame::OnUpdateSelectSquare(CCmdUI *pCmdUI)\n");
	pCmdUI->SetCheck(m_SelectIndex == 2);
}


void CMainFrame::OnUpdateSelectAll(CCmdUI *pCmdUI)
{
	//TRACE0("CMainFrame::OnUpdateSelectAll(CCmdUI *pCmdUI)\n");
	pCmdUI->SetCheck(m_SelectIndex == 3);
}


void CMainFrame::OnElementType()
{
	// TODO: �ڴ���������������
	CMFCRibbonGallery* pGallery = (CMFCRibbonGallery*)m_wndRibbonBar.FindByID(ID_ELEMENT_TYPE);
	int index = pGallery->GetSelectedItem();
	GetActiveView()->SendMessage(WM_GRAPH,index);
}


void CMainFrame::OnLineType()
{
	CMFCRibbonGallery* pGallery = (CMFCRibbonGallery*)m_wndRibbonBar.FindByID(ID_LINE_TYPE);
	int index = pGallery->GetSelectedItem();
	GetActiveView()->SendMessage(WM_LINETYPE,index);
}


void CMainFrame::OnLineWidth()
{
	CMFCRibbonGallery* pGallery = (CMFCRibbonGallery*)m_wndRibbonBar.FindByID(ID_LINE_WIDTH);
	int index = pGallery->GetSelectedItem();
	GetActiveView()->SendMessage(WM_LINE_WIDTH,index);
}


void CMainFrame::OnColorOne()
{
	CMFCRibbonColorButton* pColorOne = (CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_COLOR_ONE);
	COLORREF colorref = pColorOne->GetColor();
	GetActiveView()->SendMessage(WM_COLOR_ONE,colorref);
}


void CMainFrame::OnColorTwo()
{
	CMFCRibbonColorButton* pColorOne = (CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_COLOR_TWO);
	COLORREF colorref = pColorOne->GetColor();
	GetActiveView()->SendMessage(WM_COLOR_TWO,colorref);
}

