#pragma once
#include "afxwin.h"


// MySettingCommon 对话框

class MySettingCommon : public CDialogEx
{
	DECLARE_DYNAMIC(MySettingCommon)

public:
	MySettingCommon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MySettingCommon();

// 对话框数据
	enum { IDD = IDD_DLG_SETTING_COMMON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckDissysnoti();
	afx_msg void OnBnClickedCheckPlaytick();
	afx_msg void OnBnClickedCheckPlayhints();
	afx_msg void OnBnClickedCheckPowerboot();
	afx_msg void OnBnClickedCheckFromsystemtray();
	afx_msg void OnBnClickedCheckAutoadjustsize();
	virtual BOOL OnInitDialog();
	

	INISYSCONFIGINFO * GetSysConfigInfo() const { return g_SysConfigInfo; }
	void SetSysConfigInfo(INISYSCONFIGINFO * val) { g_SysConfigInfo = val; }
private:
	INISYSCONFIGINFO *g_SysConfigInfo;

	CButton m_bDisplaySystemNotifications;
	CButton m_bPlayTick;
	CButton m_bPlayPromptSound;
	CButton m_bRunningWithSystem;
	CButton m_bFromSystemTray;
	CButton m_bAutoAdjustSize;
	
};
