#pragma once
#include "afxcmn.h"
#include "SerCtrl.h"
#include "LstnSocket.h"

// CMainDlg �Ի���
using namespace Gdiplus;
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)


public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	void ShowJPEG(void* pData, int DataSize); //��ʾJPEGͼƬ
	virtual ~CMainDlg();
	SOCKET  m_Socket;					//�����׽���
	char*	m_BmpData;					//λͼ����ָ��
	char*   m_Header;					//��ʱָ��
	BOOL    m_ShowBmp;					//�Ƿ���ʾλͼ
	char*   m_TempData;					//��ʱ����ָ��
	int     m_BmpSize;					//��¼λͼ��С
	int     m_RecSize;					//ʵ�ʽ��յĴ�С
	CString m_ClientIP;					//�ͻ���IP
	UINT    m_ClientPort;				//�ͻ��˶˿�
	DWORD   m_JPGSize;					//JPG���ݵ��ܴ�С	
	BOOL    m_IsScreen;					//�Ƿ�ȫ����ʾ
	WINDOWPLACEMENT m_OldPlacement;		//ԭ���Ĵ���ģʽ
	CRect m_FullScreenRect;				//ȫ����ʾ����
	sockaddr_in m_Addr;

	void setCurrIP(CString currIP);

private:
	IStream * m_pStm;
	Bitmap *m_pNewBmp;

	SerCtrl* mSerCtrl;
	LstnSocket* LSocket;
	POINT old;//ԭʼ�ͻ��˳�����
	CRect old_bt1;
	CRect old_static5;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	// ��ʾ��ǰ���û�
	CString CurrUserName;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
