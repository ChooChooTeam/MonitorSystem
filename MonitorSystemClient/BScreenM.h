#pragma once
#include "DIALOG1.h"
// 由调用方第二次判断到他的指针不为NULL时销毁？？？
#include "../MonitorSystemServer/WrkSocket.h"
class BScreenM
{
	//for screensend
	int speed ;
	DWORD threadID;
	
	HANDLE static g_hMutex;//a mutex for runAble
 	bool static runAble;

	static void setrunAble(bool b) {
		//请求获得一个互斥量锁
		WaitForSingleObject(g_hMutex, INFINITE);
		bool runAble = b;
		//释放互斥量锁
		ReleaseMutex(g_hMutex);
	}
	
public:
	void runOnce();
	CDIALOG1 * dlg = NULL;
	static bool getrunAble() {
		bool b;
		//请求获得一个互斥量锁
		WaitForSingleObject(g_hMutex, INFINITE);
		b = runAble;
		//释放互斥量锁
		ReleaseMutex(g_hMutex);
		return b;
	}
	BScreenM(CDIALOG1 *dlg) {
		this->dlg = dlg;
		speed = 30;
		g_hMutex = CreateMutex(NULL, FALSE, NULL);
		setrunAble(true);
	};
	void stopThreading() {
		setrunAble(false);
	}

	HANDLE runThreading();
		
	~BScreenM();
};

