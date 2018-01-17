#pragma once
#include "IControler.h"
#include "Adosql.h"

class CMainDlg;

class SerCtrl : public IControler
{
public:
	SerCtrl(CMainDlg* dlg);
	void DoCmd(WsOp op);		// 执行控制指令	
	void DoJPG(char* jpg, int size);  // 执行图片
	void DoOnLine(std::vector<CString> nameList);
	void DoOffLine(std::vector<CString> nameList, CString offlineName);
	bool DoQuary(CString name, CString pwd);
	void DoQuaryReturn(bool rtn);
	virtual ~SerCtrl();
private:
	CMainDlg * dlg;
	Adosql* mAdo;
};

