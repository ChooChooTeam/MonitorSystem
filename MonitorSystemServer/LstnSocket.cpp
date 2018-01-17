#include "stdafx.h"
#include "LstnSocket.h"
#include "IControler.h"
#include "SerCtrl.h"

LstnSocket::LstnSocket(IControler & con):
	ctrler(con)
{

}

void LstnSocket::Listen(int nPort)
{
	this->Create(nPort);
	CAsyncSocket::Listen();
}


LstnSocket::~LstnSocket()
{
	for (auto&i : vecWrk) {
		delete i;
		i = nullptr;
	}
}


void LstnSocket::OnAccept(int nErrorCode)
{
	SOCKADDR_IN sockaddr_in;
	int sockaddr_in_len = sizeof(sockaddr_in);
	
	WrkSocket* wrk = new WrkSocket(ctrler,nullptr,this);
	vecWrk.push_back(wrk);
	
	Accept(*wrk, (SOCKADDR*)&sockaddr_in,&sockaddr_in_len);
	wrk->mIP.Format(_T("%d.%d.%d.%d"), sockaddr_in.sin_addr.S_un.S_un_b.s_b1,
		sockaddr_in.sin_addr.S_un.S_un_b.s_b2,
		sockaddr_in.sin_addr.S_un.S_un_b.s_b3,
		sockaddr_in.sin_addr.S_un.S_un_b.s_b4);

	CAsyncSocket::OnAccept(nErrorCode);
}

void LstnSocket::OnClose(int nErrorCode)
{
	for (auto&i : vecWrk) {
		delete i;
		i = nullptr;
	}
	CAsyncSocket::OnClose(nErrorCode);
}

void LstnSocket::NewOnLine()
{
	std::vector<CString> vecName;
	std::vector<CString> vecIP;
	for (auto&w : vecWrk) {
		// 只放入已经有名字的Socket
		if (w->GetName().Compare(_T("")) != 0) {
			vecName.push_back(w->GetName());
			vecIP.push_back(w->mIP);
		}
	}
	ctrler.DoOnLine(vecName,vecIP);
}

void LstnSocket::NewOffLine(CString name)
{
	std::vector<CString> vecName;
	auto it = vecWrk.begin();
	while (it != vecWrk.end())
	{
		if ((*it)->GetName() != name) {
			vecName.push_back((*it)->GetName());
		}
		else {
			delete (*it);
			it = vecWrk.erase(it);
		}

		if (it != vecWrk.end()) {
			it++;
		}
		else {
			break;
		}
		
	}

	ctrler.DoOffLine(vecName, name);

}


void LstnSocket::SendControl(CString name, WsOp op)
{
	for (auto&w : vecWrk) {
		if (w->GetName() == name) {
			w->SendControl(op);

			return;
		}
	}
}

bool LstnSocket::Activate(CString name)
{
	currName = name;
	CString IP;
	bool done = false;
	for (auto&w : vecWrk) {
		if (w->GetName() == currName) {
			w->SendControl(RESUME);
			IP = w->mIP;
			done = true;
		}
		else {
			w->SendControl(STOP);
		}
	}

	ctrler.DoActivate(name,IP);

	return done;
}

CString LstnSocket::GetCurrName()
{
	return currName;
}
