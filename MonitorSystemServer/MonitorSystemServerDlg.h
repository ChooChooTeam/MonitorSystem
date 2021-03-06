
// MonitorSystemServerDlg.h: 头文件
//

#pragma once
#include"Adosql.h"
#include "..\MonitorSystemClient\CSecureEdit.h"

// CMonitorSystemServerDlg 对话框
class CMonitorSystemServerDlg : public CDialog
{
// 构造
public:
	CMonitorSystemServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITORSYSTEMSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();

	Adosql sql;  //数据库对象的全局变量
	// 管理员帐号
	CString AdminName;
	// 管理员密码
	CString AdminPwd;
	CSecureEdit safe_password;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
