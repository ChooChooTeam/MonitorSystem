// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MonitorSystemClient.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
//#include "CEdit.h"

// CRegisterDlg �Ի���

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
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CRegisterDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CRegisterDlg ��Ϣ�������


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(16);  //���ʮ�����ַ�
	CFont font;
	font.CreatePointFont(110, _T("����"));
	GetDlgItem(IDC_STATIC1)->SetFont(&font);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	GetDlgItem(IDC_STATIC3)->SetFont(&font);

	CFont *pFont = new CFont; //����һ��ָ�����������͵�ָ��pFont
	LOGFONT LogFont;
	lstrcpy((LPWSTR)LogFont.lfFaceName, (LPWSTR)"Arial");

	LogFont.lfWeight = 500;
	LogFont.lfWidth = 15;
	LogFont.lfHeight = 25;
	LogFont.lfEscapement = 0;
	LogFont.lfUnderline = FALSE;
	LogFont.lfItalic = FALSE;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfCharSet = GB2312_CHARSET; //���ϲ�������һ����������
	pFont->CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_EDIT_USERNAME)->SetFont(pFont);
	GetDlgItem(IDC_EDIT_PASSWORD)->SetFont(pFont);
	GetDlgItem(IDC_EDIT_DPASSWORD)->SetFont(pFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE

}

BOOL CRegisterDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ȡ�ؼ�����ָ��  
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		  case VK_RETURN:    //���»س���Ӧע�ᰴť 
			CRegisterDlg::OnBnClickedButtonRegister();
				return TRUE;
		}
	}
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	
	if ((GetFocus() == pEdit1 ) && (pMsg->message == WM_CHAR))//���������edit_username�Ŀؼ���
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


void CRegisterDlg::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ж����ݿ����Ƿ�����ͬ���û�����



	CEdit* pass  = (CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
	CEdit* dpass = (CEdit*)GetDlgItem(IDC_EDIT_DPASSWORD);
	CEdit* user = (CEdit * )GetDlgItem(IDC_EDIT_USERNAME);

	int len;
	CString password, dpassword;
	//�ж��Ƿ��û����������Ƿ�Ϊ��,���������Ƿ�һ��
	len= user->GetWindowTextLengthW();
	pass->GetWindowText(password);
	dpass->GetWindowText(dpassword);

	if (password.GetLength() == 0||len==0)
	{
		MessageBox(_T(" �û��������벻��Ϊ��!"), _T("ע��ʧ��")); return;
	}
	if (password != dpassword||password.GetLength()==0)
	{
		MessageBox(_T("  �������벻һ��!"),_T("ע��ʧ��")); return;
	}
	
	//�����û��������뵽���ݿ��У�

}
