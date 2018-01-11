#pragma once
#include "WrkSocket.h"
#include <vector>
class IControler
{
public:
	// ���麯��
	virtual void DoCmd(WsOp op) = 0;		// ִ�п���ָ��	
	virtual void DoJPG(char* jpg, int size) = 0;  // ִ��ͼƬ
	virtual void DoOnLine(std::vector<CString> nameList) = 0;
	virtual void DoOffLine(std::vector<CString> nameList,CString offlineName) = 0;
};

