#pragma once
#include "afxcmn.h"


// MySettingTomatoRelated 对话框

class MySettingTomatoRelated : public CDialogEx
{
	DECLARE_DYNAMIC(MySettingTomatoRelated)

public:
	MySettingTomatoRelated(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MySettingTomatoRelated();

// 对话框数据
	enum { IDD = IDD_DLG_SETTING_TOMATORELATED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 番茄时长
	LONGLONG m_editLTomato;
	// 番茄时长spin
	CSpinButtonCtrl m_spinLTomato;
	// 休息时长
	LONGLONG m_editRestTime;
	// 休息时长spin
	CSpinButtonCtrl m_spinRestTime;
	// 长休息时长
	LONGLONG m_editLongRestTime;
	// 长休息时长spin
	CSpinButtonCtrl m_spinLongRestTime;
	// 长休息间隔
	UINT m_editULongRestInterval;
	// 长休息间隔spin
	CSpinButtonCtrl m_spinULongRestInterval;
	virtual BOOL OnInitDialog();
public:
	INISYSCONFIGINFO * GetSysConfigInfo() const { return g_SysConfigInfo; }
	void SetSysConfigInfo(INISYSCONFIGINFO * val) { g_SysConfigInfo = val; }
private:
	INISYSCONFIGINFO *g_SysConfigInfo;
public:
	afx_msg void OnEnChangeEditLtomatotime();
};
