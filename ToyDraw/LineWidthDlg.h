#pragma once


// CLineWidthDlg 对话框

class CLineWidthDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLineWidthDlg)

public:
	CLineWidthDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLineWidthDlg();

// 对话框数据
	enum { IDD = IDD_LINE_WIDTH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_LineWidth;
	afx_msg void OnEnChangeLineWidth();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
