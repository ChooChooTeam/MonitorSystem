#include "stdafx.h"
#include "Adosql.h"


Adosql::Adosql()
{
}


Adosql::~Adosql()
{
}

void Adosql::OnInitADOConn()
{
	::CoInitialize(NULL);
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		_bstr_t strConnect = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=UserInfo;Data Source=.";
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		AfxMessageBox(_T("���ӳɹ�"));
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("����ʧ��"));
	}
}
void Adosql::ExitConnect()
{
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	::CoUninitialize();
}
