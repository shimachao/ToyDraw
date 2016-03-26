// InteractDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToyDraw.h"
#include "InteractDlg.h"
#include "afxdialogex.h"


// CInteractDlg �Ի���

IMPLEMENT_DYNAMIC(CInteractDlg, CDialogEx)

CInteractDlg::CInteractDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInteractDlg::IDD, pParent)
{

}

CInteractDlg::~CInteractDlg()
{
}

void CInteractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInteractDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CInteractDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	Graphics graphics(dc.GetSafeHdc());
	Pen pen(Color(255,0,0,0));
	graphics.DrawEllipse(&pen,0,0,200,200);
}


void CInteractDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACE0("CInteractDlg::OnMouseMove-------hahahah!\n");
	CDialogEx::OnMouseMove(nFlags, point);
}


void CInteractDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MessageBox(L"CInteractDlg::OnLButtonDown");
	CDialogEx::OnLButtonDown(nFlags, point);
}


