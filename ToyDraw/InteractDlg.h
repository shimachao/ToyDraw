#pragma once


// CInteractDlg �Ի���

class CInteractDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInteractDlg)

public:
	CInteractDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInteractDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_INTERACT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	virtual void PreInitDialog();
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
