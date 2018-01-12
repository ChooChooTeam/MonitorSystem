#include "stdafx.h"
#include "SerCtrl.h"
#include "MainDlg.h"

SerCtrl::SerCtrl(CMainDlg * dlg)
{
	this->dlg = dlg;
}

void SerCtrl::DoCmd(WsOp op)
{
}

void SerCtrl::DoJPG(char * jpg, int size)
{
	OutputDebugString(_T("Get jpg"));
	dlg->ShowJPEG(jpg, size);
}

void SerCtrl::DoOnLine(std::vector<CString> nameList)
{
}

void SerCtrl::DoOffLine(std::vector<CString> nameList, CString offlineName)
{
}


SerCtrl::~SerCtrl()
{
}
