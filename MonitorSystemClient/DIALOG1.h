#pragma once


// CDIALOG1 对话框

class CDIALOG1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDIALOG1)

public:
	CDIALOG1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDIALOG1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
};
