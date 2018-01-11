#pragma once
class IControler;
class LstnSocket;
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
	USER_INFO = 0x20,	// ��Ҫ�����û���Ϣ
	PROGRESS = 0x22,	// ��Ҫ���ͽ�����Ϣ
	JPGE = 0x24,		// ��Ҫ����ͼƬ��Ϣ
};

// ����Socket
// �ͻ��˿�ʹ�ô�Socket���������ͨѶ
class WrkSocket : public CAsyncSocket
{
public:
	// �ͻ��˹��캯��
	WrkSocket(IControler& con,CString username);
	// �������˹��캯��
	WrkSocket(IControler& con, CString username, LstnSocket* parent);
	void Connect(CString sIp, int nPort);	// ����
	virtual ~WrkSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	void SendControl(WsOp op);	// ���Ϳ�����Ϣ
	void SendJPGE(char* jpg, int size);	// ����ͼƬ��Ϣ

	const CString& GetName();

private:
	CString name;		//�׽��ֶ�Ӧ���û���
	IControler & ctrler;
	LstnSocket* pParent;

	int mSize;
	char* jpgBuff;
};

