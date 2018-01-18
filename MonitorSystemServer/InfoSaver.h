#pragma once
class InfoSaver
{
public:
	InfoSaver();
	bool SaveJPEG(char* jpeg,int len,CString filename);
	bool SaveProgress(CString name[]);
	~InfoSaver();
};

