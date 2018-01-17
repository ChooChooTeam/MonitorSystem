#pragma once
class IControler;
class LstnSocket;

#define _JPGE_MAX_SIZE_  (2*1024 - 4*3)

enum WsOp
{
	// ������Ϣ
	SHUTDOWN,			// �ػ�
	REBOOT,				// ����
	LOOK,				// ����
	UNLOOK,				// ����		
	STOP,				// ֹͣ����ͼƬ
	RESUME,				// �ָ�����ͼƬ
	// ������Ϣ
	USER_NAME = 0x20,	// ��Ҫ�����û���(��ʼ���ʶ��)
	USER_INFO = 0x21,	// ��Ҫ�����û���Ϣ(�û���������)
	USER_RETURN = 0x22,	// ��Ҫ�����û���Ϣ�˶Խ��(�ͻ��˵�¼)
	PROGRESS = 0x23,	// ��Ҫ���ͽ�����Ϣ
	PROGRESS_RTN = 0x25,// ���ؽ�����Ϣ
	JPGE = 0x24,		// ��Ҫ����ͼƬ��Ϣ
};

struct InfoPack {
	WsOp op;
	int mSize;
	int isEnd;
	char buff[_JPGE_MAX_SIZE_];
};


struct UserInfoStr {
	char name[33];
	char pwd[33];
};

struct ProgressInfo {
	char name[18];
	short ID;
};

// ����Socket
// �ͻ��˿�ʹ�ô�Socket���������ͨѶ
class WrkSocket : public CAsyncSocket
{
public:
	
	WrkSocket(IControler& con,CString username); // �ͻ��˹��캯��
	WrkSocket(IControler& con, CString username, LstnSocket* parent); // �������˹��캯��
	void Connect(CString sIp, int nPort);	// ����
	virtual ~WrkSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	void SendUserInfo(CString name, CString pwdMD5);
	void SendControl(WsOp op);			// ���Ϳ�����Ϣ
	void SendProgress(ProgressInfo p[], int num);

	const CString& GetName();
	CString mIP;			// �׽��ֶ�Ӧ��(�ͻ��˵�)IP

private:
	CString name;			// �׽��ֶ�Ӧ���û���
	IControler & ctrler;	// �ص�������
	LstnSocket* pParent;	// �������׽���

	InfoPack* msgS;			// ���ͻ�����
	InfoPack* msgR;			// ���ܻ�����

	ProgressInfo* progressBuff;	// ������Ϣ������
	CString* names;				// �����û���
	short* PIDs;				// ����PID
	
};

