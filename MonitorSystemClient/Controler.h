#pragma once
#include "../MonitorSystemServer/IControler.h"
#include "../MonitorSystemServer/WrkSocket.h"
#include "DIALOG1.h"
class Controler :public IControler{
	WrkSocket * socket;
	CDIALOG1 * dlg;
	public:
	Controler(CDIALOG1 *dlg);
	void setSocket(WrkSocket * socket) {
		this->socket = socket;
	}

	 void DoCmd(WsOp op);		// ִ�п���ָ��	
	 void DoJPG(char* jpg, int size);  // ִ��ͼƬ
	 void DoOnLine(std::vector<CString> nameList);
	 void DoOffLine(std::vector<CString> nameList, CString offlineName) ;
	 virtual bool DoQuary(CString name, CString pwd) { return true; };		// ִ�в�ѯ����
	 virtual void DoQuaryReturn(bool rtn) {};					// ִ�в�ѯ���ز���
	~Controler();
};

