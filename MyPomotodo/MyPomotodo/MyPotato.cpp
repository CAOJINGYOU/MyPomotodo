// MyPotato.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyPotato.h"
#include "afxdialogex.h"

// CMyPotato 对话框
extern CMyDatabase g_MyDatabase;

IMPLEMENT_DYNAMIC(CMyPotato, CDialogEx)

CMyPotato::CMyPotato(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_POTATO, pParent)
	, m_DlgButtonList(NULL)
{
	//m_MyDatabase.CreateTablePotato();
	//m_MyDatabase.init()
	//g_MyDatabase.init();
}

CMyPotato::~CMyPotato()
{
	if (m_DlgButtonList!=NULL)
	{
		delete m_DlgButtonList;
		m_DlgButtonList = NULL;
	}
}

void CMyPotato::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_ADDPOTATO, m_EditAddPotato);
	DDX_Control(pDX, IDC_EDIT_POTATO, m_EditAddPotato);
}


BEGIN_MESSAGE_MAP(CMyPotato, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMyPotato::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADDPOTATO, &CMyPotato::OnBnClickedButtonAddpotato)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyPotato 消息处理程序


BOOL CMyPotato::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_KEYDOWN)
	{
		if ( VK_RETURN == pMsg->wParam )
		{
			// 按下回车
			// 获取焦点句柄
			HWND hFocus = ::GetFocus();
			if ( hFocus == m_EditAddPotato.GetSafeHwnd() )
			{
				// 处理你的逻辑
				OnBnClickedButtonAddpotato();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyPotato::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	///CDialogEx::OnOK();
}


void CMyPotato::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


void CMyPotato::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CMyPotato::OnBnClickedButtonAddpotato()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strTemp = _T("");
	GetDlgItem(IDC_EDIT_POTATO)->GetWindowText(strTemp);

	strTemp.Trim();

	if (strTemp.GetLength()<=0)
	{
		return;
	}

	//m_MyDatabase.InsertTablePotato(strTemp);
	g_MyDatabase.InsertTablePotato(strTemp);

	GetDlgItem(IDC_EDIT_POTATO)->SetWindowText(_T(""));
	/*m_MyDatabase.SelectTablePotato();

	std::vector<POTATOINFO>::iterator iter;
	for(iter=m_MyDatabase.m_vPotatos.begin();iter!=m_MyDatabase.m_vPotatos.end();iter++)
	{
	CString strName = iter->strPotatoName;
	int n = iter->nId;
	}*/

	m_DlgButtonList->updateList();
}


HBRUSH CMyPotato::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC && !m_DlgButtonList)
	{
		CRect rect;

		m_DlgButtonList = new CMyButtonList;
		if (m_DlgButtonList->Create(IDD_DIALOG_BUTTON_LIST, this))
		{
			pWnd->GetWindowRect(&rect);
			m_DlgButtonList->ScreenToClient(&rect);
			rect.DeflateRect(5, 10, 0, 0);
			m_DlgButtonList->MoveWindow(&rect);
			m_DlgButtonList->ShowWindow(SW_SHOW);
			m_DlgButtonList->Invalidate();
		}
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		return CreateSolidBrush(RGB(249, 249, 249));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return CreateSolidBrush(RGB(250, 250, 250))/*hbr*/;
}


void CMyPotato::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

}


BOOL CMyPotato::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	BOOL bOk = CDialogEx::DestroyWindow();
	if (m_DlgButtonList!=NULL)
	{
		m_DlgButtonList->DestroyWindow();
		delete m_DlgButtonList;
		
		m_DlgButtonList = NULL;
	}
	return bOk;
}


BOOL CMyPotato::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
