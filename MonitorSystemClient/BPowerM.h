#pragma once
#pragma warning(disable: 4996)       
#define EWX_SETPOWER                  0x00000100
class BPowerM
{
public:
	BPowerM();
	static BOOL  ReSetWindows(DWORD dwFlags, BOOL bForce)
	{
		//�������Ƿ���ȷ  
		if (dwFlags != EWX_LOGOFF && dwFlags != EWX_REBOOT && dwFlags != EWX_SHUTDOWN&& dwFlags != EWX_SETPOWER)
			return FALSE;
		//���ϵͳ�İ汾��Ϣ�������Ǻ���ȷ���Ƿ���Ҫ����ϵͳȨ��  
		OSVERSIONINFO osvi = { 0 };
		//��ò����Ĵ�С�����ṩ��GetVersionEx���ж�����һ���°汾��OSVERSIONINFO�����Ǿɰ汾��  
		//�°汾��OSVERSIONINFOEX������汾  
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (! GetVersionEx(&osvi))
		{
			return FALSE;
		}
		//������ϵͳ�İ汾�������NT���͵�ϵͳ����Ҫ����ϵͳȨ��  
		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			EnableShutDownPriv();  
		}
		if (dwFlags == EWX_SETPOWER) {
			return SetSystemPowerState(TRUE, TRUE);

		}
		//�ж��Ƿ���ǿ�ƹػ���ǿ�ƹر�ϵͳ���̡�  
		dwFlags |= (bForce != FALSE) ? EWX_FORCE : EWX_FORCEIFHUNG;
		//����API  
		
		return ExitWindowsEx(dwFlags, 0);
	}

	//����һ��ͨ�õ�����Ȩ�޺����������Ҫ��������Ȩ��  
	//����LookupPrivilegeValue�ĵڶ�������SE_SHUTDOWN_NAME������  
	static BOOL  EnableShutDownPriv()
	{
		HANDLE hToken = NULL;
		TOKEN_PRIVILEGES tkp = { 0 };
		//�򿪵�ǰ�����Ȩ������  
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		{
			return FALSE;
		}
		//���ĳһ�ض�Ȩ�޵�Ȩ�ޱ�ʶLUID��������tkp��  
		if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
		{
			CloseHandle(hToken);
			return FALSE;
		}
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		//����AdjustTokenPrivileges������������Ҫ��ϵͳȨ��  
		if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
		{
			CloseHandle(hToken);
			return FALSE;
		}
		return TRUE;
	}
	~BPowerM();
};

