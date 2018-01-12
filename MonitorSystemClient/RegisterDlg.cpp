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

	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(16);  //最多十六个字符

		return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE

}

BOOL CRegisterDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//获取控件窗口指针  
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	
	if ((GetFocus() == pEdit1 ) && (pMsg->message == WM_CHAR))
	{
		//只允许数字和字母
		if ((pMsg->wParam <= '9' && pMsg->wParam >= '0') || (pMsg->wParam >= 'a' && pMsg->wParam <= 'z') || (pMsg->wParam >= 'A' && pMsg->wParam <= 'Z'))
		{
			return 0;

		}
		else if (pMsg->wParam == 0x08 || pMsg->wParam == 0x10)  //接受Backspace和delete键  
		{
			return 0;
		}
		else
		{
			//响应标签页切换的快捷键  
			switch (pMsg->wParam)
			{
			case 'q':
			case 'Q':
			case 'w':
			case 'W':
			case 'e':
			case 'E':
			case 'r':
			case 'R':
			case 't':
			case 'T':
			case 'y':
			case 'Y':
			case 'u':
			case 'U':
			case 'i':
			case 'I':
			case 'o':
			case 'O':

			CWnd * pParent = GetParent();
			pParent->SetFocus();
			return 0;
			}
		
		}
		
			MessageBox(_T("用户名只能含有大小写英文字母和数字!"), _T("提示"));
			return 1;		
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
