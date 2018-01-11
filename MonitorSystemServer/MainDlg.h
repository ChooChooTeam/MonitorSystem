#pragma once
#include "afxcmn.h"


// CMainDlg 对话框
using namespace Gdiplus;
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)


public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	void ShowJPEG(void* pData, int DataSize); //显示JPEG图片
	virtual ~CMainDlg();

private:
	IStream * m_pStm;
	Bitmap *m_pNewBmp;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	CListCtrl m_userlist;
	CStatic* pic;
};
