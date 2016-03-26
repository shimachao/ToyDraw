// SetViewSizeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToyDraw.h"
#include "SetViewSizeDlg.h"
#include "afxdialogex.h"


// CSetViewSizeDlg �Ի���

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


// CSetViewSizeDlg ��Ϣ�������


BOOL CSetViewSizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemInt(IDC_CX,0);
	SetDlgItemInt(IDC_CY,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSetViewSizeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cx = GetDlgItemInt(IDC_CX);
	m_cy = GetDlgItemInt(IDC_CY);
	CDialogEx::OnOK();
}
