#pragma once
#include "WrkSocket.h"
#include <string>
#include <map>
#include <vector>
// ����Socket
// ��������ʹ��,���ڼ����ͻ�������
class LstnSocket : public CAsyncSocket
{
public:
	LstnSocket(IControler& con);
	void Listen(int nPort);
	void SendControl(CString name, WsOp op);	// ���Ϳ�����Ϣ
	bool Activate(CString name);				// ����ָ�����Ŀͻ���
	CString GetCurrName();						// ��õ�ǰ���ڼ���״̬��Socket�ͻ���
	void ResetAll();
	virtual ~LstnSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void NewOnLine();
	void NewOffLine(CString name);

private:
	std::vector<WrkSocket*> vecWrk;
	CString currName;
	IControler& ctrler;
	int port;
};

