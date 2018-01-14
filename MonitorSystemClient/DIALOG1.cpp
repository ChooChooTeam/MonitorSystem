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
	BProcessM::showAllProcess();
}

//int GetCodecClsid(const WCHAR* format, CLSID* pClsid)
//{
//	UINT  num = 0;
//	UINT  size = 0;
//
//	ImageCodecInfo* pImageCodecInfo = NULL;
//	GetImageEncodersSize(&num, &size);
//	if (size == 0)
//		return -1;
//
//	pImageCodecInfo = new ImageCodecInfo[size];
//	if (pImageCodecInfo == NULL)
//	{
//		delete[]pImageCodecInfo;
//		return -1;
//	}
//	GetImageEncoders(num, size, pImageCodecInfo);
//	for (UINT j = 0; j < num; ++j)
//	{
//		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
//		{
//			*pClsid = pImageCodecInfo[j].Clsid;
//			delete[] pImageCodecInfo;
//			return j;
//		}
//	}
//	delete[] pImageCodecInfo;
//	return -1;
//}


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

#include "../MonitorSystemServer/IControler.h"
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime) {
	Controler * controler = new Controler();
	WrkSocket * w;
	w = new WrkSocket(*controler, _T("sdds"));
	controler->setSocket(w);
	w->Connect(_T("192.168.1.101"), 8848);
	BScreenM* b = new BScreenM(w);
	b->runOnce();
}
void CDIALOG1::OnBnClickedButton1()
{
	
	
	//b->runThreading();
	SetTimer(1, 200, TimerProc);

	
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
