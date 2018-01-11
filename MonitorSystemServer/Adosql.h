#pragma once
#include"stdafx.h"
class Adosql
{
public:
	Adosql();
	~Adosql();

	_ConnectionPtr m_pConnection; //���ݿ�
	_RecordsetPtr m_pRecordset; //����
	_CommandPtr m_pCommand; // ��¼
	void OnInitADOConn();
	void ExitConnect();
	bool queryAdmin(CString str1, CString str2);
	bool queryClient(CString str1, CString str2);
	bool insertAdmin(CString str1, CString str2);
	bool insertClient(CString str1, CString str2);
	bool updateAdmin(CString str1, CString str2);
	bool updateClient(CString str1, CString str2);
	bool deleteAdmin(CString str);
	bool deleteClient(CString str);
};

