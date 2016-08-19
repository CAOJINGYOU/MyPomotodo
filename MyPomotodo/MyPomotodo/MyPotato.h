#pragma once
#include "afxwin.h"
#include "MyDatabase.h"

#include "MyButtonList.h"
// CMyPotato 对话框

class CMyPotato : public CDialogEx
{
	DECLARE_DYNAMIC(CMyPotato)

public:
	CMyPotato(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyPotato();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POTATO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAddpotato();
	// 添加土豆的文本框
	CEdit m_EditAddPotato;
	//CMyDatabase m_MyDatabase;
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CMyButtonList* m_DlgButtonList;
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
};
