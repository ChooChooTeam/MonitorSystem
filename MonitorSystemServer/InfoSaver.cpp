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
		file.SeekToBegin(); //�����ļ���ͷ   
		file.Write("/xff/xfe", 2); //Unicode�����txt�ļ���0xff��0xfe�����ֽ���Ϊ��ͷ��ǡ�  

		for (int i = 0; i < num; i++) {
			file.Write(name[i], name[i].GetLength() * 2); //д��ʵ������ 
			file.Write(_T(" "), 2);
			file.Write(&PID[i], sizeof(short));
			file.Write(_T("\n"), 2);
		}
		file.Close(); //�ر��ļ�   
		return true;
	}
	else {
		return false;
	}



	
}


