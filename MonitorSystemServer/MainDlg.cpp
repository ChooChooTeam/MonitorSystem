// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "MainDlg.h"
#include "afxdialogex.h"
using namespace Gdiplus;

// CMainDlg �Ի���

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	
}

void CMainDlg::ShowJPEG(void * pData, int DataSize)
{

	HGLOBAL m_hMem1 = GlobalAlloc(GMEM_MOVEABLE, DataSize);
	LPBYTE lpData1 = (LPBYTE)GlobalLock(m_hMem1);
	memcpy(lpData1, pData, DataSize);
	GlobalUnlock(m_hMem1);
	::CreateStreamOnHGlobal(m_hMem1, TRUE, &m_pStm);

	m_pNewBmp = Bitmap::FromStream(m_pStm);
	CRect rc;
	GetClientRect(rc);
	HDC hDC = pic->GetDC()->m_hDC;
	Graphics *graphics = Graphics::FromHDC(hDC);
	graphics->DrawImage(m_pNewBmp, 1, 1, rc.Width(), rc.Height());
	m_pStm->Release();
	m_pStm = NULL;
	delete graphics;
	GlobalFree(m_hMem1);
	::ReleaseDC(m_hWnd, hDC);
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_LIST4, m_userlist);
}



BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������





BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ��������Ϣ�б�
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_list.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	m_list.InsertColumn(1, _T("������"), LVCFMT_LEFT, 100);        // �����2�е�����  
	m_list.InsertColumn(2, _T("CPU"), LVCFMT_LEFT, 100);        // �����3�е�����  
	m_list.InsertColumn(3, _T("�ڴ�"), LVCFMT_LEFT, 100);        // �����4�е����� 
	CString strName, strAge, strSex;
	for (int i = 0; i <= 7; i++) {
		strName.Format(_T("����%d"), i);
		strAge.Format(_T("%d"), 20 + i);
		strSex = i % 2 ? _T("10") : _T("20");
		m_list.InsertItem(i, _T(""));                          // ������  
		m_list.SetItemText(i, 1, strName);                     // ���õ�2��(����)  
		m_list.SetItemText(i, 2, strAge);                      // ���õ�3��(����)  
		m_list.SetItemText(i, 3, strSex);                      // ���õ�4��(�Ա�)  
	}

	//��ʼ���û���Ϣ�б�
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_userlist.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	m_userlist.InsertColumn(1, _T("�û���"), LVCFMT_LEFT, 100);        // �����2�е�����  
	
	CString userName;
	for (int i = 0; i <= 7; i++) {
		userName.Format(_T("�û�%d"), i);
		m_userlist.InsertItem(i, _T(""));                          // ������  
		m_userlist.SetItemText(i, 1, userName);                     // ���õ�2��(����)  
		
	}

	pic = (CStatic*)GetDlgItem(IDC_STATIC);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
