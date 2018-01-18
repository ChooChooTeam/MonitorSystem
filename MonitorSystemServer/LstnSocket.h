#pragma once
#include "WrkSocket.h"
#include <string>
#include <map>
#include <vector>
// 监听Socket
// 服务器端使用,用于监听客户端请求
class LstnSocket : public CAsyncSocket
{
public:
	LstnSocket(IControler& con);
	void Listen(int nPort);
	void SendControl(CString name, WsOp op);	// 发送控制信息
	bool Activate(CString name);				// 激活指定名的客户端
	CString GetCurrName();						// 获得当前处于激活状态的Socket客户名
	void ResetAll();
	virtual ~LstnSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void NewOnLine();
	void NewOffLine(CString name);

private:
	std::vector<WrkSocket*> vecWrk;
	CString currName;
	IControler& ctrler;
	int port;
};

