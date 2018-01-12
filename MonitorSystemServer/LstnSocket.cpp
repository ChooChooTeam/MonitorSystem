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

}


void LstnSocket::OnAccept(int nErrorCode)
{
	WrkSocket* wrk = new WrkSocket(ctrler,nullptr,this);
	vecWrk.push_back(wrk);
	Accept(*wrk);

	CAsyncSocket::OnAccept(nErrorCode);
}

void LstnSocket::OnClose(int nErrorCode)
{
	for (auto&i : vecWrk) {
		delete i;
	}
	CAsyncSocket::OnClose(nErrorCode);
}

void LstnSocket::NewOnLine()
{
	std::vector<CString> vecName;
	for (auto&w : vecWrk) {
		vecName.push_back(w->GetName());
	}
	ctrler.DoOnLine(vecName);
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

void LstnSocket::Activate(CString name)
{
	currName = name;

	for (auto&w : vecWrk) {
		if (w->GetName() == currName) {
			w->SendControl(RESUME);
		}
		else {
			w->SendControl(STOP);
		}
	}
}

CString LstnSocket::GetCurrName()
{
	return currName;
}
