#pragma once


// MySettingAccountNum �Ի���

class MySettingAccountNum : public CDialogEx
{
	DECLARE_DYNAMIC(MySettingAccountNum)

public:
	MySettingAccountNum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MySettingAccountNum();

// �Ի�������
	enum { IDD = IDD_DLG_SETTING_ACCOUNTNUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	INISYSCONFIGINFO * GetSysConfigInfo() const { return g_SysConfigInfo; }
	void SetSysConfigInfo(INISYSCONFIGINFO * val) { g_SysConfigInfo = val; }
private:
	INISYSCONFIGINFO *g_SysConfigInfo;
};
