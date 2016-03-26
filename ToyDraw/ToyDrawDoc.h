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

// ToyDrawDoc.h : CToyDrawDoc ��Ľӿ�
//


#pragma once
#include "afxcoll.h"
#include "ToySG.h"
#include "GraphList.h"
using ToySG::CGraph;
class CToyDrawDoc : public CDocument
{
protected: // �������л�����
	CToyDrawDoc();
	DECLARE_DYNCREATE(CToyDrawDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CToyDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
	CGraphList m_GraphList;
public:
	void AddGraph(CGraph* pGraph);
	CGraphList* GetGraphList();
	void MoveSelectedGraph(int dx,int dy);
	void SelectNoGraph();
	void DeleteSelectedGraph();
	CGraph* GetSelectedGraph();
	void	ScaleGraph(float f);
	afx_msg void OnScaleBig();
	afx_msg void OnScaleSmall();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	// ���û�����С
	void SetCanvasSize(SIZE size);
	SIZE& GetCanvasSize();
};
