
// MonitorSystemClientDlg.h: 头文件
//

#pragma once
#include "afxwin.h"
#include "CSecureEdit.h"


// CMonitorSystemClientDlg 对话框
class CMonitorSystemClientDlg : public CDialog
{
// 构造
public:
	CMonitorSystemClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMonitorSystemClientDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITORSYSTEMCLIENT_DIALOG };
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
	DECLARE_MESSAGE_MAP();
	BOOL PreTranslateMessage(MSG* pMsg);

public:
	Dbctrl * dbctrl;
	WrkSocket * worksocket;


public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//用户名变量
//	CStatic m_uesrcontrol;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CString username;	
	// //界面上的服务器ip地址
	CString m_serverIp;
	// 界面上服务器端端口
	int m_serverPort;
	CSecureEdit safe_password;
};
