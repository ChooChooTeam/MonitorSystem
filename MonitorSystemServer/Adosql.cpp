#include "stdafx.h"
#include "Adosql.h"
#include<afx.h>
#include<string.h>
#include<afxpriv.h>

char strsql[1024];
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
		_bstr_t strConnect = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=UserInfo;Data Source=LAPTOP-LTK0NPPQ";
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		AfxMessageBox(_T("数据库连接成功"));
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("数据库连接失败"));
	}
}
void Adosql::ExitConnect()
{
}

/*
核对管理员身份
输入1：管理员帐户
输入2：管理员密码
输出：bool值，true为身份确认，否则帐户或密码错误
*/
bool Adosql::queryAdmin(CString str1,CString str2)
{
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pCommand->ActiveConnection = m_pConnection;

	USES_CONVERSION;
	sprintf(strsql, "SELECT * FROM Admin WHERE AdminName = '%s'",T2A(str1));
	m_pCommand->CommandText = strsql; //通过pCmd对象访问数据库

	m_pRecordset = m_pCommand->Execute(NULL, NULL, adCmdText);
	while (!m_pRecordset->adoEOF)
	{
		if (str2.Compare(CString(m_pRecordset->GetCollect("AdminPWord")).TrimRight())==0)
		{
			m_pRecordset->Close();
			return true;
		}
		

		m_pRecordset->MoveNext(); //下移一个
	}
	m_pRecordset->Close();
	return false;
}

/*
核对用户身份
输入1：用户帐户
输入2：用户密码
输出：bool值，true为身份确认，否则帐户或密码错误
*/
bool Adosql::queryClient(CString str1, CString str2)
{
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pRecordset.CreateInstance(__uuidof(Record));
	m_pCommand->ActiveConnection = m_pConnection;

	USES_CONVERSION;
	sprintf(strsql, "SELECT * FROM Client WHERE UserName = '%s'", T2A(str1));
	m_pCommand->CommandText = strsql; //通过pCmd对象访问数据库

	m_pRecordset = m_pCommand->Execute(NULL, NULL, adCmdText);
	while (!m_pRecordset->adoEOF)
	{
		if (str2.Compare(CString(m_pRecordset->GetCollect("ClientPwd")).TrimRight()) == 0)
		{
			
			m_pRecordset->Close();
			return true;
		}

		m_pRecordset->MoveNext(); //下移一个
	}
	m_pRecordset->Close();
	return false;
}

/*
添加一个管理员身份
输入1：管理员帐户
输入2：管理员密码
输出：bool值，若为true则添加成功，否则失败
*/
bool Adosql::insertAdmin(CString str1, CString str2)
{
	USES_CONVERSION;
	try
	{

		m_pRecordset->Open("SELECT * FROM Admin ", m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockPessimistic, adCmdText);
	}
	catch(_com_error &e)
	{
		CString str;
		str.Format(e.Description());
		AfxMessageBox((str));
	}
	
	try
	{
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("AdminName", T2A(str1));
		m_pRecordset->PutCollect("AdminPword", T2A(str2));


		m_pRecordset->Update();
		m_pRecordset->Close();
		return true;

	}
	catch (_com_error &e)
	{
		/*CString str;
		str.Format(e.Description());
		AfxMessageBox((str));*/
		
		m_pRecordset->Close();
		/*AfxMessageBox(e.Description());*/
		return false;
	}
	
	
	
}

/*
添加一个用户身份
输入1：用户帐户
输入2：用户码
输出：bool值，若为true则添加成功，否则失败
*/
bool Adosql::insertClient(CString str1, CString str2)
{
	USES_CONVERSION;
	m_pRecordset.CreateInstance(__uuidof(Recordset));


	m_pRecordset->Open("SELECT * FROM Client ", m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockPessimistic, adCmdText);


	try
	{
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("UserName", T2A(str1));
		m_pRecordset->PutCollect("ClientPwd", T2A(str2));
		m_pRecordset->Update();
		m_pRecordset->Close();

	}
	catch (_com_error &e)
	{
		m_pRecordset->Close();
		return false;
	}

	return true;
}

/*
修改管理员密码
输入1：待修改的管理员帐户
输入2：修改后密码
输出：bool值，若为true则修改成功，否则修改失败
*/
bool Adosql::updateAdmin(CString str1,CString str2)
{
	USES_CONVERSION;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	m_pRecordset->Open("SELECT * FROM Admin ", m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockPessimistic, adCmdText);

	while (!m_pRecordset->adoEOF)
	{
		if (str1.Compare(CString(m_pRecordset->GetCollect("AdminName")).TrimRight()) == 0)
		{
			m_pRecordset->PutCollect("AdminPword", T2A(str2));
			m_pRecordset->Update();


			m_pRecordset->Close();
			
			return true;
		}

		m_pRecordset->MoveNext(); //下移一个
	}

	m_pRecordset->Close();
	return false;
}

/*
修改用户密码
输入1：待修改的用户帐户
输入2：修改后密码
输出：bool值，若为true则修改成功，否则修改失败
*/
bool Adosql::updateClient(CString str1, CString str2)
{
	USES_CONVERSION;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	m_pRecordset->Open("SELECT * FROM Client ", m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockPessimistic, adCmdText);

	while (!m_pRecordset->adoEOF)
	{
		if (str1.Compare(CString(m_pRecordset->GetCollect("ClientName")).TrimRight()) == 0)
		{
			m_pRecordset->PutCollect("ClientPwd", T2A(str2));
			m_pRecordset->Update();
			m_pRecordset->Close();

			return true;
		}

		m_pRecordset->MoveNext(); //下移一个
	}

	m_pRecordset->Close();
	return false;
}


/*
删除一个管理员信息
输入：管理员帐户
输出：bool，若为true则删除成功，否则删除失败
*/
bool Adosql::deleteAdmin(CString str)
{
	USES_CONVERSION;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	m_pRecordset->Open("SELECT * FROM Admin ", m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockPessimistic, adCmdText);
	while (!m_pRecordset->adoEOF)
	{
		if (str.Compare(CString(m_pRecordset->GetCollect("AdminName")).TrimRight()) == 0)
		{
			m_pRecordset->Delete(adAffectCurrent);
			m_pRecordset->Update();


			m_pRecordset->Close();

			return true;
		}

		m_pRecordset->MoveNext(); //下移一个
	}

	m_pRecordset->Close();
	return false;
}


/*
删除一个用户信息
输入：用户帐户
输出：bool，若为true则删除成功，否则删除失败
*/
bool Adosql::deleteClient(CString str)
{
	USES_CONVERSION;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	m_pRecordset->Open("SELECT * FROM Client ", m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockPessimistic, adCmdText);
	while (!m_pRecordset->adoEOF)
	{
		if (str.Compare(CString(m_pRecordset->GetCollect("ClientName")).TrimRight()) == 0)
		{
			m_pRecordset->Delete(adAffectCurrent);
			m_pRecordset->Update();


			m_pRecordset->Close();

			return true;
		}

		m_pRecordset->MoveNext(); //下移一个
	}

	m_pRecordset->Close();
	return false;
}