#pragma once
enum CmdType {
	CT_Confirm, CT_HideDesk, CT_ShowDesk, CT_ShutDown,
	CT_ReRun, CT_Logout, CT_SendText, CT_CloseClient
};
typedef struct DataPackage
{
	CmdType  MsgType;	//��������
	char  Content[512]; //�ı���Ϣ
};
class BPicSendet
{
public:
	BPicSendet();
public:
	int  SendData(UINT index, int mod, int bmpsize, int totalsize, int frames, char *pSendBuf, sockaddr_in &addr);
	
	ULONG_PTR m_pGdiToken;

	SOCKET  m_Socket;		//�ͻ����׽���
	CString m_ServerIP;		//������IP
	BOOL	m_Confirm;		//ȷ����Ϣ
	int     m_FrameIndex;	//��¼����
	int     m_Mod;			//��¼����
	int     m_Count;		//ÿһ��λͼ�ֱ�������
	int     m_Bmpsize;		//λͼ��ʵ�ʴ�С
	char*	m_pSendBuf;		//���ͻ�����ָ��
	char*	m_pHeader;		//��ʱָ��
	sockaddr_in  m_Addr;	//�׽��ֵ�ַ
	BOOL    m_Received;		//�Ƿ���յ�������������ȷ����Ϣ
	int     m_Counter;		//������
	DWORD	m_JpegSize;		//JPEG�����ܴ�С

	afx_msg void OnTimer(UINT nIDEvent);
	~BPicSendet();
};

