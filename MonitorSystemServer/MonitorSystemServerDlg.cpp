
// MonitorSystemServerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "MonitorSystemServerDlg.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Adosql.h"
#include "Register.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Adosql sql;  //数据库对象的全局变量

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMonitorSystemServerDlg 对话框



CMonitorSystemServerDlg::CMonitorSystemServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MONITORSYSTEMSERVER_DIALOG, pParent)
	, AdminName(_T(""))
	, AdminPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorSystemServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, AdminName);
	DDV_MaxChars(pDX, AdminName, 32);
	DDX_Text(pDX, IDC_EDIT1, AdminPwd);
}

BEGIN_MESSAGE_MAP(CMonitorSystemServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMonitorSystemServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitorSystemServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMonitorSystemServerDlg::OnBnClickedButton2)	
END_MESSAGE_MAP()


// CMonitorSystemServerDlg 消息处理程序

BOOL CMonitorSystemServerDlg::OnInitDialog()
{
	sql.OnInitADOConn();

	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMonitorSystemServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMonitorSystemServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMonitorSystemServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMonitorSystemServerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CMonitorSystemServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	
	if (sql.queryAdmin(AdminName, AdminPwd))
	{
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken,&gdiplusStartupInput, NULL);
	
		CMainDlg mlg = new CMainDlg();
		mlg.DoModal();
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}
	else
	{
		MessageBox(_T("帐号或密码错误，请重新输入！"));
	}
	
}


void CMonitorSystemServerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Register rDlg = new Register();
	rDlg.DoModal();
}


