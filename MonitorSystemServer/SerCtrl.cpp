#include "stdafx.h"
#include "SerCtrl.h"
#include "MainDlg.h"

SerCtrl::SerCtrl(CMainDlg * dlg)
{
	this->dlg = dlg;
}


void SerCtrl::DoOnLine(std::vector<CString> nameList, std::vector<CString> IPList)
{
	dlg->m_userlist.DeleteAllItems();
	
	for (unsigned int i = 0; i < nameList.size(); i++) {
		// 隐藏数据库服务
		if (nameList[i].Compare(_T("db")) != 0) {
			dlg->m_userlist.InsertItem(i, nameList[i]);
			dlg->m_userlist.SetItemText(i, 0, nameList[i]);
			dlg->m_userlist.SetItemText(i, 1, IPList[i]);
		}
	}
}

void SerCtrl::DoOffLine(std::vector<CString> nameList, std::vector<CString> IPList)
{
	dlg->m_userlist.DeleteAllItems();

	for (unsigned int i = 0; i < nameList.size(); i++) {
		dlg->m_userlist.InsertItem(i,_T(""));
		dlg->m_userlist.SetItemText(i, 0, nameList[i]);
		dlg->m_userlist.SetItemText(i, 1, IPList[i]);
	}
}

bool SerCtrl::DoQuary(CString name, CString pwd)
{
	if (mAdo == nullptr) {
		mAdo = new Adosql;
		mAdo->OnInitADOConn();
	}

	return mAdo->queryClient(name, pwd);
}

void SerCtrl::DoProgress(CString name[], short PID[], int num)
{
	dlg->m_list.DeleteAllItems();

	for (int i = 0; i < num; i++) {
		dlg->m_list.InsertItem(i, _T(""));
		dlg->m_list.SetItemText(i, 0, name[i]);
		CString ss; ss.Format(_T("%d"), PID[i]);
		dlg->m_list.SetItemText(i, 1, ss);
	}
}

void SerCtrl::DoActivate(CString name, CString IP)
{
	dlg->setCurrIP(IP);
	dlg->CurrUserName = CString("当前用户:") + name;
	dlg->UpdateData(FALSE);
}

SerCtrl::~SerCtrl()
{
	delete mAdo;
}
