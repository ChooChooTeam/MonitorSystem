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