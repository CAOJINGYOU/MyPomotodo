
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

/*
 *	枚举
 */

/*
 *	对话框数量
 */
enum
{
	DIALOG_POTATO_INDEX,
	DIALOG_TOMATO_INDEX,
	DIALOG_COUNT
};

/*
 *	Button框数量
 */
enum
{
	BUTTON_POTATO_INDEX,
	BUTTON_TOMATO_INDEX,
	BUTTON_WEBSITE_INDEX,
	BUTTON_TOP_INDEX,
	BUTTON_OTHER_INDEX,
	BUTTON_SET_INDEX,
	BUTTON_CONTINUITY_INDEX,
	BUTTON_TIME_INDEX,
	BUTTON_START_INDEX,
	BUTTON_COUNT
};

/*
 *	Button框数量
 */
enum
{
	IID_BUTTON_POTATO = 81000,
	IID_BUTTON_TOMATO_INDEX,
	IID_BUTTON_WEBSITE_INDEX,
	IID_BUTTON_TOP_INDEX,
	IID_BUTTON_OTHER_INDEX,
	IID_BUTTON_SET_INDEX,
	IID_BUTTON_CONTINUITY_INDEX,
	IID_BUTTON_TIME_INDEX,
	IID_BUTTON_START_INDEX
};

/*
 *	结构体struct
 */

typedef struct tagSysConfigInfo
{
	tagSysConfigInfo()
		: lTomatoTime(25)
		, lRestTime(5)
		, lLongRestTime(15)
		, uLongRestInterval(4)
		, strWorkSound(_T(""))
		, strThatSound(_T(""))
		, bDisplaySystemNotifications(TRUE)
		, bPlayTick(FALSE)
		, bPlayPromptSound(TRUE)
		, bRunningWithSystem(FALSE)
		, bFromSystemTray(FALSE)
		, bAutoAdjustSize(FALSE)
		, uState(0)
		, strWorkTime(_T(""))
		, strWorkRestTime(_T(""))
	{
	};

	//番茄相关
	LONGLONG		lTomatoTime;			//番茄时长
	LONGLONG		lRestTime;				//休息时长
	LONGLONG		lLongRestTime;			//长休息时长
	UINT			uLongRestInterval;		//长休息间隔
	CString			strWorkSound;			//工作音效
	CString			strThatSound;			//提示音效

	//常用
	BOOL bDisplaySystemNotifications;		//显示系统通知
	BOOL bPlayTick;							//播放滴答声
	BOOL bPlayPromptSound;					//播放提示音效
	BOOL bRunningWithSystem;				//系统启动时运行番茄土豆
	BOOL bFromSystemTray;					//脱离系统托盘
	BOOL bAutoAdjustSize;					//自动调整窗口尺寸

	//其他
	UINT uState;								//工作还是休息状态，0为停止，1为工作，2为休息
	CString			strWorkTime;				//上次工作时间
	CString			strWorkRestTime;			//上次工作或休息开始时间

} INISYSCONFIGINFO, *PINISYSCONFIGINFO;




#pragma comment(lib,"MyMouseHook.lib")   //隐式链接DLL


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


