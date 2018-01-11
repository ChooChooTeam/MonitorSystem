// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "MainDlg.h"
#include "afxdialogex.h"
using namespace Gdiplus;

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	
}

void CMainDlg::ShowJPEG(void * pData, int DataSize)
{

	HGLOBAL m_hMem1 = GlobalAlloc(GMEM_MOVEABLE, DataSize);
	LPBYTE lpData1 = (LPBYTE)GlobalLock(m_hMem1);
	memcpy(lpData1, pData, DataSize);
	GlobalUnlock(m_hMem1);
	::CreateStreamOnHGlobal(m_hMem1, TRUE, &m_pStm);

	m_pNewBmp = Bitmap::FromStream(m_pStm);
	CRect rc;
	GetClientRect(rc);
	HDC hDC = pic->GetDC()->m_hDC;
	Graphics *graphics = Graphics::FromHDC(hDC);
	graphics->DrawImage(m_pNewBmp, 1, 1, rc.Width(), rc.Height());
	m_pStm->Release();
	m_pStm = NULL;
	delete graphics;
	GlobalFree(m_hMem1);
	::ReleaseDC(m_hWnd, hDC);
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_LIST4, m_userlist);
}



BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序





BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化进程信息列表
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

	//初始化用户信息列表
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_userlist.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	m_userlist.InsertColumn(1, _T("用户名"), LVCFMT_LEFT, 100);        // 插入第2列的列名  
	
	CString userName;
	for (int i = 0; i <= 7; i++) {
		userName.Format(_T("用户%d"), i);
		m_userlist.InsertItem(i, _T(""));                          // 插入行  
		m_userlist.SetItemText(i, 1, userName);                     // 设置第2列(姓名)  
		
	}

	pic = (CStatic*)GetDlgItem(IDC_STATIC);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
