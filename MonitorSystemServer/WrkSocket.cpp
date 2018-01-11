#include "stdafx.h"
#include "WrkSocket.h"
#include "IControler.h"
#include "LstnSocket.h"

const char ran[] = "0123456789";
WrkSocket::WrkSocket(IControler& con, CString username) :
	ctrler(con),name(username)
{
	srand(time(NULL));
	name = name + CString(ran[rand() % 10]) + CString(ran[rand() % 10]);
}

WrkSocket::WrkSocket(IControler & con, CString username, LstnSocket * parent) :
	ctrler(con), name(username), pParent(parent)
{
}

void WrkSocket::Connect(CString sIp, int nPort)
{
	this->Create();
	CAsyncSocket::Connect(sIp, nPort);
}



WrkSocket::~WrkSocket()
{
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
	// 连接成功后,立即发送用户信息
	WsOp op = USER_INFO;
	Send(&op, sizeof(WsOp));
	Send(name, name.GetLength() * sizeof(TCHAR));

	CAsyncSocket::OnConnect(nErrorCode);
}


void WrkSocket::OnReceive(int nErrorCode)
{
	WsOp op;
	Receive(&op, sizeof(WsOp));

	if (op == SHUTDOWN || op == REBOOT || op == LOOK ||
		op == UNLOOK || op == STOP || op == RESUME) {
		ctrler.DoCmd(op);
	}
	else if (op == JPGE) {
		delete jpgBuff;
		Receive(&mSize, sizeof(int));
		jpgBuff = new char[mSize];
		Receive(jpgBuff, mSize);
		ctrler.DoJPG(jpgBuff, mSize);
	}
	else if (op == PROGRESS) {
		//TODO: 后续的进程信息读取
	}
	else if (op == USER_INFO) {
		char szTemp[34];
		int n = Receive(szTemp, 34);
		szTemp[n] = '\0';
		szTemp[n + 1] = '\0';
		this->name.Format(_T("%s"), szTemp);
		pParent->NewOnLine();
	}


	CAsyncSocket::OnReceive(nErrorCode);
}

void WrkSocket::SendControl(WsOp op)
{
	Send(&op, sizeof(WsOp));
}

void WrkSocket::SendJPGE(char * jpg, int size)
{
	SendControl(JPGE);
	Send(&size, sizeof(int));
	Send(jpg, size);
}

const CString& WrkSocket::GetName()
{
	return name;
}
