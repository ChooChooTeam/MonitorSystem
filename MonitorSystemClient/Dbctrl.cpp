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
//��ת�߼������Ϊ�棬������һ������
	if (rtn)
	{
		
		mscd->ShowWindow(SW_HIDE);
		mscd->worksocket->Close();
		CDIALOG1 cd;
		cd.DoModal();
	}
	else
		return;
}