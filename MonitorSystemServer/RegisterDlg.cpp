// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


// RegisterDlg �Ի���

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_REGISTER, pParent)
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &RegisterDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// RegisterDlg ��Ϣ�������


void RegisterDlg::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
