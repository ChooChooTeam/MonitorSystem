#pragma once
#include "DIALOG1.h"
// �ɵ��÷��ڶ����жϵ�����ָ�벻ΪNULLʱ���٣�����
#include "../MonitorSystemServer/WrkSocket.h"
class BScreenM
{
	//for screensend
	int speed ;
	DWORD threadID;
	
	HANDLE static g_hMutex;//a mutex for runAble
 	bool static runAble;

	static void setrunAble(bool b) {
		//������һ����������
		WaitForSingleObject(g_hMutex, INFINITE);
		bool runAble = b;
		//�ͷŻ�������
		ReleaseMutex(g_hMutex);
	}
	
public:
	void runOnce();
	CDIALOG1 * dlg = NULL;
	static bool getrunAble() {
		bool b;
		//������һ����������
		WaitForSingleObject(g_hMutex, INFINITE);
		b = runAble;
		//�ͷŻ�������
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

