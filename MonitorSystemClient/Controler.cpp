#include "stdafx.h"
#include "Controler.h"


Controler::Controler()
{
}

void Controler::DoCmd(WsOp op)
{
	switch (op)
	{
	case SHUTDOWN:
		break;
	case REBOOT:
		break;
	case LOOK:
		break;
	case UNLOOK:
		break;
	case STOP:
		break;
	case RESUME:
		break;
	case USER_INFO:
		break;
	case PROGRESS:
		break;
	case JPGE:
		DWORD threadID;
		b = new BScreenM(this->socket);
		b->runThreading();
		
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
