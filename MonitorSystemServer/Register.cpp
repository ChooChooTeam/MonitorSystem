// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "Register.h"
#include "afxdialogex.h"
#include "Adosql.h"

// Register �Ի���

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


// Register ��Ϣ�������


void Register::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ж����ݿ����Ƿ�����ͬ���û�����


	//��ÿؼ���ֵ
	CEdit* pass = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* dpass = (CEdit*)GetDlgItem(IDC_EDIT3);
	CEdit* user = (CEdit *)GetDlgItem(IDC_EDIT1);
	CComboBox * box= (CComboBox *)GetDlgItem(IDC_TYPE);

	int len;
	CString username, password, dpassword, type; //���֡����롢���

	//�ж��Ƿ��û����������Ƿ�Ϊ��,���������Ƿ�һ��
	len = user->GetWindowTextLengthW();
	user->GetWindowText(username);
	pass->GetWindowText(password);
	box->GetWindowText(type);
	dpass->GetWindowText(dpassword);


	if (password.GetLength() == 0 || len == 0)
	{
		MessageBox(_T(" �û��������벻��Ϊ��!"), _T("ע��ʧ��")); return;
	}
	if (password != dpassword || password.GetLength() == 0)
	{
		MessageBox(_T("  �������벻һ��!"), _T("ע��ʧ��")); return;
	}

	//�����û��������뵽���ݿ��У�
	//MessageBox(username);
	//MessageBox( password);
    //MessageBox( type);

	//if (type = _T("�û�"))
		sql.insertClient(username, password);
	//else
		//sql.insertAdmin(username, password);
	  


}


BOOL Register::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ȡ�ؼ�����ָ��  
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:    //���»س���Ӧע�ᰴť 
			Register::OnBnClickedButtonRegister();
			return TRUE;
		}
	}
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);

	if ((GetFocus() == pEdit1) && (pMsg->message == WM_CHAR))//���������edit_username�Ŀؼ���
	{
		//ֻ�������ֺ���ĸ
		if ((pMsg->wParam <= '9' && pMsg->wParam >= '0') || (pMsg->wParam >= 'a' && pMsg->wParam <= 'z') || (pMsg->wParam >= 'A' && pMsg->wParam <= 'Z'))
		{
			return 0;

		}
		else if (pMsg->wParam == 0x08 || pMsg->wParam == 0x10)  //����Backspace��delete��  
		{
			return 0;
		}
		else
		{
			//��Ӧ��ǩҳ�л��Ŀ�ݼ�  
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

		MessageBox(_T("�û���ֻ�ܺ��д�СдӢ����ĸ������!"), _T("��ʾ"));
		return 1;
	}



	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL Register::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	sql.OnInitADOConn();

	CEdit * name = ((CEdit*)GetDlgItem(IDC_EDIT1));
	name->SetLimitText(16);  //���ʮ�����ַ�

	CFont font;
	font.CreatePointFont(110, _T("����"));
	GetDlgItem(IDC_STATIC1)->SetFont(&font);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	GetDlgItem(IDC_STATIC3)->SetFont(&font);
	GetDlgItem(IDC_STATIC4)->SetFont(&font);

	CFont *pFont = new CFont; //����һ��ָ�����������͵�ָ��pFont
	LOGFONT LogFont;
	lstrcpy((LPWSTR)LogFont.lfFaceName, (LPWSTR)"Arial");

	LogFont.lfWeight = 500;
	LogFont.lfWidth = 10;
	LogFont.lfHeight = 20;
	LogFont.lfEscapement = 0;
	LogFont.lfUnderline = FALSE;
	LogFont.lfItalic = FALSE;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfCharSet = GB2312_CHARSET; //���ϲ�������һ����������

	pFont->CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_EDIT1)->SetFont(pFont);
	GetDlgItem(IDC_EDIT2)->SetFont(pFont);
	GetDlgItem(IDC_EDIT3)->SetFont(pFont);
	GetDlgItem(IDC_TYPE)->SetFont(pFont);

	combox.AddString(_T("�û�"));
	combox.AddString(_T("����Ա"));
	combox.SetCurSel(0);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Register::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ȡ������Ӧ
	CEdit* pass = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* dpass = (CEdit*)GetDlgItem(IDC_EDIT3);
	CEdit* user = (CEdit *)GetDlgItem(IDC_EDIT1);
	CComboBox * box = (CComboBox *)GetDlgItem(IDC_TYPE);
	pass->SetWindowText(_T(""));
	dpass->SetWindowText(_T(""));
	user->SetWindowText(_T(""));

}
