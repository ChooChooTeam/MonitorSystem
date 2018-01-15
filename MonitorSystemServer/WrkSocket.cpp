#include "stdafx.h"
#include "WrkSocket.h"
#include "IControler.h"
#include "LstnSocket.h"
#include <Winsock2.h>

//#include "Adosql.h"

//const char ran[] = "0123456789";
WrkSocket::WrkSocket(IControler& con, CString username) :
	ctrler(con),name(username)
{
	msgS = new InfoPack;
	msgR = new InfoPack;
	jpgBuf = new char[256 * 1024];
	//srand(time(NULL));
	//name = name + CString(ran[rand() % 10]) + CString(ran[rand() % 10]);
}

WrkSocket::WrkSocket(IControler & con, CString username, LstnSocket * parent) :
	ctrler(con), name(username), pParent(parent)
{
	msgS = new InfoPack;
	msgR = new InfoPack;
	jpgBuf = new char[256 * 1024];
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
	delete jpgBuf;
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
	//int n = sizeof(WsOp) + sizeof(int) + msgS->mSize;
	Send(msgS, sizeof(InfoPack));
	
	CAsyncSocket::OnConnect(nErrorCode);
}


void WrkSocket::OnReceive(int nErrorCode)
{
	Sleep(10);
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
		op == UNLOOK || op == STOP || op == RESUME) {
		ctrler.DoCmd(op);
	}
	else if (op == JPGE) {
		if (msgR->isEnd == false) {
			memcpy(jpgBuf + jpgBeg, msgR->buff, msgR->mSize);
			jpgBeg += msgR->mSize;
			//FILE* f;
			//fopen_s(&f, "a.bin", "a");
			//fwrite(msgR, sizeof(InfoPack), 1, f);
			//fclose(f);
			//OutputDebugString(_T("写入\n"));
		}
		else {
			memcpy(jpgBuf + jpgBeg, msgR->buff, msgR->mSize);
			ctrler.DoJPG(jpgBuf, jpgBeg+ msgR->mSize);
			jpgBeg = 0;
		}
	}
	else if (op == PROGRESS) {
		//TODO: 后续的进程信息读取
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

	}
	else if (op == USER_RETURN) {

	}
	else {
		OutputDebugString(_T("未定义的指令"));
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void WrkSocket::SendUserInfo(CString name, CString pwdMD5)
{
	//SendControl(USER_INFO);
	//Send(name, name.GetLength() * sizeof(TCHAR));
	//Send(pwdMD5, pwdMD5.GetLength() * sizeof(TCHAR));
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

//void WrkSocket::SendControl(WsOp op)
//{
//	Send(&op, sizeof(WsOp));
//}
#define SLEEPT 100
void WrkSocket::SendJPGE(char * jpg, int size)
{
	const int maxSize = _JPGE_MAX_SIZE_;
	msgS->op = JPGE;
	msgS->mSize = maxSize;
	int jpgBeg = 0;
	while (size > maxSize)
	{
		msgS->isEnd = false;
		memcpy(msgS->buff, jpg+jpgBeg, maxSize);
		Sleep(SLEEPT);
		int n = Send(msgS, sizeof(InfoPack));
		CString ss;
		while (n == -1) {
			Sleep(50);
			int err = GetLastError();
			ss.Format(_T("err = %d\n"),err);
			n = Send(msgS, sizeof(InfoPack));
			OutputDebugString(ss);
		}
		ss.Format(_T("发送: 指令为%d 长度为%d 实际发送长度为%d\n"), msgS->op, msgS->mSize, n);
		OutputDebugString(ss);

		size = size - maxSize;
		jpgBeg += maxSize;
	}

	if (size != 0) {
		Sleep(SLEEPT);
		msgS->isEnd = true;
		msgS->mSize = size;
		memcpy(msgS->buff, jpg + jpgBeg, size);
		int n = Send(msgS, sizeof(InfoPack));
	
		CString ss;
		ss.Format(_T("发送: 指令为%d 长度为%d 实际发送长度为%d\n"), msgS->op, msgS->mSize, n);
		OutputDebugString(ss);
	}
	delete jpg;
}

const CString& WrkSocket::GetName()
{
	return name;
}
