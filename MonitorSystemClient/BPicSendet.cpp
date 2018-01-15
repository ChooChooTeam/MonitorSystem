#include "stdafx.h"
#include "BPicSendet.h"
#define GraphSize    40960
#define CM_RECEIVED  WM_USER+2
using namespace Gdiplus;

BPicSendet::BPicSendet()
{
	//��ȡ����IP
	hostent* phost = gethostbyname("");
	char* localIP = inet_ntoa(*(struct in_addr *)*phost->h_addr_list);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(localIP);
	addr.sin_port = htons(5001);
	//�����׽���
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		MessageBox(_T("�׽��ִ���ʧ��!"));
	}
	char* len = "9999";
	if (setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, len, 4) != 0)
	{
		MessageBox("����ʧ��!");
	}

	//���׽���
	if (bind(m_Socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox("�׽��ְ�ʧ��!");
	}
	m_ServerIP = "127.0.0.1";
	GetPrivateProfileString("ServerInfo", "IP", "127.0.0.1", m_ServerIP.GetBuffer(0), MAX_PATH, "./Server.ini");
	m_pSendBuf = new char[1024 * 1024];
	m_pHeader = m_pSendBuf;
	WSAAsyncSelect(m_Socket, m_hWnd, CM_RECEIVED, FD_READ);
	m_Confirm = TRUE;
	OnOK();
	m_Received = FALSE;
	m_Counter = 0;
	SetTimer(1, 1000, NULL);
	return TRUE;
}

int BPicSendet::SendData(UINT index, int mod, int bmpsize, int totalsize, int frames, char * pSendBuf, sockaddr_in & addr)
{
	/*���2λ||�������2λ||JPG����||JPG���ݴ�С4λ||JPG�����ܴ�С4λ||���ݱ���С4λ*/
	char* pPackage;
	int packsize = 0;
	if (mod == 0 || index != frames - 1)
		packsize = 2 + 2 + bmpsize + 4 + 4 + 4;
	else
		packsize = 2 + 2 + mod + 4 + 4 + 4;
	pPackage = new char[packsize];
	memset(pPackage, 0, packsize);
	//������ݱ�
	*(WORD*)&pPackage[0] = index;	//������
	if (index != frames - 1)			//���������
		*(WORD*)&pPackage[2] = 0;
	else
		*(WORD*)&pPackage[2] = 1;
	//���λͼ����
	pSendBuf += bmpsize * index;
	memcpy(&pPackage[4], pSendBuf, packsize - 12);
	//���λͼ��С
	*(int*)&pPackage[packsize - 12] = bmpsize;
	//���JPG�����ܴ�С
	*(int*)&pPackage[packsize - 8] = totalsize;
	//������ݱ���С
	*(int*)&pPackage[packsize - 4] = packsize;
	m_Confirm = FALSE;
	int ret = sendto(m_Socket, pPackage, packsize, 0, (sockaddr*)&addr, sizeof(addr));
	delete[] pPackage;
	return ret;
}



BPicSendet::~BPicSendet()
{
}
