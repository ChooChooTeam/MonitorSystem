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
	//MyTODO: 注意,上线的同时还要通知更新当前UI
	dlg->m_userlist.DeleteAllItems();
	
	for (unsigned int i = 0; i < nameList.size(); i++) {
		dlg->m_userlist.InsertItem(i, nameList[i]);
		dlg->m_userlist.SetItemText(i, 1, nameList[i]);
	}
}

void SerCtrl::DoOffLine(std::vector<CString> nameList, CString offlineName)
{
	dlg->m_userlist.DeleteAllItems();

	for (unsigned int i = 0; i < nameList.size(); i++) {
		dlg->m_userlist.InsertItem(i, nameList[i]);
		dlg->m_userlist.SetItemText(i, 1, nameList[i]);
	}
}


SerCtrl::~SerCtrl()
{
}
