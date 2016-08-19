// MouseHook.cpp : 实现文件
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

HINSTANCE glhInstance=NULL; //DLL实例句柄

#pragma data_seg()

#pragma comment(linker,"/section:.SharedDataName,rws")
// CMouseHook

static AFX_EXTENSION_MODULE MyMouseHookDLL = { NULL, NULL };

extern "C" int APIENTRY
	DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// 如果使用 lpReserved，请将此移除
	UNREFERENCED_PARAMETER(lpReserved);

	char* old_locale = _strdup( setlocale(LC_ALL,NULL) );
	setlocale( LC_ALL, "chs" );

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MyMouseHook.DLL 正在初始化!\n");

		// 扩展 DLL 一次性初始化
		if (!AfxInitExtensionModule(MyMouseHookDLL, hInstance))
			return 0;

		// 将此 DLL 插入到资源链中
		// 注意: 如果此扩展 DLL 由
		//  MFC 规则 DLL (如 ActiveX 控件)隐式链接到，
		//  而不是由 MFC 应用程序链接到，则需要
		//  将此行从 DllMain 中移除并将其放置在一个
		//  从此扩展 DLL 导出的单独的函数中。使用此扩展 DLL 的
		//  规则 DLL 然后应显式
		//  调用该函数以初始化此扩展 DLL。否则，
		//  CDynLinkLibrary 对象不会附加到
		//  规则 DLL 的资源链，并将导致严重的
		//  问题。

		new CDynLinkLibrary(MyMouseHookDLL);
		glhInstance=hInstance; //插入保存DLL
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MyMouseHook.DLL 正在终止!\n");

		// 在调用析构函数之前终止该库
		AfxTermExtensionModule(MyMouseHookDLL);
	}

	setlocale( LC_ALL, old_locale);
	free(old_locale); 
	return 1;   // 确定
}


//钩子函数的实现： 
//LRESULT WINAPI MouseProc(int nCode,WPARAM wparam,LPARAM lparam)
//{
//	LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *)lparam;
//	if (nCode>=0)
//	{
//		if (WM_LBUTTONDOWN==wparam)
//		{
//			
//			//鼠标钩子,lParam是MOUSEHOOKSTRUCT结构指针
//			PMOUSEHOOKSTRUCT lpMsg = (PMOUSEHOOKSTRUCT)lparam;
//			lpMsg->hwnd = NULL;
//			lpMsg->dwExtraInfo = 0L;
//			lpMsg->pt = CPoint(0,0);
//			lpMsg->wHitTestCode = 0L;
//		} 
//
//		/*============================================================================
//		如下代码是得到父窗口标题文本的做法
//		HWND glhTargetWnd=pMouseHook->hwnd;     //取目标窗口句柄
//		HWND ParentWnd=glhTargetWnd;
//		while (ParentWnd !=NULL)
//		{
//			glhTargetWnd=ParentWnd;
//			ParentWnd=GetParent(glhTargetWnd);   //取应用程序主窗口句柄
//		}
//		===========================================================================*/
//		//HWND glhTargetWnd=XYZWindowFromPoint(NULL,pMouseHook->pt);    //用上面的一段注释掉的代码替换此行是得到父窗口标题文本的做法
//		//if(glhTargetWnd!=glhPrevTarWnd)
//		//{
//		//	char szCaption[256];
//		//	GetWindowText(glhTargetWnd,szCaption,100);
//		//	//取目标窗口标题
//		//	if(IsWindow(glhDisplayWnd))
//		//		SendMessage(glhDisplayWnd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)szCaption);
//		//	glhPrevTarWnd=glhTargetWnd;
//		//	//保存目标窗口
//		//}
//	}
//	return CallNextHookEx(glhHook,nCode,wparam,lparam);
//	//继续传递消息
//}

LRESULT CALLBACK MouseProc(
	int nCode,      // hook code
	WPARAM wParam,  // message identifier
	LPARAM lParam   // mouse coordinates
	) //鼠标钩子过程
{
	LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *)lParam;
		if (nCode>=0)
		{
			if (WM_LBUTTONDOWN==wParam)
			{
				
				//鼠标钩子,lParam是MOUSEHOOKSTRUCT结构指针
				PMOUSEHOOKSTRUCT lpMsg = (PMOUSEHOOKSTRUCT)lParam;
				CPoint point = lpMsg->pt;
				
				RECT rect;
				::GetWindowRect(g_hwnd, &rect);	//得到整个窗口在屏幕上的矩形框位置

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
	)//键盘钩子过程
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


// CMouseHook 成员函数

//安装钩子并设定接收显示窗口句柄
BOOL CMouseHook::StartHook(HWND hWnd)
{
	BOOL bResult=FALSE;
	g_hwnd=hWnd;

	g_mouseHook=::SetWindowsHookEx(WH_MOUSE,MouseProc,glhInstance/*::GetModuleHandle(_T("MyMouseHook.dll"))*/,0); 
	//g_keyboardHook=::SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,::GetModuleHandle(_T("MyMouseHook.dll")),0);
	/*=================================================================================
    HHOOK SetWindowsHookEx( int idHook,HOOKPROC lpfn, INSTANCE hMod,DWORD dwThreadId )
　　参数idHook表示钩子类型，它是和钩子函数类型一一对应的。
    比如，WH_KEYBOARD表示安装的是键盘钩子，WH_MOUSE表示是鼠标钩子等等。 

　　Lpfn是钩子函数的地址。 

　　HMod是钩子函数所在的实例的句柄。对于线程钩子，该参数为NULL；
    对于系统钩子，该参数为钩子函数所在的DLL句柄。 

　　dwThreadId 指定钩子所监视的线程的线程号。对于全局钩子，该参数为NULL。 

　　SetWindowsHookEx返回所安装的钩子句柄。
    值得注意的是线程钩子和系统钩子的钩子函数的位置有很大的差别。
	线程钩子一般在当前线程或者当前线程派生的线程内，
	而系统钩子必须放在独立的动态链接库中，实现起来要麻烦一些。 
	==================================================================================*/
	if(g_mouseHook!=NULL)
		bResult=TRUE;
	//glhDisplayWnd=hWnd;
	//设置显示目标窗口标题编辑框的句柄
	return bResult; 
}

//卸载钩子
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
