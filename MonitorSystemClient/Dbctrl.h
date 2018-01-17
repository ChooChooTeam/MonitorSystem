#pragma once
//#include "stdafx.h"
#include "..\MonitorSystemServer\IControler.h"
#include "DIALOG1.h"
class CMonitorSystemClientDlg;
class Dbctrl :
	public IControler
{
public:
	//Dbctrl();
	Dbctrl(CMonitorSystemClientDlg * p);
	~Dbctrl();
	void DoCmd(WsOp op) { };
	void DoJPG(char* jpg, int size) { };
	void DoOnLine(std::vector<CString> nameList, std::vector<CString> IPList) {};
	void DoOffLine(std::vector<CString> nameList, CString offlineName) { };
	bool DoQuary(CString name, CString pwd) { return true; };		
	void DoQuaryReturn(bool rtn);
	virtual void DoProgress(CString name[], short PID[], int num)  {};

private:
	CMonitorSystemClientDlg * mscd;

};

