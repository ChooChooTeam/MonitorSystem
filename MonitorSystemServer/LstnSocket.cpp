#include "stdafx.h"
#include "LstnSocket.h"
#include "IControler.h"

LstnSocket::LstnSocket(IControler& con):
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
	WrkSocket* wrk = new WrkSocket(ctrler,nullptr,this);
	vecWrk.push_back(wrk);
	Accept(*wrk,&(wrk->mIP));
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
	std::vector<SOCKADDR> vecIP;
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
	bool done = false;
	for (auto&w : vecWrk) {
		if (w->GetName() == currName) {
			w->SendControl(RESUME);
			done = true;
		}
		else {
			w->SendControl(STOP);
		}
	}

	return done;
}

CString LstnSocket::GetCurrName()
{
	return currName;
}
