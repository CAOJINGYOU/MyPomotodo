
// MyPomotodo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyPomotodoApp: 
// �йش����ʵ�֣������ MyPomotodo.cpp
//

class CMyPomotodoApp : public CWinApp
{
public:
	CMyPomotodoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyPomotodoApp theApp;