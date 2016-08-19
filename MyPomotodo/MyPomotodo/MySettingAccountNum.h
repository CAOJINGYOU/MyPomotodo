#pragma once


// MySettingAccountNum 对话框

class MySettingAccountNum : public CDialogEx
{
	DECLARE_DYNAMIC(MySettingAccountNum)

public:
	MySettingAccountNum(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MySettingAccountNum();

// 对话框数据
	enum { IDD = IDD_DLG_SETTING_ACCOUNTNUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	INISYSCONFIGINFO * GetSysConfigInfo() const { return g_SysConfigInfo; }
	void SetSysConfigInfo(INISYSCONFIGINFO * val) { g_SysConfigInfo = val; }
private:
	INISYSCONFIGINFO *g_SysConfigInfo;
};
