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
};

