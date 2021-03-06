
// MonitorSystemClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MonitorSystemClient.h"
#include "MonitorSystemClientDlg.h"
#include "DIALOG1.h"
#include "afxdialogex.h"
#include "Dbctrl.h"
#include "..\MonitorSystemClient\CSecureEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMonitorSystemClientDlg 对话框



CMonitorSystemClientDlg::CMonitorSystemClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MONITORSYSTEMCLIENT_DIALOG, pParent)
	, username(_T(""))	
	, m_serverIp(_T(""))
	, m_serverPort(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMonitorSystemClientDlg::~CMonitorSystemClientDlg()
{
	delete dbctrl;
	delete worksocket;
}

void CMonitorSystemClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_USERNAME, m_uesrcontrol);
	DDX_Text(pDX, IDC_EDIT1, username);	
	DDX_Text(pDX, IDC_EDIT3, m_serverIp);
	DDX_Text(pDX, IDC_EDIT4, m_serverPort);
	DDX_Control(pDX, IDC_EDIT2, safe_password);
}

BEGIN_MESSAGE_MAP(CMonitorSystemClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitorSystemClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMonitorSystemClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMonitorSystemClientDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMonitorSystemClientDlg 消息处理程序

BOOL CMonitorSystemClientDlg::OnInitDialog()
{
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

	//设置字体
	CFont *font1;
	font1 = new CFont();
	font1->CreatePointFont(110, _T("黑体"));
	GetDlgItem(IDC_USERNAME)->SetFont(font1);
	GetDlgItem(IDC_PASSWORD)->SetFont(font1);

	CFont *f1;
	f1 = new CFont();
	f1->CreatePointFont(120, _T("Times New Roman"));
	GetDlgItem(IDC_EDIT1)->SetFont(f1);
	/*GetDlgItem(IDC_EDIT2)->SetFont(f1);*/
	


	CFont *font2;
	font2 = new CFont();
	font2->CreatePointFont(90, _T("宋体"));
	GetDlgItem(IDC_STATIC1)->SetFont(font2);
	GetDlgItem(IDC_STATIC2)->SetFont(font2);
	

	WCHAR ServerIP[MAX_PATH] = { 0 };

	GetPrivateProfileString(_T("ServerInfo"), _T("IP"), _T("127.0.0.1"), ServerIP, MAX_PATH, _T("./Server.ini"));
	m_serverPort= GetPrivateProfileInt(_T("ServerInfo"), _T("Port"), 5002, _T("./Server.ini"));
	//worksocket->Connect(ServerIP, nPort);
	m_serverIp = ServerIP;

	dbctrl = new Dbctrl(this);
	
	UpdateData(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMonitorSystemClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMonitorSystemClientDlg::OnPaint()
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
HCURSOR CMonitorSystemClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CMonitorSystemClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CMonitorSystemClientDlg::OnBnClickedButton1()
{
	CString password;
	safe_password.GetRealText(password);


	// TODO: 在此添加控件通知处理程序代码
	worksocket = new WrkSocket(*dbctrl, _T("db"));
	//WCHAR ServerIP[MAX_PATH] = { 0 };


	//GetPrivateProfileString(_T("ServerInfo"), _T("IP"), _T("127.0.0.1"), ServerIP, MAX_PATH, _T("./Server.ini"));
	//int nPort = GetPrivateProfileInt(_T("ServerInfo"), _T("Port"), 5002, _T("./Server.ini"));
	UpdateData(true);
	
	char szBuf[100];
	_itoa_s(m_serverPort, szBuf, 10);
	CString csStr(szBuf);
	WritePrivateProfileString(_T("ServerInfo"), _T("IP"), m_serverIp, _T("./Server.ini"));
	WritePrivateProfileString(_T("ServerInfo"), _T("Port"), csStr, _T("./Server.ini"));
	if (username.IsEmpty()||password.IsEmpty()) {
		MessageBox(_T("用户名或密码不能为空！"));
		return;
	}
	WritePrivateProfileString(_T("UserInfo"), _T("Name"), username, _T("./Server.ini"));
	worksocket->Connect(m_serverIp, m_serverPort);
	Sleep(100);
		//与服务器端通信
	worksocket->SendUserInfo(username, password);
	

}


void CMonitorSystemClientDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);

}


void CMonitorSystemClientDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDIALOG1 cd;
	cd.DoModal();

}

BOOL CMonitorSystemClientDlg::PreTranslateMessage(MSG* pMsg) {
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedButton1();
			return TRUE;//截获消息
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
