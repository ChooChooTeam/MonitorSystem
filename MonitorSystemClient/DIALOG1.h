#pragma once
using namespace Gdiplus;
#define GraphSize    40960
enum CmdType {
	CT_Confirm, CT_HideDesk, CT_ShowDesk, CT_ShutDown,
	CT_ReRun, CT_Logout, CT_SendText, CT_CloseClient
};
typedef struct DataPackage
{
	CmdType  MsgType;	//命令类型
	char  Content[512]; //文本信息
};

// CDIALOG1 对话框

class CDIALOG1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDIALOG1)
	//for server
	IStream *m_pStm;
	Bitmap  *m_pNewBmp;
	void ShowJPEG(void* pData, int DataSize);
	void OnOK();
	//for jpeg
	int  SendData(UINT index, int mod, int bmpsize, int totalsize, int frames, char *pSendBuf, sockaddr_in &addr);
	afx_msg LRESULT OnReceived(WPARAM wParam, LPARAM lParam);
	SOCKET  m_Socket;		//客户端套接字
	CString		m_ServerIP;		//服务器IP
	BOOL	m_Confirm;		//确认信息
	int     m_FrameIndex;	//记录索引
	int     m_Mod;			//记录余数
	int     m_Count;		//每一个位图分报的数量
	int     m_Bmpsize;		//位图的实际大小
	char*	m_pSendBuf;		//发送缓冲区指针
	char*	m_pHeader;		//临时指针
	sockaddr_in  m_Addr;	//套接字地址
	BOOL    m_Received;		//是否接收到服务器发来的确认信息
	int     m_Counter;		//记数器
	DWORD	m_JpegSize;		//JPEG数据总大小
	int m_IsSendingJpeg;
	WrkSocket * w;
public:
	void startJpeg() {
		m_IsSendingJpeg = true;
		OnOK();

	}
	void stopJpeg() {
		m_IsSendingJpeg = false;
	}
	CDIALOG1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDIALOG1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};
