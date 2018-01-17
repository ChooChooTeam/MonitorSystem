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
	//MyTODO: ע��,���ߵ�ͬʱ��Ҫ֪ͨ���µ�ǰUI
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

bool SerCtrl::DoQuary(CString name, CString pwd)
{
	if (mAdo == nullptr) {
		mAdo = new Adosql;
	}

	return mAdo->queryClient(name, pwd);
}

void SerCtrl::DoQuaryReturn(bool rtn)
{
	// �˴�ִ�з��ؽ��
}


SerCtrl::~SerCtrl()
{
	delete mAdo;
}
