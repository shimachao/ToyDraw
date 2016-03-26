// LineWidthDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToyDraw.h"
#include "LineWidthDlg.h"
#include "afxdialogex.h"


// CLineWidthDlg �Ի���

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


// CLineWidthDlg ��Ϣ�������


void CLineWidthDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LineWidth = GetDlgItemInt(IDC_LINE_WIDTH);
	CDialogEx::OnOK();
}


void CLineWidthDlg::OnEnChangeLineWidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int n = GetDlgItemInt(IDC_LINE_WIDTH);
	if (n > 19)
	{
		MessageBox(L"�������ֵ����");
		m_LineWidth = 1;
		return;
	}
	m_LineWidth = n;
	Invalidate();
}


void CLineWidthDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemInt(IDC_LINE_WIDTH,1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
