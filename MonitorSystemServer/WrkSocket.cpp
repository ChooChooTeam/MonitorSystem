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
	static bool isLess;
	int n = Receive(msgR, sizeof(InfoPack));

	if (n < sizeof(InfoPack) && !isLess) {
		isLess = true;
		int len = n - sizeof(WsOp) - sizeof(int) - sizeof(int);
		memcpy(jpgBuf + jpgBeg, msgR->buff, len);
		jpgBeg += len;

		CString ss;
		ss.Format(_T("处理:  指令为%d 长度为%d 实际接收长度为%d,写入\n"), msgR->op, msgR->mSize, n);
		OutputDebugString(ss);

		return;
	}

	if (isLess) {
		memcpy(jpgBuf + jpgBeg, &msgR, n);
		jpgBeg += n;
		isLess = false;
		
		CString ss;
		ss.Format(_T("处理:  实际接收长度为%d,写入第二部分\n"), n);
		OutputDebugString(ss);

		return;
	}

	CString ss;
	ss.Format(_T("回调: 指令为%d 长度为%d 实际接收长度为%d\n"), msgR->op, msgR->mSize,n);
	OutputDebugString(ss);

	
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
			OutputDebugString(_T("写入\n"));
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

//void WrkSocket::SendControl(WsOp op)
//{
//	Send(&op, sizeof(WsOp));
//}

void WrkSocket::SendJPGE(char * jpg, int size)
{
	const int maxSize = 1024;
	msgS->op = JPGE;
	msgS->mSize = maxSize;
	int jpgBeg = 0;
	while (size > maxSize)
	{
		msgS->isEnd = false;
		memcpy(msgS->buff, jpg+jpgBeg, maxSize);
		int n = Send(msgS, sizeof(InfoPack));
		Sleep(5);
		if (n == SOCKET_ERROR) {
			int err = GetLastError(); 
			CString ss;
			ss.Format(_T("err = %d\n"), err);
		}

		CString ss;
		ss.Format(_T("发送: 指令为%d 长度为%d 实际发送长度为%d\n"), msgS->op, msgS->mSize, n);
		OutputDebugString(ss);

		size = size - maxSize;
		jpgBeg += maxSize;
	}

	if (size != 0) {
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
