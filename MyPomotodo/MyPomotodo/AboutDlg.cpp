// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "AboutDlg.h"
#include "afxdialogex.h"


// CAboutDlg 对话框

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{

}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CAboutDlg::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()


// CAboutDlg 消息处理程序


void CAboutDlg::OnBnClickedButtonUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"), _T("http://blog.leanote.com/yhcao"), NULL, NULL, SW_SHOWNORMAL);
}
