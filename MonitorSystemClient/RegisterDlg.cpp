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
	ON_EN_UPDATE(IDC_EDIT_USERNAME, &CRegisterDlg::OnEnUpdateEditUsername)
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CRegisterDlg ��Ϣ�������


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(16);

		return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE

}


void CRegisterDlg::OnEnUpdateEditUsername()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	const int m_maxTxtLen = 16; //16���ֽ�

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	CString strVal;
	pEdit->GetWindowText(strVal);
	int a = CStringA(strVal).GetLength();
	 
	if (a - bytes >= 2)  //�����ַ��������ֽ�,�ж�����
	{
		MessageBox(_T("ע���û������ɺ�������,����������"));

		CString strtemp;
		strtemp = strVal.Left(bytes);  //��������ַ�
		pEdit->SetWindowText(strtemp);

		int l = pEdit->GetWindowTextLength();
		pEdit->SetSel(l, l, FALSE); //������ŵ���β
		pEdit->SetFocus();
	}


   pEdit->GetWindowText(strVal);
   bytes= CStringA(strVal).GetLength();

  // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


