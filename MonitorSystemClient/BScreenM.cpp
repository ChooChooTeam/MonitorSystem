#include "stdafx.h"
#include "BScreenM.h"
struct para {
	BScreenM * M;
};


void  sendScreenData(para* p) {
	DWORD start;
	DWORD end;
	while (true) {
		start = GetTickCount();
		CDC* pDeskDC;
		CRect rc;
		CDC  memDC;
		CBitmap bmp;
		BITMAP bitmap;
		int panelsize = 0;
		BITMAPINFO *pBInfo;
		pDeskDC = AfxGetMainWnd()->GetDesktopWindow()->GetDC();		//获取桌面画布对象

		AfxGetMainWnd()->GetDesktopWindow()->GetClientRect(rc);				//获取屏幕的客户区域

																//定义一个内存画布
		memDC.CreateCompatibleDC(pDeskDC);					//创建一个兼容的画布

		bmp.CreateCompatibleBitmap(pDeskDC, rc.Width(), rc.Height());	//创建兼容位图
		memDC.SelectObject(&bmp);							//选中位图对象

		bmp.GetBitmap(&bitmap);


		if (bitmap.bmBitsPixel < 16)							//判断是否为真彩色位图
			panelsize =(int) pow(2, bitmap.bmBitsPixel * sizeof(RGBQUAD));

		pBInfo = (BITMAPINFO*)LocalAlloc(LPTR, sizeof(BITMAPINFO) + panelsize);
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
		img.Save(pOutStream, Gdiplus::ImageFormatJPEG);//费时间
		HGLOBAL hOutGlobal = NULL;
		GetHGlobalFromStream(pOutStream, &hOutGlobal);
		LPBYTE lpData = (LPBYTE)GlobalLock(hOutGlobal);
		int mJpegSize = GlobalSize(lpData);
		char *pBuffer = new char[mJpegSize];
		memcpy(pBuffer, lpData, mJpegSize);
		GlobalUnlock(hOutGlobal);
		memDC.DeleteDC();
		pDeskDC->DeleteDC();

		//send data

		p->M->socket->SendJPGE(pBuffer, mJpegSize);

		delete[] pData;
		//delete[] pBuffer;
		pOutStream->Release();
		LocalFree(pBInfo);
		GlobalFree(hOutGlobal);
		
		bmp.DeleteObject();
		img.Destroy();


		end = GetTickCount();
		
		DWORD  runTime = end - start;
		if (runTime) {
	
			Sleep(500- runTime);
		
		}
	}
	//delete p;




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


	// TODO: 在此添加控件通知处理程序代码
}
HANDLE BScreenM::g_hMutex=NULL;
bool BScreenM::runAble = 1;
void BScreenM::runOnce()
{
	para* p = new para;
	p->M = this;
	sendScreenData(p);
}
HANDLE BScreenM::runThreading()
{
	
		para* p = new para;
		p->M = this;
		return  CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE)sendScreenData,
			p,
			0,
			&threadID);


	
}

BScreenM::~BScreenM()
{
}
