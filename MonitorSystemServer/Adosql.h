#pragma once
#include"stdafx.h"
class Adosql
{
public:
	Adosql();
	~Adosql();

	_ConnectionPtr m_pConnection; //Êý¾Ý¿â
	_RecordsetPtr m_pRecordset; //ÃüÁî
	_CommandPtr m_pCommand; // ¼ÇÂ¼
	void OnInitADOConn();
	void ExitConnect();
};

