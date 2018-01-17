#pragma once
#include"Adosql.h"


// RegisterDlg 对话框

class RegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RegisterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRegister();
	// 管理员名
	CString m_edit_AdminName;

	// 管理员密码
	CString m_edit_AdminPwd;
	// 确认密码
	CString m_edit_AdminEndPwd;

	Adosql sql;
};
