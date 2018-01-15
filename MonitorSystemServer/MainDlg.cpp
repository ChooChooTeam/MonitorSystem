// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MonitorSystemServer.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include <gdiplus.h>
// CMainDlg �Ի���
#define CM_RECEIVED  WM_USER+1001
#pragma warning(disable: 4996)   
#define MAX_BUFF 99999
IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

enum CmdType {
	CT_Confirm, CT_HideDesk, CT_ShowDesk, CT_ShutDown,
	CT_ReRun, CT_Logout, CT_SendText, CT_CloseClient
};

typedef struct DataPackage
{
	CmdType	MsgType;		//��������
	char	Content[512];	//�ı���Ϣ,ֻ������������ΪCT_SendTextʱ�Ϸ�
};

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
	CClientDC dc(this);


	CRect rc;
	CStatic* pic = (CStatic*)GetDlgItem(IDC_PIC);
	pic->GetClientRect(rc);
	HDC hDC = pic->GetDC()->m_hDC;
	// DEBUG: �˴�����ֵ����ȷ
	//Gdiplus::Graphics *graphics = Gdiplus::Graphics::FromHDC(hDC);
	Gdiplus::Graphics graphics(hDC);
	graphics.DrawImage(m_pNewBmp, 1, 1, rc.Width(), rc.Height());
	m_pStm->Release();
	m_pStm = NULL;
	//delete graphics;
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
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CMainDlg::OnNMClickList4)
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
	
	//CString userName;
	//for (int i = 0; i <= 7; i++) {
	//	userName.Format(_T("�û�%d"), i);
	//	m_userlist.InsertItem(i, _T(""));                          // ������  
	//	m_userlist.SetItemText(i, 1, userName);                     // ���õ�2��(����)  
	//	
	//}

	mSerCtrl = new SerCtrl(this);
	LSocket = new LstnSocket(*mSerCtrl);
	LSocket->Listen(8848);


	//��ȡ����IP
	hostent* phost = gethostbyname("");
	char* localIP = inet_ntoa(*(struct in_addr *)*phost->h_addr_list);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(localIP);
	addr.sin_port = htons(5002);
	//�����׽���
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		MessageBox(_T("�׽��ִ���ʧ��!"));
	}
	//���׽���
	if (bind(m_Socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(_T("�׽��ְ�ʧ��!"));
	}
	m_BmpData = new char[1024 * 1024];
	memset(m_BmpData, 0, 1024 * 1024);
	m_TempData = new char[1024 * 1024 * 2];
	memset(m_TempData, 0, 1024 * 1024 * 2);
	m_Header = m_BmpData;
	WSAAsyncSelect(m_Socket, m_hWnd, CM_RECEIVED, FD_READ);
	m_ShowBmp = FALSE;
	m_BmpSize = 0;
	m_RecSize = 0;
	m_ClientPort = 0;
	WCHAR IP[MAX_PATH] = { 0 };
	GetPrivateProfileString(_T("ClientInfo"),_T( "IP"),_T( "127.0.0.1"), IP, MAX_PATH, _T("./Client.ini"));
	m_ClientIP = IP;





	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CMainDlg::OnReceived()
{
	//��������
	BYTE* buffer = new BYTE[MAX_BUFF];

	int factsize = sizeof(sockaddr);
	int ret = recvfrom(m_Socket, (char*)buffer, MAX_BUFF, 0, (sockaddr*)&m_Addr, &factsize);

	if (ret != -1)
	{
		CString revIP =CString( inet_ntoa(m_Addr.sin_addr));
		if (revIP != m_ClientIP)
		{
			delete[] buffer;
			return;
		}
		/*���2λ||�������2λ||JPG����||JPG���ݴ�С4λ||JPG�����ܴ�С4λ||���ݱ���С4λ*/
		m_ClientPort = ntohs(m_Addr.sin_port);
		//��¼���յ����ݱ���С
		m_RecSize += ret;
		//��ȡ���
		WORD orderID = *(WORD*)&buffer[0];
		//��ȡ�������
		WORD endID = *(WORD*)&buffer[2];
		//��ȡλͼ��С
		int bmpsize = *(int*)&buffer[ret - 12];
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(m_ClientPort);
		addr.sin_addr.S_un.S_addr = inet_addr((LPSTR)(LPCTSTR)m_ClientIP.GetBuffer(0));
		int size = sizeof(addr);
		m_JPGSize = 0;
		//����ȷ����Ϣ
		DataPackage Package;
		memset(&Package, 0, sizeof(DataPackage));

		Package.MsgType = CT_Confirm;

		int nRet = sendto(m_Socket, (char*)&Package, sizeof(DataPackage), 0, (sockaddr*)&m_Addr, size);

		if (orderID == 0)
		{
			m_BmpSize = bmpsize;
			m_BmpData = m_Header;
		}
		else
			m_BmpSize += bmpsize;
		memcpy(m_BmpData, &buffer[4], bmpsize);
		m_BmpData += bmpsize;
		m_ShowBmp = FALSE;
		if (endID == 1)
		{
			m_ShowBmp = TRUE;
			m_BmpData = m_Header;
			m_JPGSize = *(int*)&buffer[ret - 8];
			memset(m_TempData, 0, 1024 * 1024 * 2);
			memcpy(m_TempData, m_Header, 1024 * 1024);
			ShowJPEG(m_TempData, m_JPGSize);
			m_RecSize = 0;
		}
	}
	delete[] buffer;
}


void CMainDlg::OnBnClickedButton3()
{
	ShowJPEG(nullptr, 0);
}


// �û��б�򵥻��¼�
void CMainDlg::OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n = m_userlist.GetSelectionMark();

	CString name = m_userlist.GetItemText(n, 0);

	LSocket->Activate(name);
	

	*pResult = 0;
}
