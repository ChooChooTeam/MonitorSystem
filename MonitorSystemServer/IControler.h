#pragma once
#include "WrkSocket.h"
#include <vector>
class IControler
{
public:
	// ���麯��
	virtual void DoCmd(WsOp op) = 0;							// ִ�п���ָ��	
	virtual void DoJPG(char* jpg, int size) = 0;				// ִ��ͼƬ
	virtual void DoOnLine(std::vector<CString> nameList, std::vector<CString> IPList) = 0;	// ִ�����߲���
	virtual void DoOffLine(std::vector<CString> nameList,CString offlineName) = 0;			// ִ�����߲���
	virtual bool DoQuary(CString name, CString pwd) = 0;		// ִ�в�ѯ����
	virtual void DoQuaryReturn(bool rtn) = 0;					// ִ�в�ѯ���ز���
	virtual void DoProgress(CString name[], short PID[], int num) = 0;		// ִ�н�����Ϣ���²���
	virtual void DoActivate(CString name,CString IP) = 0;		// ִ�м���ĳһ�ͻ��˲���
};

