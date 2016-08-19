#pragma once
#include "afxcmn.h"


// MySettingTomatoRelated �Ի���

class MySettingTomatoRelated : public CDialogEx
{
	DECLARE_DYNAMIC(MySettingTomatoRelated)

public:
	MySettingTomatoRelated(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MySettingTomatoRelated();

// �Ի�������
	enum { IDD = IDD_DLG_SETTING_TOMATORELATED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����ʱ��
	LONGLONG m_editLTomato;
	// ����ʱ��spin
	CSpinButtonCtrl m_spinLTomato;
	// ��Ϣʱ��
	LONGLONG m_editRestTime;
	// ��Ϣʱ��spin
	CSpinButtonCtrl m_spinRestTime;
	// ����Ϣʱ��
	LONGLONG m_editLongRestTime;
	// ����Ϣʱ��spin
	CSpinButtonCtrl m_spinLongRestTime;
	// ����Ϣ���
	UINT m_editULongRestInterval;
	// ����Ϣ���spin
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
