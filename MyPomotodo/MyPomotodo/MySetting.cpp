// MySetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MySetting.h"
#include "afxdialogex.h"




// MySetting �Ի���

IMPLEMENT_DYNAMIC(MySetting, CDialogEx)

MySetting::MySetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(MySetting::IDD, pParent)
{

}

MySetting::~MySetting()
{
}

void MySetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETTING, m_TabSetting);
}


BEGIN_MESSAGE_MAP(MySetting, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETTING, &MySetting::OnTcnSelchangeTabSetting)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &MySetting::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// MySetting ��Ϣ�������


BOOL MySetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_TabSetting.InsertItem(0,_T("����"));  
	m_TabSetting.InsertItem(1,_T("�������")); 
	m_TabSetting.InsertItem(2,_T("�˺�")); 

	m_MySettingCommon.SetSysConfigInfo(g_SysConfigInfo);
	m_MySettingCommon.Create(IDD_DLG_SETTING_COMMON, &m_TabSetting);  
	m_MySettingTomatoRelated.SetSysConfigInfo(g_SysConfigInfo);
	m_MySettingTomatoRelated.Create(IDD_DLG_SETTING_TOMATORELATED, &m_TabSetting);  
	m_MySettingAccountNum.SetSysConfigInfo(g_SysConfigInfo);
	m_MySettingAccountNum.Create(IDD_DLG_SETTING_ACCOUNTNUM, &m_TabSetting);  

	CRect rect; 
	m_TabSetting.GetClientRect(&rect); 
	rect.top+=30;   
	rect.bottom-=5;  
	rect.left+=5;  
	rect.right-=5;

	m_MySettingCommon.MoveWindow(&rect);
	m_MySettingTomatoRelated.MoveWindow(&rect);
	m_MySettingAccountNum.MoveWindow(&rect);

	m_MySettingCommon.ShowWindow(true);
	m_MySettingTomatoRelated.ShowWindow(false);
	m_MySettingAccountNum.ShowWindow(false);

	m_TabSetting.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void MySetting::OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int CurSel = m_TabSetting.GetCurSel();

	m_MySettingCommon.ShowWindow(false);
	m_MySettingTomatoRelated.ShowWindow(false);
	m_MySettingAccountNum.ShowWindow(false);

	switch(CurSel)
	{
	case 0:
		m_MySettingCommon.ShowWindow(true);
		break;
	case 1:
		m_MySettingTomatoRelated.ShowWindow(true);
		break;
	case 2:
		m_MySettingAccountNum.ShowWindow(true);
		break;
	default: ;
	}
}


void MySetting::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}


BOOL MySetting::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::DestroyWindow();
}


void MySetting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void MySetting::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��g_SysConfigInfo��������д�����ݿ�
	m_MySettingTomatoRelated.UpdateData(TRUE);
	g_SysConfigInfo->lTomatoTime = m_MySettingTomatoRelated.m_editLTomato;
	g_SysConfigInfo->lRestTime = m_MySettingTomatoRelated.m_editRestTime;
	g_SysConfigInfo->lLongRestTime = m_MySettingTomatoRelated.m_editLongRestTime;
	g_SysConfigInfo->uLongRestInterval = m_MySettingTomatoRelated.m_editULongRestInterval;

	CDialogEx::OnClose();
}
