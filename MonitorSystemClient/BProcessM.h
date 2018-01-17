#pragma once
#include <TlHelp32.h>//声明快照函数头文件 
#include "Psapi.h"
#pragma warning(disable: 4996)   
class BProcessM
{
public:
	BProcessM();
	static void showAllProcess() {
		OSVERSIONINFO osvi = { 0 };
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx(&osvi))
		{
			return ;
		}
		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			GetDebugPriv();
		}
		


		PROCESSENTRY32W pe32;
		pe32.dwSize = sizeof(pe32);
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			#ifdef _DEBUG
				OutputDebugString(_T("CreateToolhelp32Snapshot调用失败!\n"));
			#endif
			return;
		}
		//遍历进程快照。轮流显示每个进程的信息  
		CString strPrcNameID;
		BOOL bMore = ::Process32First(hProcessSnap, &pe32);
		while (bMore)
		{
			strPrcNameID.Format(L"进程名称：%s，ID：%u\n", pe32.szExeFile, pe32.th32ProcessID);
#ifdef _DEBUG
			OutputDebugString(strPrcNameID);
#endif
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
		//清除snapshot对象  
		::CloseHandle(hProcessSnap);
	
	}
	//查找指定进程  
	static DWORD FindProcess(TCHAR *strProcessName)
	{
		DWORD aProcesses[1024], cbNeeded, cbMNeeded;
		HMODULE hMods[1024];
		HANDLE hProcess;
		TCHAR szProcessName[MAX_PATH];
		OSVERSIONINFO osvi = { 0 };
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx(&osvi))
		{
			return false;
		}
		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			GetDebugPriv();
		}

		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded ))  return 0;
		for (int i = 0; i< (int)(cbNeeded  / sizeof(DWORD)); i++)
		{
			hProcess  = OpenProcess(PROCESS_QUERY_INFORMATION  | PROCESS_VM_READ, FALSE, aProcesses[i]);
			EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
			GetModuleFileNameEx(hProcess, hMods[0], szProcessName, sizeof(szProcessName));

			CString strPrcFullName(szProcessName);
			CString strPrcName(strProcessName);
			if (_tcsstr(strPrcFullName, strPrcName) || _tcsstr(strPrcFullName, strPrcName.MakeLower()))
			{
				CString strNameFull;
				strNameFull.Format(_T("Process full name：\n%s;"), szProcessName);
				//AfxMessageBox(strNameFull);  
				return(aProcesses[i]);
			}
		}

		return 0;
	}

	// 此函数利用上面的 FindProcess 函数获得你的目标进程的ID  
	// 用WIN API OpenPorcess 获得此进程的句柄，再以TerminateProcess强制结束这个进程  
	static VOID KillProcess(TCHAR *strProcessName)
	{
		OSVERSIONINFO osvi = { 0 };
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx(&osvi))
		{
			return;
		}
		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			GetDebugPriv();
		}

		// When the all operation fail this function terminate the "winlogon" Process for force exit the system.  
		HANDLE hYourTargetProcess  = OpenProcess(PROCESS_QUERY_INFORMATION  |   // Required by Alpha  
			PROCESS_CREATE_THREAD      |   // For CreateRemoteThread  
			PROCESS_VM_OPERATION       |   // For VirtualAllocEx/VirtualFreeEx  
			PROCESS_VM_WRITE           |  // For WriteProcessMemory  
			PROCESS_TERMINATE,           //Required to terminate a process using TerminateProcess function  
			FALSE, FindProcess(strProcessName));

		if (hYourTargetProcess  == NULL) 
		{
			DWORD ulErrCode  = GetLastError();
			CString strError;
			strError.Format(L"OpenProcess failed,error code:%ld", ulErrCode);
			AfxMessageBox(strError);
		}

		BOOL result  = TerminateProcess(hYourTargetProcess, 0);
		if (!result)
		{
			DWORD ulErrCode  = GetLastError();
			CString strError;
			strError.Format(L"TerminateProcess failed,error code:%ld", ulErrCode);
			AfxMessageBox(strError);
		}
		return;
	}

	// 在 Windows NT/2000/XP 中可能因权限不够导致以上函数失败  
	// 如以　System 权限运行的系统进程，服务进程用本函数取得　debug 权限即可,Winlogon.exe 都可以终止哦 :)  
	static BOOL GetDebugPriv()
	{
		HANDLE hToken;
		LUID sedebugnameValue;
		TOKEN_PRIVILEGES tkp;

		if (!OpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES  | TOKEN_QUERY, &hToken ))
		{
			return FALSE;
		}


		if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue ))
		{
			CloseHandle(hToken );
			return FALSE;
		}

		tkp.PrivilegeCount  = 1;
		tkp.Privileges[0].Luid  = sedebugnameValue;
		tkp.Privileges[0].Attributes  = SE_PRIVILEGE_ENABLED;

		if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ))
		{
			CloseHandle(hToken );
			return FALSE;
		}

		return TRUE;
	}
	~BProcessM();
};

