// LineWidthDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ToyDraw.h"
#include "LineWidthDlg.h"
#include "afxdialogex.h"


// CLineWidthDlg 对话框

IMPLEMENT_DYNAMIC(CLineWidthDlg, CDialogEx)

CLineWidthDlg::CLineWidthDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLineWidthDlg::IDD, pParent)
	, m_LineWidth(1)
{

}

CLineWidthDlg::~CLineWidthDlg()
{
}

void CLineWidthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLineWidthDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLineWidthDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_LINE_WIDTH, &CLineWidthDlg::OnEnChangeLineWidth)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLineWidthDlg 消息处理程序


void CLineWidthDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LineWidth = GetDlgItemInt(IDC_LINE_WIDTH);
	CDialogEx::OnOK();
}


void CLineWidthDlg::OnEnChangeLineWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int n = GetDlgItemInt(IDC_LINE_WIDTH);
	if (n > 19)
	{
		MessageBox(L"输入的数值过大");
		m_LineWidth = 1;
		return;
	}
	m_LineWidth = n;
	Invalidate();
}


void CLineWidthDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetDlgItem(IDC_POS_TAG)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	CPen newPen;
	newPen.CreatePen(PS_SOLID,m_LineWidth,RGB(0,0,0));
	CPen *pOldPen = dc.SelectObject(&newPen);
	dc.MoveTo(rect.left,rect.top);
	dc.LineTo(rect.left+120,rect.top);

	dc.SelectObject(pOldPen);
	
}


BOOL CLineWidthDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemInt(IDC_LINE_WIDTH,1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
