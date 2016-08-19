#pragma once
#include "afxwin.h"
#include "MyTomatoButton.h"
#include "MyDatabase.h"
// CMyTomato 对话框

class CMyTomato : public CDialogEx
{
	DECLARE_DYNAMIC(CMyTomato)

public:
	CMyTomato(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyTomato();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOMATO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CArray<CMyTomatoButton*, CMyTomatoButton*&> m_arrTomatoList;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	int m_page;

	int GetScrollPos(int nBar, UINT nSBCode);  
	void ScrollClient(int nBar, int nPos);  
	void VScrool(int nBar, UINT nSBCode);

//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int updateList(void);
	void init(void);
	virtual BOOL DestroyWindow();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CTime StringToTime(CString strTime);
};
