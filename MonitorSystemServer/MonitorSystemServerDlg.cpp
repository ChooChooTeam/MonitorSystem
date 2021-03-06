
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorSystemServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, AdminName);		
	DDX_Control(pDX, IDC_EDIT1, safe_password);
}

BEGIN_MESSAGE_MAP(CMonitorSystemServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMonitorSystemServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitorSystemServerDlg::OnBnClickedButton1)
	ON_WM_KEYDOWN()
	ON_WM_CTLCOLOR()
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
		//注释该语句：防止重复调用重画函数
		/*CDialog::OnPaint();*/
		
		//添加代码对话框背景贴图
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);    //获取对话框长宽      
		CDC   dcBmp;             //定义并创建一个内存设备环境
		dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);    //载入资源中图片
		BITMAP   m_bitmap;                         //图片变量               
		bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
												  //将位图选入临时内存设备环境
		CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
		//调用函数显示图片StretchBlt显示形状可变
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
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
	
	CString str;
	safe_password.GetRealText(str);
	if (sql.queryAdmin(AdminName, str))
	{
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken,&gdiplusStartupInput, NULL);
	
		CMainDlg mlg = new CMainDlg();
		mlg.DoModal();
		//this->ShowWindow(SW_HIDE);
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}
	else
	{
		MessageBox(_T("帐号或密码错误，请重新输入！"));
	}
	
}

BOOL CMonitorSystemServerDlg::PreTranslateMessage(MSG* pMsg) {
	//检测按键消息
	if (pMsg->message == WM_KEYDOWN)
	{
		//检测是否是enter键
		if (pMsg->wParam == VK_RETURN)
		{
			//截获消息，实现登陆操作
			OnBnClickedButton1();//相当于点击了登陆按钮
			return TRUE;
		} 
	}
	//其他情况正常返回
	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CMonitorSystemServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC1) || (pWnd->GetDlgCtrlID() == IDC_STATIC2))
	{
		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
