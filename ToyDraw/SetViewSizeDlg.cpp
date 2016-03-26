// SetViewSizeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ToyDraw.h"
#include "SetViewSizeDlg.h"
#include "afxdialogex.h"


// CSetViewSizeDlg 对话框

IMPLEMENT_DYNAMIC(CSetViewSizeDlg, CDialogEx)

CSetViewSizeDlg::CSetViewSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetViewSizeDlg::IDD, pParent)
	, m_cx(0)
	, m_cy(0)
{

}

CSetViewSizeDlg::~CSetViewSizeDlg()
{
}

void CSetViewSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetViewSizeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetViewSizeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetViewSizeDlg 消息处理程序


BOOL CSetViewSizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemInt(IDC_CX,0);
	SetDlgItemInt(IDC_CY,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetViewSizeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cx = GetDlgItemInt(IDC_CX);
	m_cy = GetDlgItemInt(IDC_CY);
	CDialogEx::OnOK();
}
