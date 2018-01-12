// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemClient.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
//#include "CEdit.h"

// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_REGISTER, pParent)
{
	bytes = 0;
}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_EDIT_USERNAME, username);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_EN_UPDATE(IDC_EDIT_USERNAME, &CRegisterDlg::OnEnUpdateEditUsername)
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(16);

		return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE

}


void CRegisterDlg::OnEnUpdateEditUsername()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	const int m_maxTxtLen = 16; //16个字节

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	CString strVal;
	pEdit->GetWindowText(strVal);
	int a = CStringA(strVal).GetLength();
	 
	if (a - bytes >= 2)  //中文字符点两个字节,判断条件
	{
		MessageBox(_T("注册用户名不可含有中文,请重新输入"));

		CString strtemp;
		strtemp = strVal.Left(bytes);  //清除中文字符
		pEdit->SetWindowText(strtemp);

		int l = pEdit->GetWindowTextLength();
		pEdit->SetSel(l, l, FALSE); //将焦点放到句尾
		pEdit->SetFocus();
	}


   pEdit->GetWindowText(strVal);
   bytes= CStringA(strVal).GetLength();

  // TODO:  在此添加控件通知处理程序代码
}


