// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}



BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序





BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_list.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	m_list.InsertColumn(1, _T("进程名"), LVCFMT_LEFT, 100);        // 插入第2列的列名  
	m_list.InsertColumn(2, _T("CPU"), LVCFMT_LEFT, 100);        // 插入第3列的列名  
	m_list.InsertColumn(3, _T("内存"), LVCFMT_LEFT, 100);        // 插入第4列的列名 
	CString strName, strAge, strSex;
	for (int i = 0; i <= 7; i++) {
		strName.Format(_T("进程%d"), i);
		strAge.Format(_T("%d"), 20 + i);
		strSex = i % 2 ? _T("10") : _T("20");
		m_list.InsertItem(i, _T(""));                          // 插入行  
		m_list.SetItemText(i, 1, strName);                     // 设置第2列(姓名)  
		m_list.SetItemText(i, 2, strAge);                      // 设置第3列(年龄)  
		m_list.SetItemText(i, 3, strSex);                      // 设置第4列(性别)  
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
