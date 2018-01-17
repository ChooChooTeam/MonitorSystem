// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include <gdiplus.h>
// CMainDlg 对话框
#define CM_RECEIVED  WM_USER+1001
#pragma warning(disable: 4996)   
#define MAX_BUFF 99999
IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

enum CmdType {
	CT_Confirm, CT_HideDesk, CT_ShowDesk, CT_ShutDown,
	CT_ReRun, CT_Logout, CT_SendText, CT_CloseClient
};

typedef struct DataPackage
{
	CmdType	MsgType;		//命令类型
	char	Content[512];	//文本信息,只有在命令类型为CT_SendText时合法
};

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
	, CurrUserName(_T(""))
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
	CClientDC dc(this);


	CRect rc;
	CStatic* pic = (CStatic*)GetDlgItem(IDC_PIC);
	pic->GetClientRect(rc);
	HDC hDC = pic->GetDC()->m_hDC;
	// DEBUG: 此处返回值不正确
	//Gdiplus::Graphics *graphics = Gdiplus::Graphics::FromHDC(hDC);
	Gdiplus::Graphics graphics(hDC);
	graphics.DrawImage(m_pNewBmp, 1, 1, rc.Width(), rc.Height());
	m_pStm->Release();
	m_pStm = NULL;
	//delete graphics;
	GlobalFree(m_hMem1);
	::ReleaseDC(m_hWnd, hDC);
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::setCurrIP(CString currIP)
{
	m_ClientIP = currIP;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_LIST4, m_userlist);
	DDX_Text(pDX, IDC_STATIC4, CurrUserName);
}

//界面框放大后的操作
void CMainDlg::reSize()
{
	float fsp[2];//记录长宽比
	POINT Newp; //获取现在对话框的长、宽 
	CRect new_rect;//新窗口
	GetClientRect(&new_rect);     //放大后窗口大小    
	Newp.x = new_rect.right - new_rect.left;   //新窗口长
	Newp.y = new_rect.bottom - new_rect.top;   //新窗口宽
	fsp[0] = (float)Newp.x / old.x;    //新旧窗口长之比
	fsp[1] = (float)Newp.y / old.y;    //新旧窗口宽之比
	
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角  
	CPoint OldBRPoint, BRPoint; //右下角  
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件
	CPoint userListTLP, userListBRP,procesListP;
	while (hwndChild)
	{
		
		woc = ::GetDlgCtrlID(hwndChild);//取得控件ID  
		if (woc == IDC_STATIC1 || woc == IDC_STATIC2 || woc == IDC_STATIC3 ) {
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
			continue;//不改变这些控件的位置，直接跳过
		}


		GetDlgItem(woc)->GetWindowRect(Rect);  //取得控件区域
		ScreenToClient(Rect);   //转换坐标

		if (woc == IDC_LIST4 || woc == IDC_LIST2) {//长度增加，宽度不变
			OldTLPoint = Rect.TopLeft();  //控件左上角
			TLPoint.x = long(OldTLPoint.x);   //新控件中左上角位置
			TLPoint.y = long(OldTLPoint.y);
			OldBRPoint = Rect.BottomRight();   //控件右下角
			BRPoint.x = long(OldBRPoint.x);//新控件中右下角位置
			BRPoint.y = long(OldBRPoint.y *1.7);
		}
		else if (woc == IDC_PIC) {//长度宽度都增加
			OldTLPoint = Rect.TopLeft();  //控件左上角
			TLPoint.x = long(OldTLPoint.x);   //新控件中左上角位置
			TLPoint.y = long(OldTLPoint.y);
			OldBRPoint = Rect.BottomRight();   //控件右下角
			BRPoint.x = long(OldBRPoint.x *fsp[0]);//新控件中右下角位置
			BRPoint.y = long(OldBRPoint.y *1.7);
		}
		else if (woc == IDC_STATIC4) {
			OldTLPoint = Rect.TopLeft();  //控件左上角
			TLPoint.x = long(OldTLPoint.x *fsp[0]);   //新控件中左上角位置
			TLPoint.y = long(OldTLPoint.y);
			OldBRPoint = Rect.BottomRight();   //控件右下角
			BRPoint.x = long(OldBRPoint.x *fsp[0]);//新控件中右下角位置
			BRPoint.y = long(OldBRPoint.y );
		}
		else if (woc == IDC_BUTTON1 || woc == IDC_BUTTON2 || woc == IDC_BUTTON3
			|| woc == IDC_BUTTON4 || woc == IDC_BUTTON5 ) {
			OldTLPoint = Rect.TopLeft();  //控件左上角
			TLPoint.x = long(OldTLPoint.x);   //新控件中左上角位置
			//新控件中top位置(保持和原控件距底部距离相等)
			TLPoint.y = long(new_rect.bottom-(old.y-old_bt1.top));
			OldBRPoint = Rect.BottomRight();   //控件右下角
			BRPoint.x = long(OldBRPoint.x );//新控件中右下角位置
			BRPoint.y = long(new_rect.bottom - (old.y - old_bt1.bottom));
		}
		else if (woc == IDC_STATIC5) {
			OldTLPoint = Rect.TopLeft();  //控件左上角
			TLPoint.x = long(OldTLPoint.x);   //新控件中左上角位置
											  //新控件中top位置(保持和原控件距底部距离相等)
			TLPoint.y = long(new_rect.bottom - (old.y - old_static5.top));
			OldBRPoint = Rect.BottomRight();   //控件右下角
			BRPoint.x = long(OldBRPoint.x);//新控件中右下角位置
			BRPoint.y = long(new_rect.bottom - (old.y - old_static5.bottom));
		}
		else {
			OldTLPoint = Rect.TopLeft();  //控件左上角
			TLPoint.x = long(OldTLPoint.x*fsp[0]);   //新控件中左上角位置
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();   //控件右下角
			BRPoint.x = long(OldBRPoint.x *fsp[0]);//新控件中右下角位置
			BRPoint.y = long(OldBRPoint.y *fsp[1]);
		}

		/*if (woc == IDC_LIST2) {
			userListTLP = OldTLPoint;
			userListBRP = OldBRPoint;
		}*/

		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);

		/*if (woc == IDC_STATIC1 || woc == IDC_STATIC1 || woc == IDC_STATIC1) {
			CFont *fo;
			fo = new CFont();
			fo->CreatePointFont(90*fsp[0], _T("Times New Roman"));
			GetDlgItem(woc)->SetFont(fo);
		}*/

		//刷新界面
		UpdateWindow();
		Invalidate(FALSE);
	}
	old = Newp;
}



BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CMainDlg::OnNMClickList4)
	ON_MESSAGE(CM_RECEIVED, &CMainDlg::OnReceived)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMainDlg 消息处理程序





BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//获取窗口原始长、宽
	CRect rect;
	GetClientRect(&rect);     //取原窗口大小    
	old.x = rect.right - rect.left;  //原窗口长
	old.y = rect.bottom - rect.top;  //原窗口宽

	GetDlgItem(IDC_BUTTON1)->GetWindowRect(&old_bt1);
	ScreenToClient(&old_bt1);

	GetDlgItem(IDC_STATIC5)->GetWindowRect(&old_static5);
	ScreenToClient(&old_static5);

	//设置字体
	CFont *fo;
	fo = new CFont();
	fo->CreatePointFont(90, _T("Times New Roman"));
	GetDlgItem(IDC_STATIC1)->SetFont(fo);
	GetDlgItem(IDC_STATIC2)->SetFont(fo);
	GetDlgItem(IDC_STATIC3)->SetFont(fo);
	GetDlgItem(IDC_STATIC4)->SetFont(fo);


	//初始化用户信息列表
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_userlist.InsertColumn(0, _T("用户名"), LVCFMT_LEFT, 70);        // 插入列
	m_userlist.InsertColumn(1, _T("IP地址"), LVCFMT_LEFT, 120);        

	CFont *font1;
	font1 = new CFont();
	font1->CreatePointFont(95, _T("Times New Roman"));
	GetDlgItem(IDC_LIST4)->SetFont(font1);

	CString strUserName, strIP;
	for (int i = 0; i <= 7; i++) {
		//strName.Format(_T("进程%d"), i);
		strUserName.Format(_T("username"));//18个字符
		strIP.Format(_T("192.168.001.001"));
		//strAge.Format(_T("%d"), 20 + i);
		m_userlist.InsertItem(i, _T(""));                          // 插入行  
		m_userlist.SetItemText(i, 0, strUserName);                     // 设置第2列 
		m_userlist.SetItemText(i, 1, strIP);                      // 设置第3列  
	}

	//初始化进程信息列表
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_list.InsertColumn(0, _T("进程名"), LVCFMT_LEFT, 150);       //插入列
	m_list.InsertColumn(1, _T("进程ID"), LVCFMT_LEFT, 78); 

	CFont *font2;
	font2 = new CFont();
	font2->CreatePointFont(95, _T("Times New Roman"));
	GetDlgItem(IDC_LIST2)->SetFont(font2);

	CString strName, strAge;
	for (int i = 0; i <= 7; i++) {
		//strName.Format(_T("进程%d"), i);
		strName.Format(_T("abcdefghijklmnopqrs"));//18个字符
		strAge.Format(_T("123456"));
		//strAge.Format(_T("%d"), 20 + i);
		m_list.InsertItem(i, _T(""));                          // 插入行  
		m_list.SetItemText(i, 0, strName);                     // 设置第2列 
		m_list.SetItemText(i, 1, strAge);                      // 设置第3列  
	}
  
	

	mSerCtrl = new SerCtrl(this);
	LSocket = new LstnSocket(*mSerCtrl);
	LSocket->Listen(8848);

	SetTimer(1, 5000, nullptr);

	//获取本机IP
	//hostent* phost = gethostbyname("");
	//char* localIP = inet_ntoa(*(struct in_addr *)*phost->h_addr_list);
	sockaddr_in addr;
	addr.sin_family = AF_INET;

	// 获取配置文件的本机IP地址
	USES_CONVERSION;
	WCHAR localIP[MAX_PATH] = { 0 };
	GetPrivateProfileString(_T("ServerInfo"), _T("LocalIP"), _T("127.0.0.1"), localIP, MAX_PATH, _T("./Client.ini"));
	addr.sin_addr.S_un.S_addr = inet_addr(T2A(localIP));
	
	// 获得监听端口
	int nPort = GetPrivateProfileInt(_T("ServerInfo"), _T("IP"), 5002, _T("./Client.ini"));
	addr.sin_port = htons(nPort);
	
	//创建套接字
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		MessageBox(_T("套接字创建失败!"));
	}
	//绑定套接字
	if (bind(m_Socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(_T("套接字绑定失败!"));
	}
	m_BmpData = new char[1024 * 1024];
	memset(m_BmpData, 0, 1024 * 1024);
	m_TempData = new char[1024 * 1024 * 2];
	memset(m_TempData, 0, 1024 * 1024 * 2);
	m_Header = m_BmpData;
	WSAAsyncSelect(m_Socket, m_hWnd, CM_RECEIVED, FD_READ);
	m_ShowBmp = FALSE;
	m_BmpSize = 0;
	m_RecSize = 0;
	m_ClientPort = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

afx_msg LRESULT CMainDlg::OnReceived(WPARAM wParam, LPARAM lParam)
{
	//CString ss;
	//ss.Format(_T("消息: 回调一次\n"));
	//OutputDebugString(ss);

	//接收数据
	BYTE* buffer = new BYTE[MAX_BUFF];

	int factsize = sizeof(sockaddr);
	int ret = recvfrom(m_Socket, (char*)buffer, MAX_BUFF, 0, (sockaddr*)&m_Addr, &factsize);

	if (ret != -1)
	{
		CString revIP =CString( inet_ntoa(m_Addr.sin_addr));
		if (revIP != m_ClientIP)
		{
			delete[] buffer;
			return 0;
		}
		/*序号2位||结束标记2位||JPG数据||JPG数据大小4位||JPG数据总大小4位||数据报大小4位*/
		m_ClientPort = ntohs(m_Addr.sin_port);
		//记录接收的数据报大小
		m_RecSize += ret;
		//读取序号
		WORD orderID = *(WORD*)&buffer[0];
		//读取结束标记
		WORD endID = *(WORD*)&buffer[2];
		//读取位图大小
		int bmpsize = *(int*)&buffer[ret - 12];
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(m_ClientPort);
		USES_CONVERSION;
		addr.sin_addr.S_un.S_addr = inet_addr(T2A(m_ClientIP));
		int size = sizeof(addr);
		m_JPGSize = 0;
		//发送确认信息
		DataPackage Package;
		memset(&Package, 0, sizeof(DataPackage));

		Package.MsgType = CT_Confirm;

		int nRet = sendto(m_Socket, (char*)&Package, sizeof(DataPackage), 0, (sockaddr*)&m_Addr, size);

		if (orderID == 0)
		{
			m_BmpSize = bmpsize;
			m_BmpData = m_Header;
		}
		else
			m_BmpSize += bmpsize;
		memcpy(m_BmpData, &buffer[4], bmpsize);
		m_BmpData += bmpsize;
		m_ShowBmp = FALSE;
		if (endID == 1)
		{
			m_ShowBmp = TRUE;
			m_BmpData = m_Header;
			m_JPGSize = *(int*)&buffer[ret - 8];
			memset(m_TempData, 0, 1024 * 1024 * 2);
			memcpy(m_TempData, m_Header, 1024 * 1024);
			ShowJPEG(m_TempData, m_JPGSize);
			m_RecSize = 0;
		}
	}
	delete[] buffer;
}


void CMainDlg::OnBnClickedButton3()
{
	// 刷新速度 >= 3s
	LSocket->SendControl(LSocket->GetCurrName(), PROGRESS);
}


// 用户列表框单击事件
void CMainDlg::OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int n = m_userlist.GetSelectionMark();

	CString name = m_userlist.GetItemText(n, 0);

	LSocket->Activate(name);
	

	*pResult = 0;
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here  
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		reSize();
	}
	// TODO: 在此处添加消息处理程序代码
}




void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (!CurrUserName.IsEmpty()) {
		// LSocket->SendControl(CurrUserName, PROGRESS);
	}
	CDialogEx::OnTimer(nIDEvent);
}
