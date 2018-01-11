#pragma once
#include "WrkSocket.h"
#include <vector>
class IControler
{
public:
	// ´¿Ðéº¯Êý
	virtual void DoCmd(WsOp op) = 0;		// Ö´ÐÐ¿ØÖÆÖ¸Áî	
	virtual void DoJPG(char* jpg, int size) = 0;  // Ö´ÐÐÍ¼Æ¬
	virtual void DoOnLine(std::vector<CString> nameList) = 0;
	virtual void DoOffLine(std::vector<CString> nameList,CString offlineName) = 0;
};

