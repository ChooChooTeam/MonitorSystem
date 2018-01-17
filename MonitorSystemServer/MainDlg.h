#pragma once
#include "afxcmn.h"
#include "SerCtrl.h"
#include "LstnSocket.h"

// CMainDlg 对话框
using namespace Gdiplus;
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)


public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	void ShowJPEG(void* pData, int DataSize); //显示JPEG图片
	virtual ~CMainDlg();
	SOCKET  m_Socket;					//定义套接字
	char*	m_BmpData;					//位图数据指针
	char*   m_Header;					//临时指针
	BOOL    m_ShowBmp;					//是否显示位图
	char*   m_TempData;					//临时数据指针
	int     m_BmpSize;					//记录位图大小
	int     m_RecSize;					//实际接收的大小
	CString m_ClientIP;					//客户端IP
	UINT    m_ClientPort;				//客户端端口
	DWORD   m_JPGSize;					//JPG数据的总大小	
	BOOL    m_IsScreen;					//是否全屏显示
	WINDOWPLACEMENT m_OldPlacement;		//原来的窗口模式
	CRect m_FullScreenRect;				//全屏显示区域
	sockaddr_in m_Addr;

	void setCurrIP(CString currIP);

private:
	IStream * m_pStm;
	Bitmap *m_pNewBmp;

	SerCtrl* mSerCtrl;
	LstnSocket* LSocket;
	POINT old;//原始客户端长、宽
	CRect old_bt1;
	CRect old_static5;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	void reSize();
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnReceived(WPARAM wParam,LPARAM lParam);
	CListCtrl m_userlist;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 显示当前的用户
	CString CurrUserName;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
