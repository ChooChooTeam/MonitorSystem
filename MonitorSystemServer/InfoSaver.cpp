#include "stdafx.h"
#include "InfoSaver.h"


InfoSaver::InfoSaver()
{

}

bool InfoSaver::SaveJPEG(char * jpeg, int len, CString filename)
{
	USES_CONVERSION;
	FILE* f;
	fopen_s(&f, T2A(filename), "w");

	int n = fwrite(jpeg, sizeof(char), len, f);

	fclose(f);

	return (n == len);
}


InfoSaver::~InfoSaver()
{
}
