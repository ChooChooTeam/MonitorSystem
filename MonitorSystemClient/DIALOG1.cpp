// DIALOG1.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemClient.h"
#include "DIALOG1.h"
#include "afxdialogex.h"
#include "BPowerM.h"
#include "BProcessM.h"

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
void CDIALOG1::OnBnClickedButton1()
{
	//TODO:修改内存泄漏，每次调用会有平均200byte泄露
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
	//new code
	int BufSize = panelsize + sizeof(BITMAPINFO) + bitmap.bmWidthBytes*bitmap.bmHeight;


	CImage img;
	img.Attach(bmp);
	IStream* pOutStream = NULL;
	CreateStreamOnHGlobal(NULL, TRUE, &pOutStream);
	img.Save(pOutStream, Gdiplus::ImageFormatJPEG);
	HGLOBAL hOutGlobal = NULL;
	GetHGlobalFromStream(pOutStream, &hOutGlobal);
	LPBYTE lpData = (LPBYTE)GlobalLock(hOutGlobal);
	int mJpegSize = GlobalSize(lpData);
	char *pBuffer = new char[mJpegSize];
	memcpy(pBuffer, lpData, mJpegSize);

	GlobalUnlock(hOutGlobal);


	//old code
	/*int BufSize = panelsize + sizeof(BITMAPINFO) + bitmap.bmWidthBytes*bitmap.bmHeight;
	Bitmap*  mmage;
	mmage = Bitmap::FromBITMAPINFO(pBInfo, pData);
	CLSID clsid;
	GetCodecClsid(L"image/jpeg", &clsid);
	HGLOBAL m_hMem = GlobalAlloc(GMEM_MOVEABLE, 0);
	IStream *pstm = NULL;
	CreateStreamOnHGlobal(m_hMem, TRUE, &pstm);
	mmage->Save(pstm, &clsid, NULL);
	m_JpegSize = GlobalSize(m_hMem);
	LPBYTE lpData = (LPBYTE)GlobalLock(m_hMem);*/
	//end old

	//m_Addr.sin_family = AF_INET;
	//m_Addr.sin_port = htons(5002);
	//m_Addr.sin_addr.S_un.S_addr = inet_addr(m_ServerIP);
	//m_Bmpsize = GraphSize;
	////计算每个位图发送的次数
	//m_Count = m_JpegSize / GraphSize;
	//m_Mod = m_JpegSize % GraphSize;
	//if (m_Mod != 0)
	//	m_Count += 1;
	//m_FrameIndex = 0;
	//memcpy(m_pSendBuf, lpData, m_JpegSize);
	//int ret = SendData(m_FrameIndex, m_Mod, GraphSize, m_JpegSize, m_Count, m_pSendBuf, m_Addr);


	//for server
	//显示jpeg图片。
	//ShowJPEG(lpData, mJpegSize);
	//end for

	memDC.DeleteDC();
	pDeskDC->DeleteDC();
	//pstm->Release();
	//if (mmage)
	//	delete mmage;
	delete[] pData;
	delete[] pBuffer;
	pOutStream->Release();
	LocalFree(pBInfo);
	//GlobalUnlock(m_hMem);
	//GlobalFree(m_hMem);
	//::LocalFree((HLOCAL)pBInfo);
	bmp.DeleteObject();
	// TODO: 在此添加控件通知处理程序代码
}
void showMessage(CString message) {
	;
	MessageBox(NULL, message, TEXT("服务器端消息!"), MB_ICONWARNING | MB_SYSTEMMODAL);

}

void CDIALOG1::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	s = "hello";
	showMessage(s);
}
