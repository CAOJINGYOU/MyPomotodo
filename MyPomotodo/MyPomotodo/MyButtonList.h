#pragma once

#include "MyPotatoListButton.h"
#include "MyDatabase.h"
// CMyButtonList �Ի���

class CMyButtonList : public CDialogEx
{
	DECLARE_DYNAMIC(CMyButtonList)

public:
	CMyButtonList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyButtonList();

// �Ի�������
	enum { IDD = IDD_DIALOG_BUTTON_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CArray<CMyPotatoListButton*, CMyPotatoListButton*&> m_arrPotatoList;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void PreInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();

	int m_page;
	int GetScrollPos(int nBar, UINT nSBCode);  
	void ScrollClient(int nBar, int nPos);  
	void VScrool(int nBar, UINT nSBCode);


	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	//CMyDatabase m_MyDatabase;
	int updateList(void);
	void init(void);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
