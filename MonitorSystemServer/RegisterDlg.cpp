// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include"Adosql.h"


// RegisterDlg 对话框

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_REGISTER, pParent)
	, m_edit_AdminName(_T(""))
	, m_edit_AdminPwd(_T(""))
	, m_edit_AdminEndPwd(_T(""))
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_AdminName);
	DDV_MaxChars(pDX, m_edit_AdminName, 32);
	DDX_Text(pDX, IDC_EDIT2, m_edit_AdminPwd);
	DDV_MaxChars(pDX, m_edit_AdminPwd, 32);
	DDX_Text(pDX, IDC_EDIT3, m_edit_AdminEndPwd);
	DDV_MaxChars(pDX, m_edit_AdminEndPwd, 32);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &RegisterDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// RegisterDlg 消息处理程序


void RegisterDlg::OnBnClickedButtonRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	USES_CONVERSION;
	if (!strcmp(T2A(m_edit_AdminPwd), T2A(m_edit_AdminPwd)))
	{
		if (sql.insertAdmin(m_edit_AdminName, m_edit_AdminPwd))
		{
			MessageBox(_T("注册成功！"));
		}
		else
		{
			MessageBox(_T("注册失败！"));
		}
	}
	else
	{
		MessageBox(_T("两次输入密码不一致！"));
	}
}
