// MySettingCommon.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MySettingCommon.h"
#include "afxdialogex.h"


// MySettingCommon 对话框

IMPLEMENT_DYNAMIC(MySettingCommon, CDialogEx)

MySettingCommon::MySettingCommon(CWnd* pParent /*=NULL*/)
	: CDialogEx(MySettingCommon::IDD, pParent)
{

}

MySettingCommon::~MySettingCommon()
{
}

void MySettingCommon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DISSYSNOTI, m_bDisplaySystemNotifications);
	DDX_Control(pDX, IDC_CHECK_PLAYTICK, m_bPlayTick);
	DDX_Control(pDX, IDC_CHECK_PLAYHINTS, m_bPlayPromptSound);
	DDX_Control(pDX, IDC_CHECK_POWERBOOT, m_bRunningWithSystem);
	DDX_Control(pDX, IDC_CHECK_FROMSYSTEMTRAY, m_bFromSystemTray);
	DDX_Control(pDX, IDC_CHECK_AUTOADJUSTSIZE, m_bAutoAdjustSize);
}


BEGIN_MESSAGE_MAP(MySettingCommon, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_DISSYSNOTI, &MySettingCommon::OnBnClickedCheckDissysnoti)
	ON_BN_CLICKED(IDC_CHECK_PLAYTICK, &MySettingCommon::OnBnClickedCheckPlaytick)
	ON_BN_CLICKED(IDC_CHECK_PLAYHINTS, &MySettingCommon::OnBnClickedCheckPlayhints)
	ON_BN_CLICKED(IDC_CHECK_POWERBOOT, &MySettingCommon::OnBnClickedCheckPowerboot)
	ON_BN_CLICKED(IDC_CHECK_FROMSYSTEMTRAY, &MySettingCommon::OnBnClickedCheckFromsystemtray)
	ON_BN_CLICKED(IDC_CHECK_AUTOADJUSTSIZE, &MySettingCommon::OnBnClickedCheckAutoadjustsize)
END_MESSAGE_MAP()


// MySettingCommon 消息处理程序


void MySettingCommon::OnBnClickedCheckDissysnoti()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked( IDC_CHECK_DISSYSNOTI ))
	{
		g_SysConfigInfo->bDisplaySystemNotifications = TRUE;
	}
	else
	{
		g_SysConfigInfo->bDisplaySystemNotifications = FALSE;
	}
}


void MySettingCommon::OnBnClickedCheckPlaytick()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked( IDC_CHECK_PLAYTICK ))
	{
		g_SysConfigInfo->bPlayTick = TRUE;
	}
	else
	{
		g_SysConfigInfo->bPlayTick = FALSE;
	}

}


void MySettingCommon::OnBnClickedCheckPlayhints()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked( IDC_CHECK_PLAYHINTS ))
	{
		g_SysConfigInfo->bPlayPromptSound = TRUE;
	}
	else
	{
		g_SysConfigInfo->bPlayPromptSound = FALSE;
	}
	
}


void MySettingCommon::OnBnClickedCheckPowerboot()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked( IDC_CHECK_POWERBOOT ))
	{
		g_SysConfigInfo->bRunningWithSystem = TRUE;
	}
	else
	{
		g_SysConfigInfo->bRunningWithSystem = FALSE;
	}
	
}


void MySettingCommon::OnBnClickedCheckFromsystemtray()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked( IDC_CHECK_FROMSYSTEMTRAY ))
	{
		g_SysConfigInfo->bFromSystemTray = TRUE;
	}
	else
	{
		g_SysConfigInfo->bFromSystemTray = FALSE;
	}
	
}


void MySettingCommon::OnBnClickedCheckAutoadjustsize()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked( IDC_CHECK_AUTOADJUSTSIZE ))
	{
		g_SysConfigInfo->bAutoAdjustSize = TRUE;
	}
	else
	{
		g_SysConfigInfo->bAutoAdjustSize = FALSE;
	}
	
}


BOOL MySettingCommon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_bDisplaySystemNotifications.SetCheck(TRUE);
	/*if (g_SysConfigInfo->bDisplaySystemNotifications)
	{
	m_bDisplaySystemNotifications.SetCheck(TRUE);
	}*/
	CheckDlgButton(IDC_CHECK_DISSYSNOTI,g_SysConfigInfo->bDisplaySystemNotifications?BST_CHECKED:BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_PLAYTICK,g_SysConfigInfo->bPlayTick?BST_CHECKED:BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_PLAYHINTS,g_SysConfigInfo->bPlayPromptSound?BST_CHECKED:BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_POWERBOOT,g_SysConfigInfo->bRunningWithSystem?BST_CHECKED:BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_FROMSYSTEMTRAY,g_SysConfigInfo->bFromSystemTray?BST_CHECKED:BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_AUTOADJUSTSIZE,g_SysConfigInfo->bAutoAdjustSize?BST_CHECKED:BST_UNCHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
