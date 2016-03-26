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

// ToyDrawDoc.cpp : CToyDrawDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CToyDrawDoc 构造/析构

CToyDrawDoc::CToyDrawDoc()
{
	// TODO: 在此添加一次性构造代码

}

CToyDrawDoc::~CToyDrawDoc()
{
}





// CToyDrawDoc 序列化

void CToyDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		
	}
	else
	{
		// TODO: 在此添加加载代码
		
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CToyDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CToyDrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CToyDrawDoc 诊断

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


// CToyDrawDoc 命令


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
	//todo缩放选中的图形
	m_GraphList.ScaleGraph(f);
	UpdateAllViews(NULL);
}

void CToyDrawDoc::OnScaleBig()
{
	// TODO: 在此添加命令处理程序代码
	m_GraphList.ScaleGraph(1.2);
	UpdateAllViews(NULL);
}


void CToyDrawDoc::OnScaleSmall()
{
	// TODO: 在此添加命令处理程序代码
	m_GraphList.ScaleGraph(0.8);
	UpdateAllViews(NULL);
}


BOOL CToyDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	//	SetTitle(L"新建文档");
	
	return TRUE;
}


BOOL CToyDrawDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	m_GraphList.Load(Unicode2ANSI(lpszPathName));
	
	return TRUE;
}


BOOL CToyDrawDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_GraphList.Save(Unicode2ANSI(lpszPathName));
	return TRUE;
	//return CDocument::OnSaveDocument(lpszPathName);
}


// 设置画布大小
void CToyDrawDoc::SetCanvasSize(SIZE size)
{
	m_GraphList.m_CanvasSize = size;
}

SIZE& CToyDrawDoc::GetCanvasSize()
{
	return m_GraphList.m_CanvasSize;
}
