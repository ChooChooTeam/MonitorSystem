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
	 void DoOnLine(std::vector<CString> nameList, std::vector<CString> IPList);
	 void DoOffLine(std::vector<CString> nameList, CString offlineName) ;
	 bool DoQuary(CString name, CString pwd) { return true; };		// 执行查询操作
	 void DoQuaryReturn(bool rtn) {};					// 执行查询返回操作
	 void DoProgress(CString name[], short PID[], int num) {};
	 void DoActivate(CString name, CString IP) {};
	~Controler();
};

