#pragma once


// CDIALOG1 �Ի���

class CDIALOG1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDIALOG1)

public:
	CDIALOG1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDIALOG1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
};
