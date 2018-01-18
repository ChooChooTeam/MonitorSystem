#include "stdafx.h"
#include "InfoSaver.h"

bool InfoSaver::SaveJPEG(char * jpeg, int len, CString filename)
{
	USES_CONVERSION;
	FILE* f;
	_wfopen_s(&f, filename, _T("w"));
	int n = fwrite(jpeg, sizeof(char), len, f);

	fclose(f);

	return (n == len);
}

bool InfoSaver::SaveProgress(CString name[], short PID[], int num, CString filename)
{
	CFile file; 
	if (file.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyRead)){
		file.SeekToBegin(); //到达文件开头   
		file.Write("/xff/xfe", 2); //Unicode编码的txt文件以0xff、0xfe两个字节作为开头标记。  

		for (int i = 0; i < num; i++) {
			file.Write(name[i], name[i].GetLength() * 2); //写入实际数据 
			file.Write(_T(" "), 2);
			file.Write(&PID[i], sizeof(short));
			file.Write(_T("\n"), 2);
		}
		file.Close(); //关闭文件   
		return true;
	}
	else {
		return false;
	}



	
}


