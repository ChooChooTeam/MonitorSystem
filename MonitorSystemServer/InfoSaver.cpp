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

