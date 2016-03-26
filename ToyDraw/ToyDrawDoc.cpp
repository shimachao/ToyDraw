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

// ToyDrawDoc.cpp : CToyDrawDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ToyDraw.h"
#endif

#include "ToyDrawDoc.h"

#include <propkey.h>

#include "transcoding.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CToyDrawDoc

IMPLEMENT_DYNCREATE(CToyDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CToyDrawDoc, CDocument)
	ON_COMMAND(ID_SCALE_BIG, &CToyDrawDoc::OnScaleBig)
	ON_COMMAND(ID_SCALE_SMALL, &CToyDrawDoc::OnScaleSmall)
END_MESSAGE_MAP()


// CToyDrawDoc ����/����

CToyDrawDoc::CToyDrawDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CToyDrawDoc::~CToyDrawDoc()
{
}





// CToyDrawDoc ���л�

void CToyDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CToyDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CToyDrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CToyDrawDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CToyDrawDoc ���

#ifdef _DEBUG
void CToyDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToyDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CToyDrawDoc ����


void CToyDrawDoc::AddGraph(CGraph* pGraph)
{
	m_GraphList.AddGraph(pGraph);
	SetModifiedFlag();
	UpdateAllViews(NULL);
}


CGraphList* CToyDrawDoc::GetGraphList()
{
	return &m_GraphList;
}


void CToyDrawDoc::MoveSelectedGraph(int dx,int dy)
{
	m_GraphList.MoveSelectGraph(dx,dy);
	UpdateAllViews(NULL);
}


void CToyDrawDoc::SelectNoGraph()
{
	m_GraphList.SelectNo();
	UpdateAllViews(NULL);
}

CGraph* CToyDrawDoc::GetSelectedGraph()
{
	return m_GraphList.GetSelectedGraph();
}

void CToyDrawDoc::DeleteSelectedGraph()
{
	m_GraphList.DeleteSelectedGraph();
	UpdateAllViews(NULL);
}

void CToyDrawDoc::ScaleGraph(float f)
{
	//todo����ѡ�е�ͼ��
	m_GraphList.ScaleGraph(f);
	UpdateAllViews(NULL);
}

void CToyDrawDoc::OnScaleBig()
{
	// TODO: �ڴ���������������
	m_GraphList.ScaleGraph(1.2);
	UpdateAllViews(NULL);
}


void CToyDrawDoc::OnScaleSmall()
{
	// TODO: �ڴ���������������
	m_GraphList.ScaleGraph(0.8);
	UpdateAllViews(NULL);
}


BOOL CToyDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	//	SetTitle(L"�½��ĵ�");
	
	return TRUE;
}


BOOL CToyDrawDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	m_GraphList.Load(Unicode2ANSI(lpszPathName));
	
	return TRUE;
}


BOOL CToyDrawDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_GraphList.Save(Unicode2ANSI(lpszPathName));
	return TRUE;
	//return CDocument::OnSaveDocument(lpszPathName);
}


// ���û�����С
void CToyDrawDoc::SetCanvasSize(SIZE size)
{
	m_GraphList.m_CanvasSize = size;
}

SIZE& CToyDrawDoc::GetCanvasSize()
{
	return m_GraphList.m_CanvasSize;
}
