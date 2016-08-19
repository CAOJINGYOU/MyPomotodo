#pragma once

enum{
	BUTTON,
	DAY,
	YEAR
};
// CMyTomatoButton

class CMyTomatoButton : public CButton
{
	DECLARE_DYNAMIC(CMyTomatoButton)

public:
	CMyTomatoButton();
	CMyTomatoButton(CString strBeigTime,CString strEndTime,CString strContent,int nType = BUTTON);
	virtual ~CMyTomatoButton();

protected:
	DECLARE_MESSAGE_MAP()
	CFont m_Font;
	CFont m_Font1;
public:
	CString m_strContent;
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	CString m_strBeigTime;
	CString m_strEndTime;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	// ∞¥≈•¿‡–Õ
	int m_nType;
};


