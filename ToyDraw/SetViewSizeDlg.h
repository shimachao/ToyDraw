#pragma once


// CSetViewSizeDlg �Ի���

class CSetViewSizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetViewSizeDlg)

public:
	CSetViewSizeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetViewSizeDlg();

// �Ի�������
	enum { IDD = IDD_SET_VIEW_SIEE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	int m_cx;
	int m_cy;
};
