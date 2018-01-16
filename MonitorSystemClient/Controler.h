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

	 void DoCmd(WsOp op);		// 执行控制指令	
	 void DoJPG(char* jpg, int size);  // 执行图片
	 void DoOnLine(std::vector<CString> nameList);
	 void DoOffLine(std::vector<CString> nameList, CString offlineName) ;
	~Controler();
};

