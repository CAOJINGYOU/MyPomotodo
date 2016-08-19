#pragma once

// CMouseHook 命令目标

class AFX_EXT_CLASS CMouseHook : public CObject	//AFX_EXT_CLASS宏声明类为导出类
{
public:
	CMouseHook();
	virtual ~CMouseHook();

public:
	BOOL StartHook(HWND hWnd); //安装钩子函数

	BOOL StopHook();//卸载钩子函数
};


