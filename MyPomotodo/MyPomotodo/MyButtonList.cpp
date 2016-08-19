// MyButtonList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyButtonList.h"
#include "afxdialogex.h"
#include "FileUtil.h"

#define BUTTONEVEN 82000
#define WM_DELETEPOTATO (WM_USER + 3)

extern CMyDatabase g_MyDatabase;
// CMyButtonList �Ի���

IMPLEMENT_DYNAMIC(CMyButtonList, CDialogEx)

CMyButtonList::CMyButtonList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyButtonList::IDD, pParent)
{

}

CMyButtonList::~CMyButtonList()
{
}

void CMyButtonList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyButtonList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CMyButtonList ��Ϣ�������


BOOL CMyButtonList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	(CButton*)GetDlgItem(IDOK)->ShowWindow(SW_HIDE); 
	(CButton*)GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

	CString strImagePath = CFileUtil::NewFilePath2(_T("images\\button"));

	CRect rect,rcS;

	GetClientRect(&rect);
	rcS = rect;

	m_arrPotatoList.RemoveAll();

	g_MyDatabase.SelectTablePotato();

	int i=0;

	std::vector<POTATOINFO>::iterator iter;
	for(iter=g_MyDatabase.m_vPotatos.begin();iter!=g_MyDatabase.m_vPotatos.end();iter++)
	{
		CString strName = iter->strPotatoName;
		int nId = iter->nId;

		CMyPotatoListButton* myButton = new CMyPotatoListButton(nId, strImagePath+_T("1-1.png"), strImagePath+_T("potatoList-01.png"), strImagePath+_T("potatoList-02.png"), strImagePath+_T("potatoList-05.png"), strImagePath+_T("potatoList-03.png"), strImagePath+_T("potatoList-06.png"), strImagePath+_T("potatoList-04.png"), strImagePath+_T("2-2.png"), strImagePath+_T("potatoList-01.png"),strName);

		myButton->Create(_T("potato1"),WS_VISIBLE | WS_CHILD|BS_OWNERDRAW /*|WS_DISABLED*/,CRect(rect.left,rect.top+40*i,rect.right,rect.top+40*(i+1)),this,BUTTONEVEN+i);


		m_arrPotatoList.Add(myButton);

		if (rcS.bottom<rect.top+40*(i+1))
		{
			rcS.bottom = rect.top+40*(i+1);
		}

		i++;
	}

	MoveWindow(rect);

	m_page = 1;
	const SIZE sz = { rcS.right - rcS.left, rcS.bottom - rcS.top };    

	SCROLLINFO si;    
	si.cbSize = sizeof(SCROLLINFO);    
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;    
	si.nPos = si.nMin = 1;    

	si.nMax = sz.cy*m_page;    
	si.nPage = rect.bottom - rect.top;    
	SetScrollInfo(SB_VERT, &si, FALSE); 

	if (rect.bottom==rcS.bottom)
	{
		ModifyStyle(WS_VSCROLL,0);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CMyButtonList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return CreateSolidBrush(RGB(249, 249, 249))/*hbr*/;
}


void CMyButtonList::PreInitDialog()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::PreInitDialog();
}


void CMyButtonList::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	
	
}


BOOL CMyButtonList::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL bOk = CDialogEx::DestroyWindow();

	for (int i = 0;i<m_arrPotatoList.GetSize();i++)
	{
		CMyPotatoListButton* myButtonTest = (CMyPotatoListButton*)m_arrPotatoList.GetAt(i);
		if (myButtonTest!=NULL)
		{
			delete myButtonTest;
			myButtonTest = NULL;
		}
	}

	m_arrPotatoList.RemoveAll();

	return bOk;
}

void CMyButtonList::ScrollClient(int nBar, int nPos)
{
	static int s_prevx = 1;
	static int s_prevy = 1;

	int cx = 0;
	int cy = 0;

	int &delta = cy;
	int &prev = s_prevy;

	delta = prev - nPos;
	prev = nPos;

	if(cx || cy)
	{
		ScrollWindow(cx, cy, NULL, NULL);
	}
}

int CMyButtonList::GetScrollPos(int nBar, UINT nSBCode)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
	GetScrollInfo(nBar, &si);

	const int minPos = si.nMin;
	const int maxPos = si.nMax - (si.nPage - 1);

	int result = -1;

	    /* SB_BOTTOM �����ײ�

    SB_ENDSCROLL ��������.

    SB_LINEDOWN ���»���һ��.

    SB_LINEUP ���ϻ���һ��.

    SB_PAGEDOWN ���»���һҳ.

    SB_PAGEUP ���ϻ���һҳ.

    SB_THUMBPOSITION ���������������ڵ�λ�ã�λ����nPos�������ṩ

    SB_THUMBTRACK �������ڱ��϶�����������������λ����nPos�����ṩ

    SB_TOP ���黬���������� */

	switch(nSBCode)
	{
	case SB_LINEUP /*SB_LINELEFT*/:
		result = max(si.nPos - 1, minPos);
		break;
	case SB_LINEDOWN /*SB_LINERIGHT*/:
		result = min(si.nPos + 1, maxPos);
		break;
	case SB_PAGEUP /*SB_PAGELEFT*/:
		result = max(si.nPos - (int)si.nPage, minPos);
		break;
	case SB_PAGEDOWN /*SB_PAGERIGHT*/:
		result = min(si.nPos + (int)si.nPage, maxPos);
		break;
	case SB_THUMBPOSITION:
		// do nothing
		break;
	case SB_THUMBTRACK:
		result = si.nTrackPos;
		break;
	case SB_TOP /*SB_LEFT*/:
		result = minPos;
		break;
	case SB_BOTTOM /*SB_RIGHT*/:
		result = maxPos;
		break;
	case SB_ENDSCROLL:
		// do nothing
		break;
	}

	return result;
}

void CMyButtonList::VScrool(int nBar, UINT nSBCode)
{
	const int scrollPos = GetScrollPos(nBar, nSBCode);

	if(scrollPos == -1)
		return;

	SetScrollPos(nBar, scrollPos, TRUE);
	ScrollClient(nBar, scrollPos);
}

void CMyButtonList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	VScrool(SB_VERT, nSBCode);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


int CMyButtonList::updateList(void)
{
	for (int i = 0;i<m_arrPotatoList.GetSize();i++)
	{
		CMyPotatoListButton* myButtonTest = (CMyPotatoListButton*)m_arrPotatoList.GetAt(i);
		if (myButtonTest!=NULL)
		{
			delete myButtonTest;
			myButtonTest = NULL;
		}
	}

	init();

	return 0;
}


void CMyButtonList::init(void)
{
	CString strImagePath = CFileUtil::NewFilePath2(_T("images\\button"));

	CRect rect,rcS;

	GetClientRect(&rect);
	rcS = rect;

	m_arrPotatoList.RemoveAll();

	//m_MyDatabase.SelectTablePotato();
	g_MyDatabase.SelectTablePotato();

	int i=0;

	std::vector<POTATOINFO>::iterator iter;
	/*for(iter=m_MyDatabase.m_vPotatos.begin();iter!=m_MyDatabase.m_vPotatos.end();iter++)*/
	for(iter=g_MyDatabase.m_vPotatos.begin();iter!=g_MyDatabase.m_vPotatos.end();iter++)
	{
		CString strName = iter->strPotatoName;
		int nId = iter->nId;

		CMyPotatoListButton* myButton = new CMyPotatoListButton(nId, strImagePath+_T("1-1.png"), strImagePath+_T("potatoList-01.png"), strImagePath+_T("potatoList-02.png"), strImagePath+_T("potatoList-05.png"), strImagePath+_T("potatoList-03.png"), strImagePath+_T("potatoList-06.png"), strImagePath+_T("potatoList-04.png"), strImagePath+_T("2-2.png"), strImagePath+_T("potatoList-01.png"),strName);

		myButton->Create(_T("potato1"),WS_VISIBLE | WS_CHILD|BS_OWNERDRAW /*|WS_DISABLED*/,CRect(rect.left,rect.top+40*i,rect.right,rect.top+40*(i+1)),this,BUTTONEVEN+i);


		m_arrPotatoList.Add(myButton);

		if (rcS.bottom<rect.top+40*(i+1))
		{
			rcS.bottom = rect.top+40*(i+1);
		}

		i++;
	}

	//MoveWindow(rect);

	m_page = 1;
	const SIZE sz = { rcS.right - rcS.left, rcS.bottom - rcS.top };    

	SCROLLINFO si;    
	si.cbSize = sizeof(SCROLLINFO);    
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;    
	si.nPos = si.nMin = 1;    

	si.nMax = sz.cy*m_page;    
	si.nPage = rect.bottom - rect.top;    
	SetScrollInfo(SB_VERT, &si, FALSE); 

	if (rect.bottom==rcS.bottom)
	{
		ModifyStyle(WS_VSCROLL,0);
	}
}


void CMyButtonList::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nID==WM_DELETEPOTATO)
	{
		//��Ҫɾ��ѡ�е�button
		CString strIds = _T("");
		CString strTemp = _T("");
		for (int i = 0;i<m_arrPotatoList.GetSize();i++)
		{
			
			CMyPotatoListButton* myButtonTest = (CMyPotatoListButton*)m_arrPotatoList.GetAt(i);
			if (myButtonTest->GetSelected())
			{
				if (strIds.GetLength()>0)
				{
					strIds += _T(",");
				}

				strTemp.Format(_T("%d"), myButtonTest->m_nID);
				strIds += strTemp;
			}

			if (myButtonTest!=NULL)
			{
				delete myButtonTest;
				myButtonTest = NULL;
			}
		}

		CString strSql;
		strSql.Format(_T("UPDATE MyPotato SET Finish = 1 where ID in (%s)"), strIds);
		g_MyDatabase.UpdateSql(strSql);

		init();
	}   

	CDialogEx::OnSysCommand(nID, lParam);
}
