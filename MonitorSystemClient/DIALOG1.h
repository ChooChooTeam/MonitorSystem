#pragma once
using namespace Gdiplus;
#define GraphSize    40960
enum CmdType {
	CT_Confirm, CT_HideDesk, CT_ShowDesk, CT_ShutDown,
	CT_ReRun, CT_Logout, CT_SendText, CT_CloseClient
};
typedef struct DataPackage
{
	CmdType  MsgType;	//��������
	char  Content[512]; //�ı���Ϣ
};

// CDIALOG1 �Ի���

class CDIALOG1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDIALOG1)
	//for server
	IStream *m_pStm;
	Bitmap  *m_pNewBmp;
	void ShowJPEG(void* pData, int DataSize);
	void OnOK();
	//for jpeg
	int  SendData(UINT index, int mod, int bmpsize, int totalsize, int frames, char *pSendBuf, sockaddr_in &addr);
	afx_msg LRESULT OnReceived(WPARAM wParam, LPARAM lParam);
	SOCKET  m_Socket;		//�ͻ����׽���
	CString		m_ServerIP;		//������IP
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
	int m_IsSendingJpeg;
	WrkSocket * w;
public:
	void startJpeg() {
		m_IsSendingJpeg = true;
		OnOK();

	}
	void stopJpeg() {
		m_IsSendingJpeg = false;
	}
	CDIALOG1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDIALOG1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};
