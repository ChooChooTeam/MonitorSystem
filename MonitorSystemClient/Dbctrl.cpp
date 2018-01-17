#include "stdafx.h"
#include "Dbctrl.h"


Dbctrl::Dbctrl(CMonitorSystemClientDlg * p)
{
	this->mscd = p;
}

Dbctrl::~Dbctrl()
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
	else
		return;
}