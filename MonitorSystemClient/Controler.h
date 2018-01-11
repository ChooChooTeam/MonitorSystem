#pragma once
#include "../MonitorSystemServer/IControler.h"
#include "../MonitorSystemServer/WrkSocket.h"
#include "BScreenM.h"
class Controler :public IControler{
	WrkSocket * socket;
	BScreenM *b = NULL;
public:
	Controler();
	void setSocket(WrkSocket * socket) {
		this->socket = socket;
	}

	 void DoCmd(WsOp op);		// ִ�п���ָ��	
	 void DoJPG(char* jpg, int size);  // ִ��ͼƬ
	 void DoOnLine(std::vector<CString> nameList);
	 void DoOffLine(std::vector<CString> nameList, CString offlineName) ;
	~Controler();
};

