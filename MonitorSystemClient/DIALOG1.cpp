// DIALOG1.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystemClient.h"
#include "DIALOG1.h"
#include "afxdialogex.h"
#include "BPowerM.h"
#include "BProcessM.h"

// CDIALOG1 对话框

IMPLEMENT_DYNAMIC(CDIALOG1, CDialogEx)

CDIALOG1::CDIALOG1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDIALOG1::~CDIALOG1()
{
}

void CDIALOG1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDIALOG1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDIALOG1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CDIALOG1::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CDIALOG1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CDIALOG1::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CDIALOG1::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDIALOG1 消息处理程序


void CDIALOG1::OnBnClickedButton2()
{
	BPowerM::EnableShutDownPriv();
	BPowerM::ReSetWindows(EWX_SHUTDOWN, true);//关机  
}


void CDIALOG1::OnBnClickedButton5()
{
	BPowerM::ReSetWindows(EWX_LOGOFF, false);//注销  
}


void CDIALOG1::OnBnClickedButton3()
{
	BPowerM::ReSetWindows(EWX_REBOOT, true);//重启  
}


void CDIALOG1::OnBnClickedButton7()
{
	BPowerM::ReSetWindows(EWX_SETPOWER, true);//睡眠  
}


void CDIALOG1::OnBnClickedButton4()
{
	BProcessM::showAllProcess();
}
