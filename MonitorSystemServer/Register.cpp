// Register.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "Register.h"
#include "afxdialogex.h"
#include "Adosql.h"

// Register 对话框

IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_REGISTER, pParent)
{

}

Register::~Register()
{
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE, combox);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &Register::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Register::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Register 消息处理程序


void Register::OnBnClickedButtonRegister()
{
	// TODO: 在此添加控件通知处理程序代码

	//判断数据库中是否有相同的用户名：


	//获得控件的值
	CEdit* pass = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* dpass = (CEdit*)GetDlgItem(IDC_EDIT3);
	CEdit* user = (CEdit *)GetDlgItem(IDC_EDIT1);
	CComboBox * box= (CComboBox *)GetDlgItem(IDC_TYPE);

	int len;
	CString username, password, dpassword, type; //名字、密码、身份

	//判断是否用户名和密码是否为空,两次密码是否一致
	len = user->GetWindowTextLengthW();
	user->GetWindowText(username);
	pass->GetWindowText(password);
	box->GetWindowText(type);
	dpass->GetWindowText(dpassword);


	if (password.GetLength() == 0 || len == 0)
	{
		MessageBox(_T(" 用户名和密码不可为空!"), _T("注册失败")); return;
	}
	if (password != dpassword || password.GetLength() == 0)
	{
		MessageBox(_T("  两次密码不一致!"), _T("注册失败")); return;
	}

	//插入用户名、密码到数据库中：
	//MessageBox(username);
	//MessageBox( password);
    //MessageBox( type);

	//if (type = _T("用户"))
		sql.insertClient(username, password);
	//else
		//sql.insertAdmin(username, password);
	  


}


BOOL Register::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//获取控件窗口指针  
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:    //按下回车响应注册按钮 
			Register::OnBnClickedButtonRegister();
			return TRUE;
		}
	}
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);

	if ((GetFocus() == pEdit1) && (pMsg->message == WM_CHAR))//如果焦点在edit_username的控件上
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


BOOL Register::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	sql.OnInitADOConn();

	CEdit * name = ((CEdit*)GetDlgItem(IDC_EDIT1));
	name->SetLimitText(16);  //最多十六个字符

	CFont font;
	font.CreatePointFont(110, _T("宋体"));
	GetDlgItem(IDC_STATIC1)->SetFont(&font);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	GetDlgItem(IDC_STATIC3)->SetFont(&font);
	GetDlgItem(IDC_STATIC4)->SetFont(&font);

	CFont *pFont = new CFont; //创建一个指向新字体类型的指针pFont
	LOGFONT LogFont;
	lstrcpy((LPWSTR)LogFont.lfFaceName, (LPWSTR)"Arial");

	LogFont.lfWeight = 500;
	LogFont.lfWidth = 10;
	LogFont.lfHeight = 20;
	LogFont.lfEscapement = 0;
	LogFont.lfUnderline = FALSE;
	LogFont.lfItalic = FALSE;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfCharSet = GB2312_CHARSET; //以上参数好像一个都不能少

	pFont->CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_EDIT1)->SetFont(pFont);
	GetDlgItem(IDC_EDIT2)->SetFont(pFont);
	GetDlgItem(IDC_EDIT3)->SetFont(pFont);
	GetDlgItem(IDC_TYPE)->SetFont(pFont);

	combox.AddString(_T("用户"));
	combox.AddString(_T("管理员"));
	combox.SetCurSel(0);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Register::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//取消的响应
	CEdit* pass = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* dpass = (CEdit*)GetDlgItem(IDC_EDIT3);
	CEdit* user = (CEdit *)GetDlgItem(IDC_EDIT1);
	CComboBox * box = (CComboBox *)GetDlgItem(IDC_TYPE);
	pass->SetWindowText(_T(""));
	dpass->SetWindowText(_T(""));
	user->SetWindowText(_T(""));

}
