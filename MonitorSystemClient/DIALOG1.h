#pragma once
using namespace Gdiplus;


// CDIALOG1 对话框

class CDIALOG1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDIALOG1)
	DWORD	m_JpegSize;		//JPEG数据总大小
	//for server
	IStream *m_pStm;
	Bitmap  *m_pNewBmp;
	void ShowJPEG(void* pData, int DataSize);

public:
	CDIALOG1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDIALOG1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
};
