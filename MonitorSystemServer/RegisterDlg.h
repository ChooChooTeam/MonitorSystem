#pragma once
#include"Adosql.h"


// RegisterDlg �Ի���

class RegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RegisterDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRegister();
	// ����Ա��
	CString m_edit_AdminName;

	// ����Ա����
	CString m_edit_AdminPwd;
	// ȷ������
	CString m_edit_AdminEndPwd;

	Adosql sql;
};
