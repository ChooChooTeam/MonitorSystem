#pragma once
#include "IControler.h"
#include "Adosql.h"

class CMainDlg;

class SerCtrl : public IControler
{
public:
	SerCtrl(CMainDlg* dlg);
	void DoCmd(WsOp op) {};		// 执行控制指令	
	void DoJPG(char* jpg, int size) {};  // 执行图片
	virtual void DoOnLine(std::vector<CString> nameList, std::vector<CString> IPList);
	void DoOffLine(std::vector<CString> nameList, std::vector<CString> IPList);
	bool DoQuary(CString name, CString pwd);
	void DoQuaryReturn(bool rtn) {};
	void DoProgress(CString name[], short PID[], int num);
	void DoActivate(CString name, CString IP);
	virtual ~SerCtrl();

	CMainDlg * dlg;
private:
	Adosql* mAdo;
};

