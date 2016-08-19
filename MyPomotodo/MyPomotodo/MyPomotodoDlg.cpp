
// MyPomotodoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyPomotodoDlg.h"
#include "afxdialogex.h"
#include <WinUser.h>
#include "AboutDlg.h"
#include "MySetting.h"


#include "FileUtil.h"
CMyDatabase g_MyDatabase;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPomotodoDlg �Ի���

#define TIME_START 2016
#define WM_MYABOUT (WM_USER + 4)
#define WM_MYSETTING (WM_USER + 5)
#define WM_MYHELP (WM_USER + 6)
#define WM_PAYMETALBELL (WM_USER + 7)
#define WM_POTATOTOTOMATO (WM_USER + 8)


#define MP3_TIME_START 2017


#define SLIDER_TIME_ELAPSE_MAX_POS 100000

//HHOOK g_hHookDm = NULL;
//HWND g_DestWndH = NULL;
//
//LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
//{
//	//�������ڵ���Ϣ���������Ϣ
//	if (WM_MOUSEMOVE<=wParam&&wParam<=WM_MOUSEWHEEL)
//	{
//		if (g_DestWndH!=NULL&&WM_LBUTTONDOWN==wParam)
//		{
//			::SendMessage(g_DestWndH, wParam, wParam, lParam);
//			//��깳��,lParam��MOUSEHOOKSTRUCT�ṹָ��
//			PMOUSEHOOKSTRUCT lpMsg = (PMOUSEHOOKSTRUCT)lParam;
//			lpMsg->hwnd = NULL;
//			lpMsg->dwExtraInfo = 0L;
//			lpMsg->pt = CPoint(0,0);
//			lpMsg->wHitTestCode = 0L;
//		} 
//		return 1;//��������ô���Ϣ�����´������ط�0
//	}
//	else
//	{
//		return ::CallNextHookEx(g_hHookDm, nCode, wParam, lParam);
//	}
//}

CMyPomotodoDlg::CMyPomotodoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYPOMOTODO_DIALOG, pParent)
	, m_pDlg(NULL)
	, m_btnButton(NULL)
	, m_pInitDlgInfo(NULL)
	, m_pInitButtonInfo(NULL)
	, m_bInitState(FALSE)
	, m_bTimeStartFirst(FALSE)
	, m_bTick(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPomotodoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TOMATO, m_EditAddTomato);
}

BEGIN_MESSAGE_MAP(CMyPomotodoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_COMMAND(WM_MYABOUT, OnMyAbout)
	ON_COMMAND(WM_MYSETTING, OnMySetting)
	ON_COMMAND(WM_MYHELP, OnMyHelp)
	ON_WM_CREATE()
	ON_COMMAND(WM_PAYMETALBELL, OnPaymetalbell)
END_MESSAGE_MAP()


// CMyPomotodoDlg ��Ϣ�������

BOOL CMyPomotodoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	g_MyDatabase.init();

	int iIndex = 0;

	m_pInitDlgInfo = new INITDLGINFO[DIALOG_COUNT];
	for (iIndex = 0;iIndex < DIALOG_COUNT;iIndex++)
	{
		switch (iIndex)
		{
			case DIALOG_POTATO_INDEX:
			{
				m_pInitDlgInfo[iIndex].uDialogTemplate = IDD_DIALOG_POTATO;
			}

			break;

			case DIALOG_TOMATO_INDEX:
			{
				m_pInitDlgInfo[iIndex].uDialogTemplate = IDD_DIALOG_TOMATO;
			}

			break;
		}
	}

	m_pInitButtonInfo = new INITBUTTONINFO[BUTTON_COUNT];
	for (iIndex = 0;iIndex < DIALOG_COUNT;iIndex++)
	{
		switch (iIndex)
		{
		case BUTTON_POTATO_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_POTATO;
			}

			break;

		case BUTTON_TOMATO_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_TOMATO_INDEX;
			}

			break;

		case BUTTON_WEBSITE_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_WEBSITE_INDEX;
			}

			break;

		case BUTTON_TOP_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_TOP_INDEX;
			}

			break;

		case BUTTON_OTHER_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_OTHER_INDEX;
			}

			break;

		case BUTTON_SET_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_SET_INDEX;
			}

			break;

		case BUTTON_CONTINUITY_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_CONTINUITY_INDEX;
			}

			break;

		case BUTTON_TIME_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_TIME_INDEX;
			}

			break;

		case BUTTON_START_INDEX:
			{
				m_pInitButtonInfo[iIndex].uButtonTemplate = IID_BUTTON_START_INDEX;
			}

			break;
		}
	}

	ToTray();

	
	g_SysConfigInfo = new INISYSCONFIGINFO;
	if (g_MyDatabase.InitSysConfigInfo(g_SysConfigInfo)==SQLITE_DONE)
	{
		g_MyDatabase.InsertSysConfigInfo();
	}
	
	if (g_SysConfigInfo->uState!=0)
	{
		Start();
	}

	//if (g_hHookDm==NULL)
	//{
	//	//���dwThreadidָ�����߳����ɵ�ǰ���̴��������ҹ��ӹ����ڵ�ʱ�����У���ôhMod��������ΪNULL.
	//	g_hHookDm = ::SetWindowsHookEx(WH_MOUSE, MouseProc, NULL, GetCurrentThreadId());
	//	if (g_hHookDm!=NULL)
	//	{
	//		g_DestWndH = m_hWnd;//����Ŀ�Ĵ��ھ��
	//	}
	//}
	m_MyMouseHook.StartHook(this->GetSafeHwnd());

	//mp3
	m_playerDll.LoadDLL(L"LibMP3DLL.dll");
	playing = false;
	pause = false;



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyPomotodoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyPomotodoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CMyPomotodoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_CENTER && !m_pDlg)
	{
		int iIndex = 0;

		m_pDlg = new CDialog*[DIALOG_COUNT];
		for (iIndex = 0;iIndex<DIALOG_COUNT;iIndex++)
		{
			switch (iIndex)
			{
				case 0:
					m_pDlg[iIndex] = new CMyPotato;
					break;
				case 1:
					m_pDlg[iIndex] = new CMyTomato;
					break;
				default:
					m_pDlg[iIndex] = new CDialogEx;
					break;
			}
		
			int iCmdShow = (iIndex == 0 ? SW_SHOW : SW_HIDE);
			CreateChildDialog(m_pDlg[iIndex], m_pInitDlgInfo[iIndex].uDialogTemplate, pWnd, this, iCmdShow);
		}

		CString strImagePath = CFileUtil::NewFilePath2(_T("images\\button"));
		CRect rect;
		GetClientRect(&rect);
		m_btnButton = new CMyButton*[BUTTON_COUNT];
		for (iIndex = 0;iIndex<BUTTON_COUNT;iIndex++)
		{
			switch (iIndex)
			{
			case BUTTON_POTATO_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("1-1.png"), strImagePath+_T("1-1.png"), strImagePath+_T("1-1.png"), strImagePath+_T("1-2.png"), strImagePath+_T("1-1.png"));

					m_btnButton[iIndex]->Create(_T("potato"),WS_VISIBLE | WS_CHILD |WS_DISABLED,CRect(rect.left+20,rect.bottom-40,rect.left+40+20,rect.bottom),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;

			case BUTTON_TOMATO_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("2-1.png"), strImagePath+_T("2-1.png"), strImagePath+_T("2-1.png"), strImagePath+_T("2-2.png"), strImagePath+_T("2-1.png"));

					m_btnButton[iIndex]->Create(_T("tomato"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.left+20+20+40,rect.bottom-40,rect.left+40+20+20+40,rect.bottom),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;

			case BUTTON_WEBSITE_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("3-1.png"), strImagePath+_T("3-1.png"), strImagePath+_T("3-1.png"), strImagePath+_T("3-1.png"), strImagePath+_T("3-1.png"));

					m_btnButton[iIndex]->Create(_T("website"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.left+20+20+40+20+40,rect.bottom-40,rect.left+40+20+20+40+20+40,rect.bottom),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;

			case BUTTON_TOP_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("4-1.png"), strImagePath+_T("4-1.png"), strImagePath+_T("4-1.png"), strImagePath+_T("4-2.png"), strImagePath+_T("4-1.png"));

					m_btnButton[iIndex]->Create(_T("top"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.right-20-40-20-40-20-40,rect.bottom-40,rect.right-20-40-20-40-20,rect.bottom),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;

			case BUTTON_OTHER_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("5-1.png"), strImagePath+_T("5-1.png"), strImagePath+_T("5-1.png"), strImagePath+_T("5-1.png"), strImagePath+_T("5-1.png"));

					m_btnButton[iIndex]->Create(_T("other"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.right-20-40-20-40,rect.bottom-40,rect.right-20-40-20,rect.bottom),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;

			case BUTTON_SET_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("6-1.png"), strImagePath+_T("6-1.png"), strImagePath+_T("6-1.png"), strImagePath+_T("6-1.png"), strImagePath+_T("6-1.png"));

					m_btnButton[iIndex]->Create(_T("set"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.right-20-40,rect.bottom-40,rect.right-20,rect.bottom),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;

			case BUTTON_CONTINUITY_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("top-1.png"), strImagePath+_T("top-1.png"), strImagePath+_T("top-1.png"), strImagePath+_T("top-2.png"), strImagePath+_T("top-1.png"));

					m_btnButton[iIndex]->Create(_T("continuity"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.left+10,rect.top,rect.left+60+10,rect.top+60),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;

			case BUTTON_TIME_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("top-3.png"), strImagePath+_T("top-3.png"), strImagePath+_T("top-3.png"), strImagePath+_T("top-3.png"), strImagePath+_T("top-3.png"));

					m_btnButton[iIndex]->Create(_T("time"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.right/2-30,rect.top,rect.right/2+30,rect.top+60),this,m_pInitButtonInfo[iIndex].uButtonTemplate);

					//m_btnButton[iIndex]->ShowWindow(SW_SHOW);
				}

				break;

			case BUTTON_START_INDEX:
				{
					m_btnButton[iIndex] = new CMyButton(strImagePath+_T("top-4.png"), strImagePath+_T("top-4.png"), strImagePath+_T("top-4.png"), strImagePath+_T("top-5.png"), strImagePath+_T("top-4.png"));

					m_btnButton[iIndex]->Create(_T("start"),WS_VISIBLE | WS_CHILD/* |WS_DISABLED*/,CRect(rect.right-60-10,rect.top,rect.right-10,rect.top+60),this,m_pInitButtonInfo[iIndex].uButtonTemplate);
				}

				break;
			}
		}
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return CreateSolidBrush(RGB(255, 255, 255));/*hbr*/;	//��������Ϊ��ɫ
}


void CMyPomotodoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	//mp3
	if(playing)
	{
		m_playerDll.Stop();
	}

	m_playerDll.Cleanup();
	m_playerDll.UnloadDLL();

	//

	if (m_pInitDlgInfo)
		delete[] m_pInitDlgInfo;
	m_pInitDlgInfo = NULL;

	if (m_pDlg)
	{
		for (int iIndex = 0;iIndex < DIALOG_COUNT;iIndex++)
		{
			if (m_pDlg[iIndex])
			{
				m_pDlg[iIndex]->DestroyWindow();
				delete m_pDlg[iIndex];
			}

			m_pDlg[iIndex] = NULL;
		}
		delete[] m_pDlg;
	}
	m_pDlg = NULL;

	if (g_SysConfigInfo!=NULL)
	{
		delete g_SysConfigInfo;
		g_SysConfigInfo = NULL;
	}

	
	/*if (g_hHookDm!=NULL)
	{
	UnhookWindowsHookEx(g_hHookDm);
	g_DestWndH = NULL;
	}*/

	m_MyMouseHook.StopHook();

	DeleteTray();
}


// �����Ӵ���
void CMyPomotodoDlg::CreateChildDialog(CDialog *pDialogEx, UINT uIDTemplate, CWnd *pStatic, CWnd *pParent, int iCmdShow)
{
	CRect rect;
	if (pDialogEx->Create(uIDTemplate, pParent))
	{
		pStatic->GetWindowRect(&rect);
		pParent->ScreenToClient(&rect);
		rect.DeflateRect(0, 1, 0, 0);
		pDialogEx->MoveWindow(&rect);
		(reinterpret_cast<CDialogEx *>(pDialogEx))->ShowWindow(iCmdShow);
	}
}

BOOL CMyPomotodoDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL bOk = CDialogEx::DestroyWindow();

	if (m_pInitButtonInfo)
		delete[] m_pInitButtonInfo;
	m_pInitButtonInfo = NULL;

	if (m_btnButton)
	{
		for (int iIndex = 0;iIndex < BUTTON_COUNT;iIndex++)
		{
			if (m_btnButton[iIndex])
				delete m_btnButton[iIndex];
			m_btnButton[iIndex] = NULL;
		}
		delete[] m_btnButton;
	}
	m_btnButton = NULL;

	return bOk;
}


void CMyPomotodoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CMyPomotodoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (pMsg->message==WM_KEYDOWN)
	{
		if ( VK_RETURN == pMsg->wParam )
		{
			// ���»س�
			// ��ȡ������
			HWND hFocus = ::GetFocus();
			if ( hFocus == m_EditAddTomato.GetSafeHwnd() )
			{
				// ��������߼�
				//OnBnClickedButtonAddpotato();
				UpdateData(TRUE);
				CString strSQL;
				CString strTemp;
				m_EditAddTomato.GetWindowText(strTemp);
				strTemp.Trim();
				strSQL.Format(_T("insert into MyTomato(TomatoName,BeigTime,EndTime) values  (\"%s\",\"%s\",\"%s\")"),strTemp,g_SysConfigInfo->strWorkTime,
					m_myTime.TimeToString(m_myTime.GetNowTime()));
				g_MyDatabase.InsertTomato(strSQL);

				ToRest();
				/*InvalidateRect(linRect,TRUE);
				UpdateWindow();*/
				m_pDlg[DIALOG_TOMATO_INDEX]->SendMessage(WM_SYSCOMMAND, WM_INITTOMATO,0);
				/*m_EditAddTomato.ShowWindow(SW_HIDE);

				m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_SHOW);
				m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_SHOW);
				m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_SHOW);*/
			}
		}
	}

	if (pMsg->message==WM_LBUTTONUP)
	{
		if (!m_btnButton[BUTTON_TOP_INDEX]->IsWindowEnabled())
		{
			CRect rect;
			m_btnButton[BUTTON_TOP_INDEX]->GetWindowRect(&rect);

			if (pMsg->pt.x>=rect.left&&pMsg->pt.x<=rect.right
				&&pMsg->pt.y>=rect.top&&pMsg->pt.y<=rect.bottom)
			{
				m_btnButton[BUTTON_TOP_INDEX]->EnableWindow(TRUE);
				SetWindowPos(&this->wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE); 
			}
		}

		if (!m_btnButton[BUTTON_CONTINUITY_INDEX]->IsWindowEnabled())
		{
			CRect rect;
			m_btnButton[BUTTON_CONTINUITY_INDEX]->GetWindowRect(&rect);

			if (pMsg->pt.x>=rect.left&&pMsg->pt.x<=rect.right
				&&pMsg->pt.y>=rect.top&&pMsg->pt.y<=rect.bottom)
			{
				m_btnButton[BUTTON_CONTINUITY_INDEX]->EnableWindow(TRUE);
			}
		}

		if (!m_btnButton[BUTTON_START_INDEX]->IsWindowEnabled())
		{
			CRect rect;
			m_btnButton[BUTTON_START_INDEX]->GetWindowRect(&rect);

			if (pMsg->pt.x>=rect.left&&pMsg->pt.x<=rect.right
				&&pMsg->pt.y>=rect.top&&pMsg->pt.y<=rect.bottom)
			{
				if (IDOK==AfxMessageBox(_T("��Ŀǰ����һ�����ѹ���ʱ���У����Ҫ�˳���"),MB_OKCANCEL | MB_ICONQUESTION))
				{
					m_btnButton[BUTTON_START_INDEX]->EnableWindow(TRUE);

					KillTimer(TIME_START);

					StopMp3();

					initHear();

					m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_SHOW);
					m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_SHOW);
					m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_SHOW);
					m_btnButton[BUTTON_START_INDEX]->EnableWindow(TRUE);

					g_MyDatabase.UpdateSql(_T("update SysConfigInfo set State=0"));
					g_SysConfigInfo->uState = 0;
				}
			}
		}

		for (int iIndex = 0;iIndex<BUTTON_COUNT;iIndex++)
		{
			if (pMsg->hwnd == m_btnButton[iIndex]->m_hWnd)
			{
				switch (iIndex)
				{
				case BUTTON_POTATO_INDEX:
					{
						m_pDlg[DIALOG_POTATO_INDEX]->ShowWindow(SW_SHOW);
						m_pDlg[DIALOG_TOMATO_INDEX]->ShowWindow(SW_HIDE);
						SetButtonShow(iIndex);
					}

					break;

				case BUTTON_TOMATO_INDEX:
					{
						m_pDlg[DIALOG_POTATO_INDEX]->ShowWindow(SW_HIDE);
						m_pDlg[DIALOG_TOMATO_INDEX]->ShowWindow(SW_SHOW);
						SetButtonShow(iIndex);
					}

					break;

				case BUTTON_WEBSITE_INDEX:
					{
						ShellExecute(NULL, _T("open"), _T("http://blog.leanote.com/yhcao"), NULL, NULL, SW_SHOWNORMAL);
					}

					break;

				case BUTTON_TOP_INDEX:
					{
						m_btnButton[BUTTON_TOP_INDEX]->EnableWindow(FALSE);
						SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE); 
					}

					break;

				case BUTTON_CONTINUITY_INDEX:
					{
						m_btnButton[BUTTON_CONTINUITY_INDEX]->EnableWindow(FALSE);
					}

					break;

				case BUTTON_TIME_INDEX:
					{
						/*m_btnButton[BUTTON_CONTINUITY_INDEX]->EnableWindow(FALSE);*/
					}

					break;

				case BUTTON_START_INDEX:
					{
						m_btnButton[BUTTON_START_INDEX]->EnableWindow(FALSE);
						Start();	
					}

					break;

				case BUTTON_SET_INDEX:
					{
						PostMessage(WM_COMMAND, WM_MYSETTING,0);
					}

					break;

				default:
					{
						//m_btnButton[iIndex]->EnableWindow(FALSE);
						//m_pDlg[iIndex]->ShowWindow(SW_SHOW);
					}
					break;
				}
			}
		}	
	}

	//if (pMsg->message==WM_KEYDOWN)
	//{
	//	if ( VK_RETURN == pMsg->wParam )
	//	{
	//		// ���»س�
	//		// ��ȡ������
	//		HWND hFocus = ::GetFocus();
	//		//if ( hFocus == m_btnButton[0]->m_EditAddPotato.GetSafeHwnd() )
	//		//{
	//		//	// ��������߼�
	//		//}
	//	}
	//}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyPomotodoDlg::SetButtonShow(int nIndex)
{
	for (int iIndex=0;iIndex<4/*BUTTON_COUNT*/;iIndex++)
	{
		if (iIndex==nIndex)
		{
			m_btnButton[iIndex]->EnableWindow(FALSE);
		} 
		else
		{
			m_btnButton[iIndex]->EnableWindow(TRUE);
		}
	}
}


void CMyPomotodoDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CMyPomotodoDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CMyPomotodoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (nIDEvent == TIME_START)
	{
		if(!m_bTimeStartFirst)
		{
			if (m_btnButton[BUTTON_CONTINUITY_INDEX]!=NULL&&m_btnButton[BUTTON_TIME_INDEX]!=NULL&&m_btnButton[BUTTON_START_INDEX]!=NULL)
			{
				m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_SHOW);
				m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_HIDE);
				m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_SHOW);
				m_btnButton[BUTTON_START_INDEX]->EnableWindow(FALSE);
				m_bTimeStartFirst = TRUE;
			}
		}

		//��ʱ����ʾ
		CRect rect,linRect;
		GetClientRect(&rect);
		rect.bottom = 60;
		linRect = rect;
		rect.left+=100;
		rect.right-=100;

		bool bEnd;

		CDC* pDc = GetDC();

		CFont font;

		font.CreateFont(
			30, // nHeight
			0, // nWidth
			0, // nEscapement
			0, // nOrientation
			FW_NORMAL, // nWeight
			FALSE, // bItalic
			FALSE, // bUnderline
			0, // cStrikeOut
			ANSI_CHARSET, // nCharSet
			OUT_DEFAULT_PRECIS, // nOutPrecision
			CLIP_DEFAULT_PRECIS, // nClipPrecision
			DEFAULT_QUALITY, // nQuality
			DEFAULT_PITCH | FF_SWISS,
			_T("����") // nPitchAndFamily Arial
			);
		CFont* oldFont = pDc->SelectObject(&font);

		if (g_SysConfigInfo->uState == 1)
		{
			pDc->SetTextColor(RGB(226,66,66));
		} 
		else
		{
			pDc->SetTextColor(RGB(62,149,96));
		}
		
		pDc->SetBkMode(TRANSPARENT);
		InvalidateRect(rect,TRUE);
		UpdateWindow();

		double dRatio = 0.0;

		pDc->DrawText(GetStrTimeSpan(bEnd, dRatio), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		if (!bEnd&&!playing)
		{
			m_bTick = TRUE;
			PlayMp3();
		}

		//mp3
		if(playing&&m_bTick)
		{
			long EvCode = 0;
			bool b = m_playerDll.WaitForCompletion(0, &EvCode);

			if(b)
			{
				StopMp3();
				TRACE(L"Playing stopped");
			}
			else
			{
				if (g_SysConfigInfo->uState!=0&&m_bTick)
				{
					__int64 duration = m_playerDll.GetDuration();
					__int64 pos =  0* duration/SLIDER_TIME_ELAPSE_MAX_POS;;
					m_playerDll.SetPositions(&pos, &duration, true);

				}
			}
		}	

		pDc->SelectObject ( oldFont);

		//��������

		CPen pen;
		pen.CreatePen(PS_SOLID,3,RGB(112,143,236));
		CPen *oldPen=pDc->SelectObject(&pen);//����DCԭʼ����

		pDc->MoveTo(linRect.left, rect.bottom+2);
		pDc->LineTo(linRect.right*dRatio, rect.bottom+2);

		pDc->SelectObject(oldPen);       //�ظ�DCԭ����

		ReleaseDC(pDc);

		if (bEnd)
		{
			KillTimer(TIME_START);
			if (m_bTick)
			{
				StopMp3();
				m_bTick = FALSE;
				PlayMp3();
			}
			
			if (g_SysConfigInfo->uState == 2)//��Ϣ����,תΪ������
			{
				ToInitialState();
			} 
			else if(g_SysConfigInfo->uState == 1)	//����������תΪ���빤�����ѻ�����
			{
				ToFill();
			}
		}
	}

	//mp3
	//if(nIDEvent == MP3_TIME_START)
	//{
	//	////mp3
	//	if(playing)
	//	{
	//		long EvCode = 0;
	//		bool b = m_playerDll.WaitForCompletion(0, &EvCode);

	//		if(b)
	//		{
	//			StopMp3();
	//			TRACE(L"Playing stopped");
	//		}
	//	}		
	//}

	CDialogEx::OnTimer(nIDEvent);
}


int CMyPomotodoDlg::Start(void)
{
	if (g_SysConfigInfo->uState != 0&&!m_bInitState)
	{
		m_myTime.SetStartTime(m_myTime.StringToTime(g_SysConfigInfo->strWorkRestTime));
	} 
	else
	{
		m_myTime.SetStartTime(m_myTime.GetNowTime());
	}

	//m_bTick = TRUE;
	StopMp3();
	//m_bTick = FALSE;

	SetTimer(TIME_START, 1000, NULL);

	if (m_bInitState)
	{
		CString strTime;
		strTime.Format(_T("update SysConfigInfo set WorkRestTime=\"%s\""), m_myTime.TimeToString(m_myTime.GetNowTime()));
		g_MyDatabase.UpdateSql(strTime);
		g_SysConfigInfo->strWorkRestTime = strTime;

		if (g_SysConfigInfo->uState == 0)
		{
			CString strWorkTime;
			g_SysConfigInfo->strWorkTime = m_myTime.TimeToString(m_myTime.GetNowTime());
			strWorkTime.Format(_T("update SysConfigInfo set WorkTime=\"%s\""), g_SysConfigInfo->strWorkTime);
			g_MyDatabase.UpdateSql(strWorkTime);
		}
	}
	
	if (g_SysConfigInfo->uState == 0)
	{
		m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_SHOW);
		m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_HIDE);
		m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_SHOW);

		g_MyDatabase.UpdateSql(_T("update SysConfigInfo set State=1"));
		g_SysConfigInfo->uState = 1;
	} 

	if (!m_bInitState)
	{
		m_bInitState = TRUE;
	}
	return 0;
}


CString CMyPomotodoDlg::GetStrTimeSpan(bool &bEnd, double &dRatio)
{
	bEnd = false;

	LONGLONG lTime = 25;
	
	switch (g_SysConfigInfo->uState)
	{
	case 1:
		lTime = g_SysConfigInfo->lTomatoTime;
		break;
	case 2:
		lTime = g_SysConfigInfo->lRestTime;
		break;
	default:
		lTime = 25;
		break;
	}

	CString strTime;

	LONGLONG lSpanMintes = lTime-m_myTime.GetTimeSpanTotalMinutes();
	LONGLONG lSpanSeconds = lTime*60 - m_myTime.GetTimeSpanTotalSeconds();
	dRatio = (double)m_myTime.GetTimeSpanTotalSeconds()/(lTime*60);
	
	if (lSpanSeconds<0)
	{
		bEnd = true;
		return _T("00:00");
	}

	if (m_myTime.GetTimeSpanTotalSeconds()>0&&lSpanMintes>0)
	{
		lSpanMintes--;
	}

	CString strSeconds;
	strSeconds.Format(_T("%0.2ld"), (lSpanSeconds)%60);

	CString strMinutes;
	
	if (lSpanMintes<60)
	{
		strMinutes.Format(_T("%0.2ld"), lSpanMintes);

		strTime.Format(_T("%s:%s"), strMinutes,strSeconds);
		return strTime;
	}
	else
	{
		if (lSpanMintes<60*24)
		{
			strMinutes.Format(_T("%0.2ld"), lSpanMintes%60);

			CString strHours;
			strHours.Format(_T("%0.2ld"), lSpanMintes/60);

			strTime.Format(_T("%s:%s:%s"), strHours,strMinutes,strSeconds);
			return strTime;
		} 
		else
		{
			strMinutes.Format(_T("%0.2ld"), lSpanMintes%60);

			CString strHours;
			strHours.Format(_T("%0.2ld"), (lSpanMintes%(60*24))/60);

			CString strDays;
			strDays.Format(_T("%0.2ld"), lSpanMintes/(60*24));

			strTime.Format(_T("%sDay %s:%s:%s"), strDays,strHours,strMinutes,strSeconds);
			return strTime;
		}
	}

	return strTime;
}


void CMyPomotodoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nID==WM_TOTASK&&this->IsWindowVisible())
	{
		ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);//����������
		
		//ToTray(); //��С�������̵ĺ���
	}               

	if(nID==WM_POTATOTOTOMATO)
	{
		CString str((TCHAR*)lParam); 
		if (m_EditAddTomato.IsWindowVisible())
		{
			m_EditAddTomato.SetWindowText(str);
		}
		
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

//�����������ͼ�� ��С�������̺���
void CMyPomotodoDlg::ToTray(void)
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(nid.szTip, _T("������������"));//��Ϣ��ʾ��
	Shell_NotifyIcon(NIM_ADD, &nid);//�����������ͼ��
	ShowWindow(SW_HIDE);//����������
}

//�ָ����溯��
LRESULT CMyPomotodoDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
	{
		return 1;
	}
	switch(lParam)
	{
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ���ر�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();//����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_MYABOUT, _T("����"));
			menu.AppendMenu(MF_STRING, WM_MYSETTING, _T("ƫ������"));
			menu.AppendMenu(MF_STRING, WM_MYHELP, _T("��������"));
			//���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ���
			//���أ��������������
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�˳�Ӧ��"));
			//ȷ������ʽ�˵���λ��
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
			//��Դ����
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK://˫������Ĵ���
		{
			this->ShowWindow(SW_SHOW);//�򵥵���ʾ������
			this->ShowWindow(SW_RESTORE);
			//DeleteTray();
		}
		break;
	default:
		break;
	}
	return 0;
}

void CMyPomotodoDlg::OnMyAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();

}

void CMyPomotodoDlg::OnMySetting()
{
	MySetting dlg;
	dlg.SetSysConfigInfo(g_SysConfigInfo);
	dlg.DoModal();
	g_MyDatabase.UpdateSysConfigInfo(g_SysConfigInfo);
}

void CMyPomotodoDlg::OnMyHelp()
{
	ShellExecute(NULL, _T("open"), _T("http://blog.leanote.com/yhcao"), NULL, NULL, SW_SHOWNORMAL);
}

void CMyPomotodoDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(nid.szTip, _T("������������"));//��Ϣ��ʾ��Ϊ�����ƻ��������ѡ�
	Shell_NotifyIcon(NIM_DELETE, &nid);//��������ɾ��ͼ��
}

int CMyPomotodoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//�޸ķ��ʹ����������������ʾ
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	return 0;
}


void CMyPomotodoDlg::initHear(void)
{
	CRect rect,linRect;
	GetClientRect(&rect);
	rect.bottom = 60;
	linRect = rect;
	rect.left+=100;
	rect.right-=100;
	linRect.top=linRect.bottom;
	linRect.bottom+=4;

	InvalidateRect(rect,TRUE);
	InvalidateRect(linRect,TRUE);
	UpdateWindow();
}


void CMyPomotodoDlg::ToRest(void)
{
	g_MyDatabase.UpdateSql(_T("update SysConfigInfo set State=2"));
	g_SysConfigInfo->uState = 2;

	initHear();

	m_EditAddTomato.ShowWindow(SW_HIDE);

	m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_SHOW);
	m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_HIDE);
	m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_SHOW);
	m_btnButton[BUTTON_START_INDEX]->EnableWindow(FALSE);

	Start();
}


void CMyPomotodoDlg::ToInitialState(void)
{
	g_MyDatabase.UpdateSql(_T("update SysConfigInfo set State=0"));
	g_SysConfigInfo->uState = 0;

	initHear();

	m_EditAddTomato.ShowWindow(SW_HIDE);

	m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_SHOW);
	m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_SHOW);
	m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_SHOW);
	m_btnButton[BUTTON_START_INDEX]->EnableWindow(TRUE);

	/*m_EditAddTomato.ShowWindow(SW_SHOW);

	m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_HIDE);
	m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_HIDE);
	m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_HIDE);*/
}


void CMyPomotodoDlg::ToFill(void)
{
	initHear();

	m_EditAddTomato.ShowWindow(SW_SHOW);

	m_btnButton[BUTTON_CONTINUITY_INDEX]->ShowWindow(SW_HIDE);
	m_btnButton[BUTTON_TIME_INDEX]->ShowWindow(SW_HIDE);
	m_btnButton[BUTTON_START_INDEX]->ShowWindow(SW_HIDE);
	m_btnButton[BUTTON_START_INDEX]->EnableWindow(FALSE);

	//Start();
}


void CMyPomotodoDlg::PlayMp3(void)
{
	StopMp3();

	if(pause)
	{
		m_playerDll.Play();
		pause = false;
	}
	else
	{
		CString file;
		file = CFileUtil::NewFilePath2(_T("mp3"));

		if (m_bTick)
		{
			file += _T("tick.mp3");
		}
		else
		{
			file += _T("metalbell.mp3");
		}
		

		if(file==L"")
		{
			MessageBox(L"No MP3 file is specified!", L"Error");
			return;
		}

		if(FileExists(file)==false)
		{
			MessageBox(L"MP3 file does not exists!", L"Error");
			return;
		}

		if (m_playerDll.Load(file))
		{
			if (m_playerDll.Play())
			{
				playing = true;
				pause = false;
		
				//this->SetTimer(MP3_TIME_START, 1000, NULL);
				
				m_playerDll.SetVolume(GetVolume());

			} 
			else
			{
				MessageBox(_T("����ʧ��"), L"Error");
			}
		}
		else
		{
			MessageBox(_T("����ʧ��"), L"Error");
		}
		/*if(m_playerDll.Load(file)&&m_playerDll.Play())
		{
			playing = true;
			pause = false;
			
			this->SetTimer(MP3_TIME_START, 1000, NULL);

			m_playerDll.SetVolume(GetVolume());

			m_bTick = TRUE;
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("Cannot play this file��\r\n%s"),file);
			MessageBox(strTemp, L"Error");
			return;
		}*/
	}
}


void CMyPomotodoDlg::StopMp3(void)
{
	if(m_playerDll.Stop())
	{
		playing = false;
		pause = false;

		//this->KillTimer(MP3_TIME_START);
	}
}


void CMyPomotodoDlg::PauseMp3(void)
{
	if(m_playerDll.Pause())
	{
		pause = true;
	}
}

/* Return TRUE if file 'fileName' exists */
bool CMyPomotodoDlg::FileExists(const TCHAR *fileName)
{
	DWORD       fileAttr;

	fileAttr = GetFileAttributes(fileName);
	if (0xFFFFFFFF == fileAttr)
		return false;
	return true;
}

int CMyPomotodoDlg::GetVolume()
{
	int vol = 10000;
	vol = 10000 - vol;
	vol = -vol;

	return vol;
}

afx_msg void CMyPomotodoDlg::OnPaymetalbell()
{
	
}
