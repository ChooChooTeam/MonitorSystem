#pragma once
enum CmdType {
	CT_Confirm, CT_HideDesk, CT_ShowDesk, CT_ShutDown,
	CT_ReRun, CT_Logout, CT_SendText, CT_CloseClient
};
typedef struct DataPackage
{
	CmdType  MsgType;	//命令类型
	char  Content[512]; //文本信息
};
class BPicSendet
{
public:
	BPicSendet();
public:
	int  SendData(UINT index, int mod, int bmpsize, int totalsize, int frames, char *pSendBuf, sockaddr_in &addr);
	
	ULONG_PTR m_pGdiToken;

	SOCKET  m_Socket;		//客户端套接字
	CString m_ServerIP;		//服务器IP
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

	afx_msg void OnTimer(UINT nIDEvent);
	~BPicSendet();
};

