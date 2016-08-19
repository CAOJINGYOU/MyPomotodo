#pragma once


// CMyPotatoListButton

#include "ximage.h"


class CMyPotatoListButton : public CButton
{
	DECLARE_DYNAMIC(CMyPotatoListButton)

private:
	CxImage * m_pImgNormal;//用了
	CxImage * m_pImgOver;//用了
	CxImage * m_pImgDown;
	CxImage * m_pImgFocus;
	CxImage * m_pImgDisable;
	CxImage * m_pImgPinOver;//用了
	CxImage * m_pImgPinDown;//用了
	CxImage * m_pImgSelectedNormal;//用了
	CxImage * m_pImgPinSelectedOver;//用了

	BOOL m_bTracking;
	BOOL m_bMouseOver;
	BOOL m_bLBtnDown;
	BOOL m_bSelected;

	CBrush m_BrushOver;
	CBrush m_BrushSelectedOver;
	CBrush m_BrushgNormal;

	CFont m_Font;
	CFont m_StrikeFont;

public:
	CMyPotatoListButton(int nId,CString strBtnDown, CString strBtnOver, CString strBtnNormal, 
		CString strBtnSelectedNormal,CString strBtnPinOver, CString strBtnPinSelectedOver, 
		CString strBtnPinDown, CString strBtnDisabled = _T(""), CString strBtnFocus = _T(""), 
		CString strBtnName = _T(""));
	virtual ~CMyPotatoListButton();

	BOOL GetSelected() const { return m_bSelected; }
	
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
	// 初始化
	void init(void);
	int GetImageType(CString& strImageName);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_strButtonName;
	int m_nID;
};


