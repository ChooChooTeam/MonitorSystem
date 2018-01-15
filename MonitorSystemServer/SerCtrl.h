#pragma once
#include "IControler.h"

class CMainDlg;

class SerCtrl : public IControler
{
public:
	SerCtrl(CMainDlg* dlg);
	void DoCmd(WsOp op);		// ִ�п���ָ��	
	void DoJPG(char* jpg, int size);  // ִ��ͼƬ
	void DoOnLine(std::vector<CString> nameList);
	void DoOffLine(std::vector<CString> nameList, CString offlineName);
	virtual ~SerCtrl();
private:
	CMainDlg * dlg;
};

