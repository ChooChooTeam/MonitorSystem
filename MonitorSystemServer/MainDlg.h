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

private:
	IStream * m_pStm;
	Bitmap *m_pNewBmp;

	SerCtrl* mSerCtrl;
	LstnSocket* LSocket;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	CListCtrl m_userlist;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult);
};
