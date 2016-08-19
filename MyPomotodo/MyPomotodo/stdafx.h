
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

/*
 *	ö��
 */

/*
 *	�Ի�������
 */
enum
{
	DIALOG_POTATO_INDEX,
	DIALOG_TOMATO_INDEX,
	DIALOG_COUNT
};

/*
 *	Button������
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
 *	Button������
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
 *	�ṹ��struct
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

	//�������
	LONGLONG		lTomatoTime;			//����ʱ��
	LONGLONG		lRestTime;				//��Ϣʱ��
	LONGLONG		lLongRestTime;			//����Ϣʱ��
	UINT			uLongRestInterval;		//����Ϣ���
	CString			strWorkSound;			//������Ч
	CString			strThatSound;			//��ʾ��Ч

	//����
	BOOL bDisplaySystemNotifications;		//��ʾϵͳ֪ͨ
	BOOL bPlayTick;							//���ŵδ���
	BOOL bPlayPromptSound;					//������ʾ��Ч
	BOOL bRunningWithSystem;				//ϵͳ����ʱ���з�������
	BOOL bFromSystemTray;					//����ϵͳ����
	BOOL bAutoAdjustSize;					//�Զ��������ڳߴ�

	//����
	UINT uState;								//����������Ϣ״̬��0Ϊֹͣ��1Ϊ������2Ϊ��Ϣ
	CString			strWorkTime;				//�ϴι���ʱ��
	CString			strWorkRestTime;			//�ϴι�������Ϣ��ʼʱ��

} INISYSCONFIGINFO, *PINISYSCONFIGINFO;




#pragma comment(lib,"MyMouseHook.lib")   //��ʽ����DLL


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


