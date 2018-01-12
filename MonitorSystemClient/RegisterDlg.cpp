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
END_MESSAGE_MAP()


// CRegisterDlg ��Ϣ�������


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(16);  //���ʮ�����ַ�

		return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE

}

BOOL CRegisterDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ȡ�ؼ�����ָ��  
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	
	if ((GetFocus() == pEdit1 ) && (pMsg->message == WM_CHAR))
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
