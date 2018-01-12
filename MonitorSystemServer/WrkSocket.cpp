#include "stdafx.h"
#include "WrkSocket.h"
#include "IControler.h"
#include "LstnSocket.h"
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
	// ���ӳɹ���,���������û�����Ϣ
	msgS->op = USER_NAME;
	msgS->mSize = name.GetLength() * sizeof(TCHAR);
	memcpy(msgS->buff, name.GetBuffer(),34);
	int n = sizeof(WsOp) + sizeof(int) + msgS->mSize;
	Send(msgS, n);
	
	CAsyncSocket::OnConnect(nErrorCode);
}


void WrkSocket::OnReceive(int nErrorCode)
{
	int n = Receive(msgR, sizeof(InfoPack));
	WsOp op = msgR->op;
	if (op == SHUTDOWN || op == REBOOT || op == LOOK ||
		op == UNLOOK || op == STOP || op == RESUME) {
		ctrler.DoCmd(op);
	}
	else if (op == JPGE) {
		if (msgR->isEnd == false) {
			memcpy(jpgBuf + jpgBeg, msgR->buff, msgR->mSize);
			jpgBeg += msgR->mSize;
		}
		else {
			memcpy(jpgBuf + jpgBeg, msgR->buff, msgR->mSize);
			ctrler.DoJPG(jpgBuf, jpgBeg+ msgR->mSize);
			jpgBeg = 0;
		}
	}
	else if (op == PROGRESS) {
		//TODO: �����Ľ�����Ϣ��ȡ
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



	//if (step == 0) {
	//	WsOp op;
	//	Receive(&op, sizeof(WsOp));

	//}
	//else if (step == 1) {
	//	if (status == JPGE) {
	//		Receive(&mSize, sizeof(int));
	//		step = 2;
	//	}
	//	else if (status == USER_NAME) {
	//		char szTemp[34];
	//		int n = Receive(szTemp, 34);
	//		//szTemp[n] = '\0';
	//		//szTemp[n + 1] = '\0';
	//		this->name.Format(_T("%s"), szTemp);
	//		pParent->NewOnLine();
	//		step = 0;
	//	}
	//	else if (status == USER_INFO) {
	//		char name[34];
	//		int n;
	//		n = Receive(name, 34);
	//		name[n] = '\0'; name[n + 1] = '\0';
	//		step = 2;
	//	}

	//	
	//}
	//else if (step == 2) {
	//	if (status == JPGE) {
	//		delete jpgBuff;
	//		jpgBuff = new char[mSize];
	//		Receive(jpgBuff, mSize);
	//		ctrler.DoJPG(jpgBuff, mSize);
	//		step = 0;
	//	}
	//	else if (status == USER_INFO) {
	//		char md5[34];
	//		int n = Receive(md5, 34);
	//		md5[n] = '\0'; md5[n] = '\0';
	//		// TODO:
	//		step = 0;
	//	}
	//}


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
	const int maxSize = 35 * 1024;
	msgS->op = JPGE;
	msgS->mSize = maxSize;
	int jpgBeg = 0;
	msgS->isEnd = false;
	while (size > maxSize)
	{
		memcpy(msgS->buff, jpg+jpgBeg, maxSize);
		Send(msgS, sizeof(InfoPack));
		size = size - maxSize;
		jpgBeg += maxSize;
	}

	if (size != 0) {
		msgS->isEnd = true;
		memcpy(msgS->buff, jpg + jpgBeg, size);
		Send(msgS, sizeof(InfoPack));
	}

	//CString s;
	//s.Format(_T("����JPG: %d�ֽ�"), size);
	//AfxMessageBox(s);
}

const CString& WrkSocket::GetName()
{
	return name;
}
