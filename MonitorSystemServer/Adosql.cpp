#include "stdafx.h"
#include "Adosql.h"
#include<afx.h>

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
		_bstr_t strConnect = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;User ID=Windows身份验证;Initial Catalog=UserInfo;Data Source=DESKTOP-90Q3P13";
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
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	::CoUninitialize();
}

/*
核对管理员身份
输入1：管理员帐户
输入2：管理员密码
输出：bool值，true为身份确认，否则帐户或密码错误
*/
bool Adosql::queryAdmin(CString str1,CString str2)
{
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_CommandPtr pCmd(__uuidof(Command)); //实例化一个Command对象pCmd
	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	sprintf(strsql, "SELECT * FROM Admin WHERE AdminName = '%s'", (char*)str1.GetBuffer(str1.GetLength()));
	
	pCmd->CommandText = strsql; //通过pCmd对象访问数据库
	pRst = pCmd->Execute(NULL, NULL, adCmdText);
	while (!pRst->adoEOF)
	{
		
		if (str2 == pRst->GetCollect("AdminPWord"))
		{
			pRst->Close(); //关闭对象
			pConn->Close();
			pCmd.Release(); //释放对象
			pRst.Release();
			pConn.Release();
			CoUninitialize(); //卸载COM组件
			return true;
		}
		
		//把数据库中学号这列的内容放入IDC_LIST1的LIST控件中
		pRst->MoveNext(); //下移一个
	}
	pRst->Close(); //关闭对象
	pConn->Close();
	pCmd.Release(); //释放对象
	pRst.Release();
	pConn.Release();
	CoUninitialize(); //卸载COM组件
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
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_CommandPtr pCmd(__uuidof(Command)); //实例化一个Command对象pCmd
	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	sprintf(strsql, "SELECT * FROM Client WHERE UserName = '%s'", (char*)str1.GetBuffer());
	pCmd->CommandText = strsql; //通过pCmd对象访问数据库
	pRst = pCmd->Execute(NULL, NULL, adCmdText);
	while (!pRst->adoEOF)
	{

		if (str2 == pRst->GetCollect("ClientPwd"))
		{
			pRst->Close(); //关闭对象
			pConn->Close();
			pCmd.Release(); //释放对象
			pRst.Release();
			pConn.Release();
			CoUninitialize(); //卸载COM组件
			return true;
		}

		pRst->MoveNext(); //下移一个
	}
	pRst->Close(); //关闭对象
	pConn->Close();
	pCmd.Release(); //释放对象
	pRst.Release();
	pConn.Release();
	CoUninitialize(); //卸载COM组件
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
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_variant_t RecordsAffected; //申请一个_variant_t类型的的变量

	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	pConn->Open("", "", "", adConnectUnspecified);
	sprintf(strsql, "INSERT INTO Admin  VALUES('%s', '%s')", (char*)str1.GetBuffer(),(char*)str2.GetBuffer());
	try
	{
		pRst = pConn->Execute(strsql, &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		pConn->Close();
		pRst.Release();
		pConn.Release();
		CoUninitialize();
		return false;
	}
	
	pConn->Close();
	pRst.Release();
	pConn.Release();
	CoUninitialize();
	return true;
}

/*
添加一个用户身份
输入1：用户帐户
输入2：用户码
输出：bool值，若为true则添加成功，否则失败
*/
bool Adosql::insertClient(CString str1, CString str2)
{
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_variant_t RecordsAffected; //申请一个_variant_t类型的的变量

	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	pConn->Open("", "", "", adConnectUnspecified);
	sprintf(strsql, "INSERT INTO  Client VALUES('%s', '%s')", (char*)str1.GetBuffer(), (char*)str2.GetBuffer());
	try
	{
		pRst = pConn->Execute(strsql, &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		pConn->Close();
		pRst.Release();
		pConn.Release();
		CoUninitialize();
		return false;
	}

	pConn->Close();
	pRst.Release();
	pConn.Release();
	CoUninitialize();
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
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_variant_t RecordsAffected; //申请一个_variant_t类型的的变量

	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	pConn->Open("", "", "", adConnectUnspecified);
	sprintf(strsql, "UPDATE Admin SET AdminPWord='%s' WHERE AdminName='%s'", (char*)str2.GetBuffer(), (char*)str1.GetBuffer());
	try
	{
		pRst = pConn->Execute(strsql, &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		pConn->Close();
		pRst.Release();
		pConn.Release();
		CoUninitialize();
		return false;
	}

	pConn->Close();
	pRst.Release();
	pConn.Release();
	CoUninitialize();
	return true;
}

/*
修改用户密码
输入1：待修改的用户帐户
输入2：修改后密码
输出：bool值，若为true则修改成功，否则修改失败
*/
bool Adosql::updateClient(CString str1, CString str2)
{
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_variant_t RecordsAffected; //申请一个_variant_t类型的的变量

	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	pConn->Open("", "", "", adConnectUnspecified);
	sprintf(strsql, "UPDATE Admin SET ClientPwd='%s' WHERE ClientName='%s'", (char*)str2.GetBuffer(), (char*)str1.GetBuffer());
	try
	{
		pRst = pConn->Execute(strsql, &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		pConn->Close();
		pRst.Release();
		pConn.Release();
		CoUninitialize();
		return false;
	}

	pConn->Close();
	pRst.Release();
	pConn.Release();
	CoUninitialize();
	return true;
}


/*
删除一个管理员信息
输入：管理员帐户
输出：bool，若为true则删除成功，否则删除失败
*/
bool Adosql::deleteAdmin(CString str)
{
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_variant_t RecordsAffected; //申请一个_variant_t类型的的变量

	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	pConn->Open("", "", "", adConnectUnspecified);
	sprintf(strsql, "DELETE FROM Admin WHERE AdminName='%s'", (char*)str.GetBuffer());

	try
	{
		pRst = pConn->Execute(strsql, &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		pConn->Close();
		pRst.Release();
		pConn.Release();
		CoUninitialize();
		return false;
	}

	pConn->Close();
	pRst.Release();
	pConn.Release();
	CoUninitialize();
	return true;
}


/*
删除一个用户信息
输入：用户帐户
输出：bool，若为true则删除成功，否则删除失败
*/
bool Adosql::deleteClient(CString str)
{
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_variant_t RecordsAffected; //申请一个_variant_t类型的的变量

	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	pConn->Open("", "", "", adConnectUnspecified);
	sprintf(strsql, "DELETE FROM Client WHERE AdminName='%s'", (char*)str.GetBuffer());

	try
	{
		pRst = pConn->Execute(strsql, &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		pConn->Close();
		pRst.Release();
		pConn.Release();
		CoUninitialize();
		return false;
	}

	pConn->Close();
	pRst.Release();
	pConn.Release();
	CoUninitialize();
	return true;
}