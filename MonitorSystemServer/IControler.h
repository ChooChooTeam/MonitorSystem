#pragma once
#include "WrkSocket.h"
#include <vector>
class IControler
{
public:
	// 纯虚函数
	virtual void DoCmd(WsOp op) = 0;							// 执行控制指令	
	virtual void DoJPG(char* jpg, int size) = 0;				// 执行图片
	virtual void DoOnLine(std::vector<CString> nameList, std::vector<CString> IPList) = 0;	// 执行上线操作
	virtual void DoOffLine(std::vector<CString> nameList,CString offlineName) = 0;			// 执行下线操作
	virtual bool DoQuary(CString name, CString pwd) = 0;		// 执行查询操作
	virtual void DoQuaryReturn(bool rtn) = 0;					// 执行查询返回操作
	virtual void DoProgress(CString name[], short PID[], int num) = 0;		// 执行进程信息更新操作
	virtual void DoActivate(CString name,CString IP) = 0;		// 执行激活某一客户端操作
};

