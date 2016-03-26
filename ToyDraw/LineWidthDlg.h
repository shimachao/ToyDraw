#pragma once


// CLineWidthDlg �Ի���

class CLineWidthDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLineWidthDlg)

public:
	CLineWidthDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLineWidthDlg();

// �Ի�������
	enum { IDD = IDD_LINE_WIDTH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_LineWidth;
	afx_msg void OnEnChangeLineWidth();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
