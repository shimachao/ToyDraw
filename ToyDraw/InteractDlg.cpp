// InteractDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ToyDraw.h"
#include "InteractDlg.h"
#include "afxdialogex.h"


// CInteractDlg 对话框

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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	Graphics graphics(dc.GetSafeHdc());
	Pen pen(Color(255,0,0,0));
	graphics.DrawEllipse(&pen,0,0,200,200);
}


void CInteractDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACE0("CInteractDlg::OnMouseMove-------hahahah!\n");
	CDialogEx::OnMouseMove(nFlags, point);
}


void CInteractDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox(L"CInteractDlg::OnLButtonDown");
	CDialogEx::OnLButtonDown(nFlags, point);
}


