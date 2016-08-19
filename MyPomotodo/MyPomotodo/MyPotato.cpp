// MyPotato.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyPotato.h"
#include "afxdialogex.h"

// CMyPotato �Ի���
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


// CMyPotato ��Ϣ�������


BOOL CMyPotato::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message==WM_KEYDOWN)
	{
		if ( VK_RETURN == pMsg->wParam )
		{
			// ���»س�
			// ��ȡ������
			HWND hFocus = ::GetFocus();
			if ( hFocus == m_EditAddPotato.GetSafeHwnd() )
			{
				// ��������߼�
				OnBnClickedButtonAddpotato();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyPotato::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	///CDialogEx::OnOK();
}


void CMyPotato::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CMyPotato::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMyPotato::OnBnClickedButtonAddpotato()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

	// TODO:  �ڴ˸��� DC ���κ�����
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

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return CreateSolidBrush(RGB(250, 250, 250))/*hbr*/;
}


void CMyPotato::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

}


BOOL CMyPotato::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
