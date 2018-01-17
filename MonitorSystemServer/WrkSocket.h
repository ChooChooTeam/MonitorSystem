#pragma once
class IControler;
class LstnSocket;

#define _JPGE_MAX_SIZE_  (2*1024 - 4*3)

enum WsOp
{
	// 控制信息
	SHUTDOWN,			// 关机
	REBOOT,				// 重启
	LOOK,				// 锁定
	UNLOOK,				// 解锁		
	STOP,				// 停止发送图片
	RESUME,				// 恢复发送图片
	// 其他信息
	USER_NAME = 0x20,	// 将要发送用户名(初始身份识别)
	USER_INFO = 0x21,	// 将要发送用户信息(用户名和密码)
	USER_RETURN = 0x22,	// 将要发送用户信息核对结果(客户端登录)
	PROGRESS = 0x23,	// 将要发送进程信息
	PROGRESS_RTN = 0x25,// 返回进程信息
	JPGE = 0x24,		// 将要发送图片信息
};

struct InfoPack {
	WsOp op;
	int mSize;
	int isEnd;
	char buff[_JPGE_MAX_SIZE_];
};


struct UserInfoStr {
	char name[33];
	char pwd[33];
};

struct ProgressInfo {
	char name[18];
	short ID;
};

// 工作Socket
// 客户端可使用此Socket向服务器端通讯
class WrkSocket : public CAsyncSocket
{
public:
	
	WrkSocket(IControler& con,CString username); // 客户端构造函数
	WrkSocket(IControler& con, CString username, LstnSocket* parent); // 服务器端构造函数
	void Connect(CString sIp, int nPort);	// 连接
	virtual ~WrkSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	void SendUserInfo(CString name, CString pwdMD5);
	void SendControl(WsOp op);			// 发送控制信息
	void SendProgress(ProgressInfo p[], int num);

	const CString& GetName();
	CString mIP;			// 套接字对应的(客户端的)IP

private:
	CString name;			// 套接字对应的用户名
	IControler & ctrler;	// 回调控制器
	LstnSocket* pParent;	// 服务器套接字

	InfoPack* msgS;			// 发送缓冲区
	InfoPack* msgR;			// 接受缓冲区

	ProgressInfo* progressBuff;	// 进程信息缓冲区
	CString* names;				// 进程用户名
	short* PIDs;				// 进程PID
	
};

