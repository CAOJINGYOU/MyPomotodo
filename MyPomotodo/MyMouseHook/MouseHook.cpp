// MouseHook.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MouseHook.h"
#define  WM_TOTASK (WM_USER + 2)

#include <afxwin.h>
#include <afxdllx.h>

#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma data_seg("SharedDataName")

HHOOK g_mouseHook;
HHOOK g_keyboardHook;

HWND g_hwnd=NULL;

HINSTANCE glhInstance=NULL; //DLLʵ�����

#pragma data_seg()

#pragma comment(linker,"/section:.SharedDataName,rws")
// CMouseHook

static AFX_EXTENSION_MODULE MyMouseHookDLL = { NULL, NULL };

extern "C" int APIENTRY
	DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	char* old_locale = _strdup( setlocale(LC_ALL,NULL) );
	setlocale( LC_ALL, "chs" );

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MyMouseHook.DLL ���ڳ�ʼ��!\n");

		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(MyMouseHookDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL (�� ActiveX �ؼ�)��ʽ���ӵ���
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(MyMouseHookDLL);
		glhInstance=hInstance; //���뱣��DLL
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MyMouseHook.DLL ������ֹ!\n");

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(MyMouseHookDLL);
	}

	setlocale( LC_ALL, old_locale);
	free(old_locale); 
	return 1;   // ȷ��
}


//���Ӻ�����ʵ�֣� 
//LRESULT WINAPI MouseProc(int nCode,WPARAM wparam,LPARAM lparam)
//{
//	LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *)lparam;
//	if (nCode>=0)
//	{
//		if (WM_LBUTTONDOWN==wparam)
//		{
//			
//			//��깳��,lParam��MOUSEHOOKSTRUCT�ṹָ��
//			PMOUSEHOOKSTRUCT lpMsg = (PMOUSEHOOKSTRUCT)lparam;
//			lpMsg->hwnd = NULL;
//			lpMsg->dwExtraInfo = 0L;
//			lpMsg->pt = CPoint(0,0);
//			lpMsg->wHitTestCode = 0L;
//		} 
//
//		/*============================================================================
//		���´����ǵõ������ڱ����ı�������
//		HWND glhTargetWnd=pMouseHook->hwnd;     //ȡĿ�괰�ھ��
//		HWND ParentWnd=glhTargetWnd;
//		while (ParentWnd !=NULL)
//		{
//			glhTargetWnd=ParentWnd;
//			ParentWnd=GetParent(glhTargetWnd);   //ȡӦ�ó��������ھ��
//		}
//		===========================================================================*/
//		//HWND glhTargetWnd=XYZWindowFromPoint(NULL,pMouseHook->pt);    //�������һ��ע�͵��Ĵ����滻�����ǵõ������ڱ����ı�������
//		//if(glhTargetWnd!=glhPrevTarWnd)
//		//{
//		//	char szCaption[256];
//		//	GetWindowText(glhTargetWnd,szCaption,100);
//		//	//ȡĿ�괰�ڱ���
//		//	if(IsWindow(glhDisplayWnd))
//		//		SendMessage(glhDisplayWnd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)szCaption);
//		//	glhPrevTarWnd=glhTargetWnd;
//		//	//����Ŀ�괰��
//		//}
//	}
//	return CallNextHookEx(glhHook,nCode,wparam,lparam);
//	//����������Ϣ
//}

LRESULT CALLBACK MouseProc(
	int nCode,      // hook code
	WPARAM wParam,  // message identifier
	LPARAM lParam   // mouse coordinates
	) //��깳�ӹ���
{
	LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *)lParam;
		if (nCode>=0)
		{
			if (WM_LBUTTONDOWN==wParam)
			{
				
				//��깳��,lParam��MOUSEHOOKSTRUCT�ṹָ��
				PMOUSEHOOKSTRUCT lpMsg = (PMOUSEHOOKSTRUCT)lParam;
				CPoint point = lpMsg->pt;
				
				RECT rect;
				::GetWindowRect(g_hwnd, &rect);	//�õ�������������Ļ�ϵľ��ο�λ��

				if ((point.x<rect.left||point.x>rect.right)||(point.y<rect.top||point.y>rect.bottom))
				{
					::SendMessage(g_hwnd,WM_SYSCOMMAND, WM_TOTASK,0);

				}
			} 
		}
		return CallNextHookEx(g_mouseHook,nCode,wParam,lParam);
}

LRESULT CALLBACK KeyboardProc(
	int code,       // hook code
	WPARAM wParam,  // virtual-key code
	LPARAM lParam   // keystroke-message information
	)//���̹��ӹ���
{
	if(VK_F2==wParam)
	{
		::SendMessage(g_hwnd,WM_CLOSE,0,0);
		::UnhookWindowsHookEx(g_mouseHook);
		::UnhookWindowsHookEx(g_keyboardHook);
	}
	else
		return 1;
}

CMouseHook::CMouseHook()
{
}

CMouseHook::~CMouseHook()
{
}


// CMouseHook ��Ա����

//��װ���Ӳ��趨������ʾ���ھ��
BOOL CMouseHook::StartHook(HWND hWnd)
{
	BOOL bResult=FALSE;
	g_hwnd=hWnd;

	g_mouseHook=::SetWindowsHookEx(WH_MOUSE,MouseProc,glhInstance/*::GetModuleHandle(_T("MyMouseHook.dll"))*/,0); 
	//g_keyboardHook=::SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,::GetModuleHandle(_T("MyMouseHook.dll")),0);
	/*=================================================================================
    HHOOK SetWindowsHookEx( int idHook,HOOKPROC lpfn, INSTANCE hMod,DWORD dwThreadId )
��������idHook��ʾ�������ͣ����Ǻ͹��Ӻ�������һһ��Ӧ�ġ�
    ���磬WH_KEYBOARD��ʾ��װ���Ǽ��̹��ӣ�WH_MOUSE��ʾ����깳�ӵȵȡ� 

����Lpfn�ǹ��Ӻ����ĵ�ַ�� 

����HMod�ǹ��Ӻ������ڵ�ʵ���ľ���������̹߳��ӣ��ò���ΪNULL��
    ����ϵͳ���ӣ��ò���Ϊ���Ӻ������ڵ�DLL����� 

����dwThreadId ָ�����������ӵ��̵߳��̺߳š�����ȫ�ֹ��ӣ��ò���ΪNULL�� 

����SetWindowsHookEx��������װ�Ĺ��Ӿ����
    ֵ��ע������̹߳��Ӻ�ϵͳ���ӵĹ��Ӻ�����λ���кܴ�Ĳ��
	�̹߳���һ���ڵ�ǰ�̻߳��ߵ�ǰ�߳��������߳��ڣ�
	��ϵͳ���ӱ�����ڶ����Ķ�̬���ӿ��У�ʵ������Ҫ�鷳һЩ�� 
	==================================================================================*/
	if(g_mouseHook!=NULL)
		bResult=TRUE;
	//glhDisplayWnd=hWnd;
	//������ʾĿ�괰�ڱ���༭��ľ��
	return bResult; 
}

//ж�ع���
BOOL CMouseHook::StopHook() 
{
	BOOL bResult=FALSE;
	if(g_mouseHook)
	{
		bResult= UnhookWindowsHookEx(g_mouseHook);
		if(bResult)
		{
			g_mouseHook=NULL;
		}
	}
	return bResult;
}
