#include "stdafx.h"
#include "Dbctrl.h"


Dbctrl::Dbctrl(CMonitorSystemClientDlg * p)
{
	this->mscd = p;
}

Dbctrl::~Dbctrl()
{
}

void Dbctrl::DoCmd(WsOp op)
{
}
void Dbctrl::DoJPG(char* jpg, int size)
{
}
void Dbctrl::DoOnLine(std::vector<CString> nameList, std::vector<SOCKADDR> IPList)
{

}

void Dbctrl::DoOffLine(std::vector<CString> nameList, CString offlineName)
{
}


void  Dbctrl::DoQuaryReturn(bool rtn) 
{
//跳转逻辑，如果为真，跳到下一个界面
	if (rtn)
	{
		
		mscd->ShowWindow(SW_HIDE);
		mscd->worksocket->Close();
		CDIALOG1 cd;
		cd.DoModal();
	}
	else {
		mscd->MessageBox(_T("用户名或密码错误"));
	}
		return;
}