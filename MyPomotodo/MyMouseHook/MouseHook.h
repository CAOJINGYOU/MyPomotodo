#pragma once

// CMouseHook ����Ŀ��

class AFX_EXT_CLASS CMouseHook : public CObject	//AFX_EXT_CLASS��������Ϊ������
{
public:
	CMouseHook();
	virtual ~CMouseHook();

public:
	BOOL StartHook(HWND hWnd); //��װ���Ӻ���

	BOOL StopHook();//ж�ع��Ӻ���
};


