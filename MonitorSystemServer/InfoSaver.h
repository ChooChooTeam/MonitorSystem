#pragma once
class InfoSaver
{
public:
	static bool SaveJPEG(char* jpeg,int len,CString filename);
	static bool SaveProgress(CString name[],short PID[] ,int num,CString filename);
};

