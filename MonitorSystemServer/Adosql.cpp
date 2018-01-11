#include "stdafx.h"
#include "Adosql.h"
#include<afx.h>

char* strsql;
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
		_bstr_t strConnect = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;User ID=sa;Password=123;Initial Catalog=UserInfo;Data Source=.";
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		AfxMessageBox(_T("连接成功"));
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("连接失败"));
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
bool queryAdmin(CString str1,CString str2)
{
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_CommandPtr pCmd(__uuidof(Command)); //实例化一个Command对象pCmd
	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	sprintf(strsql, "SELECT * FROM Admin WHERE AdminName = '%s'", str1);
	
	pCmd->CommandText = strsql; //通过pCmd对象访问数据库
	pRst = pCmd->Execute(NULL, NULL, adCmdText);
	while (!pRst->rsEOF)
	{
		
		if (str2 == pRst->GetCollect("AdminName"))
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
bool queryClient(CString str1, CString str2)
{
	CoInitialize(NULL); //初始化COM组件
	_ConnectionPtr pConn(__uuidof(Connection)); //实例化一个connection对象pConn
	_RecordsetPtr pRst(__uuidof(Recordset)); //实例化一个Recordset对象pRst
	_CommandPtr pCmd(__uuidof(Command)); //实例化一个Command对象pCmd
	pConn->ConnectionString = "Provider=MIcrosoft.Jet.OLEDB.4.0;Data source=UserInfo.mdb";
	sprintf(strsql, "SELECT * FROM Client WHERE AdminName = '%s'", str1);

	pCmd->CommandText = strsql; //通过pCmd对象访问数据库
	pRst = pCmd->Execute(NULL, NULL, adCmdText);
	while (!pRst->rsEOF)
	{

		if (str2 == pRst->GetCollect("AdminName"))
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