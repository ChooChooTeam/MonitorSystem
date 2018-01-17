// DIALOG1.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemClient.h"
#include "DIALOG1.h"
#include "afxdialogex.h"
#include "BPowerM.h"
#include "BProcessM.h"
#include "BComInfo.h"
#include "BScreenM.h"
#include "Controler.h"
#include "../MonitorSystemServer/WrkSocket.h"
#define CM_RECEIVED  WM_USER+2

// CDIALOG1 对话框

IMPLEMENT_DYNAMIC(CDIALOG1, CDialogEx)

CDIALOG1::CDIALOG1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDIALOG1::~CDIALOG1()
{

}

void CDIALOG1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CDIALOG1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDIALOG1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CDIALOG1::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CDIALOG1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CDIALOG1::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CDIALOG1::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CDIALOG1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CDIALOG1::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CDIALOG1::OnBnClickedButton8)
	ON_MESSAGE(CM_RECEIVED, &CDIALOG1::OnReceived)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDIALOG1 消息处理程序


void CDIALOG1::OnBnClickedButton2()
{
	BPowerM::EnableShutDownPriv();
	BPowerM::ReSetWindows(EWX_SHUTDOWN, true);//关机  
}


void CDIALOG1::OnBnClickedButton5()
{
	BPowerM::ReSetWindows(EWX_LOGOFF, false);//注销  
}


void CDIALOG1::OnBnClickedButton3()
{
	BPowerM::ReSetWindows(EWX_REBOOT, true);//重启  
}


void CDIALOG1::OnBnClickedButton7()
{
	BPowerM::ReSetWindows(EWX_SETPOWER, true);//睡眠  
}


void CDIALOG1::OnBnClickedButton4()
{
	ProgressInfo * info = new ProgressInfo[100];
	int len = 0;
	BProcessM::showAllProcess(info,&len);


}



//for server
void CDIALOG1::ShowJPEG(void* pData, int DataSize)
{
	/*if (m_ShowBmp)
	{*/
		HGLOBAL m_hMem1 = GlobalAlloc(GMEM_MOVEABLE, DataSize);
		LPBYTE lpData1 = (LPBYTE)GlobalLock(m_hMem1);
		memcpy(lpData1, pData, DataSize);
		GlobalUnlock(m_hMem1);
		::CreateStreamOnHGlobal(m_hMem1, TRUE, &m_pStm);
	//	if (m_pNewBmp)
	//	{
	//		delete m_pNewBmp;
	//		m_pNewBmp = NULL;
	//	}
		m_pNewBmp = Bitmap::FromStream(m_pStm);
		CRect rc;
		GetClientRect(rc);
		HDC hDC = GetDC()->m_hDC;
		Graphics *graphics = Graphics::FromHDC(hDC);
		graphics->DrawImage(m_pNewBmp, 1, 1, rc.Width(), rc.Height());
		m_pStm->Release();
		m_pStm = NULL;
		delete graphics;
		GlobalFree(m_hMem1);
		::ReleaseDC(m_hWnd, hDC);
	/*}*/
}

void CDIALOG1::OnOK()
{
	if (!m_IsSendingJpeg) {
		return;
	}
	
	CDC* pDeskDC = GetDesktopWindow()->GetDC();		//获取桌面画布对象
	CRect rc;
	GetDesktopWindow()->GetClientRect(rc);				//获取屏幕的客户区域

	CDC  memDC;											//定义一个内存画布
	memDC.CreateCompatibleDC(pDeskDC);					//创建一个兼容的画布
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDeskDC, rc.Width(), rc.Height());	//创建兼容位图
	memDC.SelectObject(&bmp);							//选中位图对象	
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);

	int panelsize = 0;									//记录调色板大小
	if (bitmap.bmBitsPixel<16)							//判断是否为真彩色位图
		panelsize = pow(2, bitmap.bmBitsPixel * sizeof(RGBQUAD));

	BITMAPINFO *pBInfo = (BITMAPINFO*)LocalAlloc(LPTR, sizeof(BITMAPINFO) + panelsize);
	pBInfo->bmiHeader.biBitCount = bitmap.bmBitsPixel;
	pBInfo->bmiHeader.biClrImportant = 0;
	pBInfo->bmiHeader.biCompression = 0;
	pBInfo->bmiHeader.biHeight = bitmap.bmHeight;
	pBInfo->bmiHeader.biPlanes = bitmap.bmPlanes;
	pBInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
	pBInfo->bmiHeader.biSizeImage = bitmap.bmWidthBytes*bitmap.bmHeight;
	pBInfo->bmiHeader.biWidth = bitmap.bmWidth;
	pBInfo->bmiHeader.biXPelsPerMeter = 0;
	pBInfo->bmiHeader.biYPelsPerMeter = 0;

	memDC.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, pDeskDC, 0, 0, SRCCOPY);

	char* pData = new char[bitmap.bmWidthBytes* bitmap.bmHeight];
	::GetDIBits(memDC.m_hDC, bmp, 0, bitmap.bmHeight, pData, pBInfo, DIB_RGB_COLORS);

	int BufSize = panelsize + sizeof(BITMAPINFO) + bitmap.bmWidthBytes*bitmap.bmHeight;
	//Bitmap*  mmage;
	//mmage = Bitmap::FromBITMAPINFO(pBInfo, pData);
	//CLSID clsid;
	//GetCodecClsid(L"image/jpeg", &clsid);
	//HGLOBAL m_hMem = GlobalAlloc(GMEM_MOVEABLE, 0);
	//IStream *pstm = NULL;
	//CreateStreamOnHGlobal(m_hMem, TRUE, &pstm);
	//mmage->Save(pstm, &clsid, NULL);
	//m_JpegSize = GlobalSize(m_hMem);
	//LPBYTE lpData = (LPBYTE)GlobalLock(m_hMem);


	CImage img;
	img.Attach(bmp);
	IStream* pOutStream = NULL;
	CreateStreamOnHGlobal(NULL, TRUE, &pOutStream);
	img.Save(pOutStream, Gdiplus::ImageFormatJPEG);//费时间
	HGLOBAL hOutGlobal = NULL;
	GetHGlobalFromStream(pOutStream, &hOutGlobal);
	LPBYTE lpData = (LPBYTE)GlobalLock(hOutGlobal);
	 m_JpegSize = GlobalSize(lpData);
	//char *pBuffer = new char[m_JpegSize];
	//memcpy(pBuffer, lpData, m_JpegSize);


	m_Addr.sin_family = AF_INET;
	m_Addr.sin_port = htons(5002);
	USES_CONVERSION;
	m_Addr.sin_addr.S_un.S_addr = inet_addr(T2A(m_ServerIP));
	m_Bmpsize = GraphSize;
	//计算每个位图发送的次数
	m_Count = m_JpegSize / GraphSize;
	m_Mod = m_JpegSize % GraphSize;
	if (m_Mod != 0)
		m_Count += 1;

	memcpy(m_pSendBuf, lpData, m_JpegSize);
//	for (int m_FrameIndex = 0; m_FrameIndex <= m_Count; m_FrameIndex++) {
	 int ret = SendData(m_FrameIndex, m_Mod, GraphSize, m_JpegSize, m_Count, m_pSendBuf, m_Addr);

//	}

	GlobalUnlock(hOutGlobal);
	memDC.DeleteDC();
	pDeskDC->DeleteDC();
	delete[] pData;
	//delete[] pBuffer;
	pOutStream->Release();
	LocalFree(pBInfo);
	GlobalFree(hOutGlobal);
	bmp.DeleteObject();
	img.Destroy();
	
}

	int CDIALOG1::SendData(UINT index, int mod, int bmpsize, int totalsize, int frames, char * pSendBuf, sockaddr_in & addr)
	{
		/*序号2位||结束标记2位||JPG数据||JPG数据大小4位||JPG数据总大小4位||数据报大小4位*/
		char* pPackage;
		int packsize = 0;
		if (mod == 0 || index != frames - 1)
			packsize = 2 + 2 + bmpsize + 4 + 4 + 4;
		else
			packsize = 2 + 2 + mod + 4 + 4 + 4;
		pPackage = new char[packsize];
		memset(pPackage, 0, packsize);
		//填充数据报
		*(WORD*)&pPackage[0] = index;	//填充序号
		if (index != frames - 1)			//填充结束标记
			*(WORD*)&pPackage[2] = 0;
		else
			*(WORD*)&pPackage[2] = 1;
		//填充位图数据
		pSendBuf += bmpsize * index;
		memcpy(&pPackage[4], pSendBuf, packsize - 12);
		//填充位图大小
		*(int*)&pPackage[packsize - 12] = bmpsize;
		//填充JPG数据总大小
		*(int*)&pPackage[packsize - 8] = totalsize;
		//填充数据报大小
		*(int*)&pPackage[packsize - 4] = packsize;
		m_Confirm = FALSE;
		int ret = sendto(m_Socket, pPackage, packsize, 0, (sockaddr*)&addr, sizeof(addr));
		delete[] pPackage;
		return ret;
	}
	afx_msg LRESULT CDIALOG1::OnReceived(WPARAM wParam, LPARAM lParam)
	{
		char* pData = new char[sizeof(DataPackage)];
		memset(pData, 0, sizeof(DataPackage));
		sockaddr_in addr;
		int factsize = sizeof(sockaddr);
		int ret = recvfrom(m_Socket, pData, sizeof(DataPackage), 0, (sockaddr*)&addr, &factsize);

		if (ret != -1)
		{
			DataPackage Package;
			memcpy(&Package, pData, sizeof(DataPackage));
			delete[]pData;
			if (Package.MsgType == CT_Confirm)
			{
				m_Received = TRUE;
				m_FrameIndex += 1;
				if (m_FrameIndex < m_Count)
					SendData(m_FrameIndex, m_Mod, m_Bmpsize, m_JpegSize, m_Count, m_pSendBuf, m_Addr);
				else {
					m_FrameIndex = 0;
					OnOK();

				}
			}
			else if (Package.MsgType == CT_HideDesk)	//隐藏桌面操作
			{
				HWND hWnd = ::FindWindow(_T("ProgMan"), NULL);
				::ShowWindow(hWnd, SW_HIDE);

			}
			else if (Package.MsgType == CT_ShowDesk)	//显示桌面操作
			{
				HWND hWnd = ::FindWindow(_T("ProgMan"), NULL);
				::ShowWindow(hWnd, SW_SHOW);
			}
			else if (Package.MsgType == CT_ShutDown)	//关机
			{
				ExitWindowsEx(EWX_SHUTDOWN | EWX_POWEROFF, 0);

			}
			else if (Package.MsgType == CT_Logout)		//注销
			{
				ExitWindowsEx(EWX_LOGOFF, 0);
			}
			else if (Package.MsgType == CT_SendText)	//显示文本
			{
			//	MessageBox(Package.Content, "提示");
			}
			else if (Package.MsgType == CT_ReRun)		//重新启动
			{
				ExitWindowsEx(EWX_REBOOT, 0);
			}
			else if (Package.MsgType == CT_CloseClient)	//结束程序
			{
				OnCancel();
			}
		}
		else
		{
			delete[]pData;
		}
		return true;
	}

#include "../MonitorSystemServer/IControler.h"
void CDIALOG1::OnBnClickedButton1()
{
	//获取本机IP
	



	Controler * controler = new Controler(this);
	WrkSocket * w;
	WCHAR username[20];
	GetPrivateProfileString(_T("UserInfo"), _T("Name"),_T("noName"), username,20, _T("./Server.ini"));
	w = new WrkSocket(*controler, username);
	controler->setSocket(w);
	WCHAR ServerIP[20];
	GetPrivateProfileString(_T("ServerInfo"), _T("IP"), _T("127.0.0.1"), ServerIP, MAX_PATH, _T("./Server.ini"));
	int ServerPort = GetPrivateProfileInt(_T("ServerInfo"), _T("Port"), 5002, _T("./Server.ini"));
	w->Connect(ServerIP, ServerPort);
	//BScreenM* b = new BScreenM(this);
	//b->runThreading();
	//SetTimer(1, 50, TimerProc);
}

void showMessage(CString message) {
	
	MessageBox(NULL, message, TEXT("服务器端消息!"), MB_ICONWARNING | MB_SYSTEMMODAL);

}

void CDIALOG1::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	s = "hello";
	showMessage(s);
}


void CDIALOG1::OnBnClickedButton8()
{
	BComInfo::GetSysInfo();
	//SetHook();
	MessageBox(TEXT("你已经被管理员锁定！请联系管理员 /f8 解锁！"), TEXT("警告!"), MB_ICONWARNING | MB_SYSTEMMODAL);
	
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CDIALOG1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	hostent* phost = gethostbyname("");
	char* localIP = inet_ntoa(*(struct in_addr *)*phost->h_addr_list);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(localIP);
	addr.sin_port = htons(5001);
	//创建套接字
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		MessageBox(_T("套接字创建失败!"));
	}
	char* len = "9999";
	
	if (setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, len, 4) != 0)
	{
		MessageBox(_T("设置失败!"));
	}

	//绑定套接字
	if (bind(m_Socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(_T("套接字绑定失败!"));
	}
	
	m_ServerIP =_T( "127.0.0.1        ");
	//注意溢出
	GetPrivateProfileString(_T("ServerInfo"), _T("IP"), _T("127.0.0.1"), m_ServerIP.GetBuffer(0), MAX_PATH, _T("./Server.ini"));
	_ASSERTE(_CrtCheckMemory());
	m_pSendBuf = new char[1024 * 1024];
	
	m_pHeader = m_pSendBuf;
	WSAAsyncSelect(m_Socket, m_hWnd, CM_RECEIVED, FD_READ);
	m_Confirm = TRUE;

//	OnOK();
	m_Received = FALSE;
	m_Counter = 0;
	SetTimer(1, 200, NULL);
	m_IsSendingJpeg = false;
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDIALOG1::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_Received)
	{
		m_Counter++;
		if (m_Counter >= 2)
		{
			m_Counter = 0;
			OnOK();  //超过5秒没有收到服务器的应答信息,重发数据
		}
	}
	else
	{
		m_Received = FALSE;
		m_Counter = 0;
	}
	CDialog::OnTimer(nIDEvent);
}
