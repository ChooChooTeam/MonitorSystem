#pragma once
#include "IControler.h"
#include "Adosql.h"

class CMainDlg;

class SerCtrl : public IControler
{
public:
	SerCtrl(CMainDlg* dlg);
	void DoCmd(WsOp op);		// ִ�п���ָ��	
	void DoJPG(char* jpg, int size);  // ִ��ͼƬ
	virtual void DoOnLine(std::vector<CString> nameList, std::vector<SOCKADDR> IPList);
	void DoOffLine(std::vector<CString> nameList, CString offlineName);
	bool DoQuary(CString name, CString pwd);
	void DoQuaryReturn(bool rtn);
	void DoProgress(CString name[], short PID[], int num);
	virtual ~SerCtrl();
private:
	CMainDlg * dlg;
	Adosql* mAdo;
};

