#include "stdafx.h"
#include "Controler.h"
#include "BPowerM.h"
#include "BProcessM.h"
#include "BComInfo.h"
#include "BScreenM.h"
#pragma comment(lib, "KeyboardHook.lib")
_declspec(dllimport) void SetHook(void);
_declspec(dllimport)	void UnHook(void);


Controler::Controler(CDIALOG1 * dlg)
{
	this->dlg = dlg;
}

void Controler::DoCmd(WsOp op)
{
	switch (op)
	{
	case SHUTDOWN:
		BPowerM::ReSetWindows(EWX_SHUTDOWN, true);//�ػ�  
		break;
	case REBOOT:
		BPowerM::ReSetWindows(EWX_REBOOT, true);//����  
		break;
	case LOOK:
		SetHook();
		MessageBox(NULL,TEXT("���Ѿ�������Ա����������ϵ����Ա������"), TEXT("����!"), MB_ICONWARNING | MB_SYSTEMMODAL);
		break;
	case UNLOOK:
		UnHook();
		MessageBox(NULL, TEXT("���Ѿ�������Ա������"), TEXT("����!"), MB_ICONWARNING | MB_SYSTEMMODAL);
		break;
	case STOP:
		dlg->stopJpeg();
		break;
	case RESUME:
		dlg->startJpeg();
		break;
	case USER_INFO://����

		break;
	case PROGRESS://����

		break;
	default:
		break;
	}

}

void Controler::DoJPG(char * jpg, int size)
{
}

void Controler::DoOnLine(std::vector<CString> nameList)
{
}

void Controler::DoOffLine(std::vector<CString> nameList, CString offlineName)
{
}


Controler::~Controler()
{
}
