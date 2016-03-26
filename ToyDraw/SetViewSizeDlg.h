#pragma once


// CSetViewSizeDlg 对话框

class CSetViewSizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetViewSizeDlg)

public:
	CSetViewSizeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetViewSizeDlg();

// 对话框数据
	enum { IDD = IDD_SET_VIEW_SIEE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	int m_cx;
	int m_cy;
};
