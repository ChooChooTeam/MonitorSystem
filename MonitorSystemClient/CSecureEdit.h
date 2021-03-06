#pragma once
#define SECURE_CHAR '*'

// CSecureEdit

class CSecureEdit : public CEdit
{
	DECLARE_DYNAMIC(CSecureEdit)

public:
	CSecureEdit();
	virtual ~CSecureEdit();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnEnUpdate();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
private:
	CString m_strRealtext;
	int oldlen;
public:
	void SetWindowText(LPCTSTR lpszString);
	void GetWindowText(CString  & rString) const;
	void GetRealText(CString & rString) const;

	afx_msg void OnEnChangeEdit2();
};


