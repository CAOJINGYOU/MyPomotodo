#pragma once
#include "afxcmn.h"
#include "MySettingCommon.h"
#include "MySettingTomatoRelated.h"
#include "MySettingAccountNum.h"


// MySetting �Ի���

class MySetting : public CDialogEx
{
	DECLARE_DYNAMIC(MySetting)

public:
	MySetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MySetting();

// �Ի�������
	enum { IDD = IDD_MYSETTING };

	INISYSCONFIGINFO * GetSysConfigInfo() const { return g_SysConfigInfo; }
	void SetSysConfigInfo(INISYSCONFIGINFO * val) { g_SysConfigInfo = val; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl m_TabSetting;
	INISYSCONFIGINFO *g_SysConfigInfo;
public:
	virtual BOOL OnInitDialog();
	MySettingCommon m_MySettingCommon;
	MySettingTomatoRelated m_MySettingTomatoRelated;
	MySettingAccountNum m_MySettingAccountNum;
	afx_msg void OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
};
