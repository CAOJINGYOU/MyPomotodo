#pragma once


// CMyButton

#include "ximage.h"


class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

private:
	CxImage * m_pImgNormal;
	CxImage * m_pImgOver;
	CxImage * m_pImgDown;
	CxImage * m_pImgFocus;
	CxImage * m_pImgDisable;

	BOOL m_bTracking;
	BOOL m_bMouseOver;
	BOOL m_bLBtnDown;

public:
	CMyButton(CString strBtnDown, CString strBtnOver, CString strBtnNormal, CString strBtnDisabled = _T(""), CString strBtnFocus = _T(""));
	virtual ~CMyButton();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	void PaintParent();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnDoubleclicked();
	afx_msg void OnBnKillfocus();
	// ≥ı ºªØ
	void init(void);
	int GetImageType(CString& strImageName);
};


