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
		BPowerM::ReSetWindows(EWX_SHUTDOWN, true);//关机  
		break;
	case REBOOT:
		BPowerM::ReSetWindows(EWX_REBOOT, true);//重启  
		break;
	case LOOK:
		SetHook();
		MessageBox(NULL,TEXT("你已经被管理员锁定！请联系管理员解锁！"), TEXT("警告!"), MB_ICONWARNING | MB_SYSTEMMODAL);
		break;
	case UNLOOK:
		UnHook();
		MessageBox(NULL, TEXT("你已经被管理员解锁！"), TEXT("警告!"), MB_ICONWARNING | MB_SYSTEMMODAL);
		break;
	case STOP:
		dlg->stopJpeg();
		break;
	case RESUME:
		dlg->startJpeg();
		break;
	case USER_INFO://待定

		break;
	case PROGRESS://待定

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
