#include "stdafx.h"
#include "WrkSocket.h"
#include "IControler.h"
#include "LstnSocket.h"
#include <Winsock2.h>

WrkSocket::WrkSocket(IControler& con, CString username) :
	ctrler(con),name(username)
{
	msgS = new InfoPack;
	msgR = new InfoPack;
	progressBuff = new ProgressInfo[100];
	names = new CString[100];
	PIDs = new short[100];
}

WrkSocket::WrkSocket(IControler & con, CString username, LstnSocket * parent) :
	ctrler(con), name(username), pParent(parent)
{
	msgS = new InfoPack;
	msgR = new InfoPack;
	progressBuff = new ProgressInfo[100];
	names = new CString[100];
	PIDs = new short[100];
}

void WrkSocket::Connect(CString sIp, int nPort)
{
	this->Create();
	CAsyncSocket::Connect(sIp, nPort);
}



WrkSocket::~WrkSocket()
{
	delete msgS;
	delete msgR;
	delete[] progressBuff;
	delete[] names;
	delete[] PIDs;
}

void WrkSocket::OnClose(int nErrorCode)
{
	this->Close();
	if (pParent != nullptr) {
		pParent->NewOffLine(name);
	}
	CAsyncSocket::OnClose(nErrorCode);
}


void WrkSocket::OnConnect(int nErrorCode)
{
	// 连接成功后,立即发送用户名信息
	msgS->op = USER_NAME;
	msgS->mSize = name.GetLength() * sizeof(TCHAR);
	memcpy(msgS->buff, name.GetBuffer(),34);
	Send(msgS, sizeof(InfoPack));
	
	CAsyncSocket::OnConnect(nErrorCode);
}


void WrkSocket::OnReceive(int nErrorCode)
{
	//Sleep(10);
	static int lastLen = 0;
	static bool isLess;
	int n;
	if (!isLess) {
		n = Receive(msgR, sizeof(InfoPack));
		if (n < sizeof(InfoPack)) {
			lastLen = n; 
			isLess = true;

			CString ss;
			ss.Format(_T("拼接: 指令为%d 长度为%d 实际接收长度为%d\n"), msgR->op, msgR->mSize, n);
			OutputDebugString(ss);

			return;
			
		}
		else {
			CString ss;
			ss.Format(_T("回调: 指令为%d 长度为%d 实际接收长度为%d\n"), msgR->op, msgR->mSize, n);
			OutputDebugString(ss);
		}
	}
	else {
		n = Receive(msgR + lastLen, sizeof(InfoPack) - lastLen);

		if (n == SOCKET_ERROR) {
			int err = GetLastError();
			CString ss;
			ss.Format(_T("err = %d\n"), err);
			OutputDebugString(ss);
		}

		lastLen += n;

		CString ss;
		ss.Format(_T("处理: 本次接收%d 累计%d 指令为%d\n"), n, lastLen, msgR->op);
		OutputDebugString(ss);

		if (lastLen >= sizeof(InfoPack)) {
			isLess = false;
		}
		else {
			return;
		}
	}




	
	WsOp op = msgR->op;
	if (op == SHUTDOWN || op == REBOOT || op == LOOK ||
		op == UNLOOK || op == STOP || op == RESUME ||
		op == PROGRESS) {
		ctrler.DoCmd(op);
	}
	else if (op == PROGRESS_RTN) {
		int size = msgR->mSize;
		ProgressInfo* pInfo = (ProgressInfo*)msgR->buff;
		
		for (int i = 0; i < size; i++) {
			names[i] = pInfo[i].name;
			PIDs[i] = pInfo[i].ID;
		}

		ctrler.DoProgress(names, PIDs, size);		
	}
	else if (op == USER_NAME) {
		msgR->buff[msgR->mSize] = '\0';
		msgR->buff[msgR->mSize + 1] = '\0';
		this->name.Format(_T("%s"), msgR->buff);

		if (pParent != nullptr) {
			pParent->NewOnLine();
		}
	}
	else if (op == USER_INFO) {
		UserInfoStr* info = (UserInfoStr*)msgR->buff;
		msgS->op = USER_RETURN;
		msgS->mSize = 4;
		// MyTODO: 修改
		//msgS->buff[0] = ctrler.DoQuary(CString(info->name), CString(info->pwd));
		msgS->buff[0] = 1;
		Send(msgS, sizeof(InfoPack));

	}
	else if (op == USER_RETURN) {
		// 不会出现,不需要任何操作
	}
	else {
		OutputDebugString(_T("未定义的指令"));
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void WrkSocket::SendUserInfo(CString name, CString pwd)
{
	msgS->op = USER_INFO;
	msgS->mSize = sizeof(UserInfoStr);
	UserInfoStr* info = (UserInfoStr*) msgS->buff;

	USES_CONVERSION;
	memcpy(info->name, T2A(name), sizeof(info->name));
	info->name[sizeof(info->name)] = '\0';
	memcpy(info->pwd, T2A(pwd), sizeof(info->pwd));
	info->pwd[sizeof(info->pwd)] = '\0';

	Send(msgS, sizeof(InfoPack));
}

void WrkSocket::SendControl(WsOp op)
{
	msgS->op = op;
	int n = Send(msgS, sizeof(InfoPack));

	if (n == SOCKET_ERROR) {
		int err = GetLastError();
		CString ss;
		ss.Format(_T("err = %d\n"), err);
		OutputDebugString(ss);
	}
}

void WrkSocket::SendProgress(ProgressInfo p[], int num)
{
	int max = _JPGE_MAX_SIZE_ / sizeof(ProgressInfo);
	max = num > max ? max : num;

	memcpy(msgS->buff, p, max * sizeof(ProgressInfo));
	msgS->op = PROGRESS_RTN;
	msgS->mSize = max;

	Send(msgS, sizeof(InfoPack));

}

const CString& WrkSocket::GetName()
{
	return name;
}
