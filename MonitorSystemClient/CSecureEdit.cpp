// CSecureEdit.cpp: 实现文件
//

#include "stdafx.h"
#include "MonitorSystemClient.h"
#include "CSecureEdit.h"



// CSecureEdit

IMPLEMENT_DYNAMIC(CSecureEdit, CEdit)

CSecureEdit::CSecureEdit()
{

}

CSecureEdit::~CSecureEdit()
{
}


BEGIN_MESSAGE_MAP(CSecureEdit, CEdit)
	ON_CONTROL_REFLECT(EN_UPDATE, &CSecureEdit::OnEnUpdate)
	ON_WM_CHAR()
	ON_WM_CONTEXTMENU()	
	ON_EN_CHANGE(IDC_EDIT2, &CSecureEdit::OnEnChangeEdit2)
END_MESSAGE_MAP()



// CSecureEdit 消息处理程序

bool used = false;


void CSecureEdit::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(ES_PASSWORD, 0);
    CEdit::PreSubclassWindow();
}


void CSecureEdit::OnEnUpdate()
{
	//static bool used = false;
	if (used)
	{
		used = false; return;
	}

	CString strText;
	CEdit::GetWindowText(strText);
	int nLen = strText.GetLength();
	DWORD dwPos = GetSel() & 0xFFFF;

	BOOL bHasChanged = FALSE;

	int i;
	int nDiff = nLen - oldlen;
	int nIndex = 0;
	BOOL bChinese = false;
	for (i = 0; i < nLen; i++)
	{
		UCHAR c = strText.GetAt(i);
		if (c != '*')
		{
			bHasChanged = true;
			nIndex = i;
			if (c > 160)
				bChinese = true;
			break;
		}

	}

	if (bHasChanged = false)
		return;
	if (oldlen == 0)
		m_strRealtext = strText;
	else
	{
		CString strTemp;
		if (nDiff < 0)
		{
			int nNum = 1;
			strTemp = m_strRealtext.Left(nIndex);
			strTemp += strText.Mid(nIndex, nNum);
			strTemp += m_strRealtext.Right(nLen - nIndex - nNum);
			m_strRealtext = strTemp;
		}
		else if (nDiff == 0)
		{
			m_strRealtext.SetAt(nIndex, strText.GetAt(nIndex));
			if (bChinese)
				m_strRealtext.SetAt(nIndex + 1, strText.GetAt(nIndex + 1));
		}
		else if (nDiff > 0)
		{
			int nNum = 1;
			strTemp = m_strRealtext.Left(nIndex);
			strTemp += strText.Mid(nIndex, nNum);
			strTemp += m_strRealtext.Right(nLen - nIndex - nNum);
			m_strRealtext = strTemp;

		}
	}

	strText.Empty();
	for (i = 0; i < nLen; i++)
		strText += '*';
	oldlen = nLen;


	
	used = true; 
	CEdit::SetWindowText(strText);
	SetSel(dwPos, dwPos, FALSE);



	
}


void CSecureEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nChar == 22 && nRepCnt == 1 && (!(nFlags & 0x400))) //ctrl+v
		return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


void CSecureEdit::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
	//MessageBox(_T("无法调用!"));

	//CMenu *pPopup;
	//pPopup = popMenu.GetSubMenu(0);
	//pPopup->EnableMenuItem(IDC_EDIT2, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);


}

void CSecureEdit::SetWindowText(LPCTSTR lpszString)
{
	CString strText;
	if (lpszString == NULL) return;
	m_strRealtext = lpszString;
	int len = strlen((char*)lpszString);
	
	strText.Empty();
	for (int i = 0; i < len; i++)
		strText += '*';

	 oldlen = len;
	
	 CEdit::SetWindowText(strText);


}

void CSecureEdit::GetWindowText(CString & rString) const
{

}

void CSecureEdit::GetRealText(CString & rString) const
{
	rString = m_strRealtext;
}



void CSecureEdit::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CEdit::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	

	//MessageBox(_T("adfad"));





	// TODO:  在此添加控件通知处理程序代码
}
