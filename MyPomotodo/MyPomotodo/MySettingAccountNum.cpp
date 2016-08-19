// MySettingAccountNum.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MySettingAccountNum.h"
#include "afxdialogex.h"


// MySettingAccountNum 对话框

IMPLEMENT_DYNAMIC(MySettingAccountNum, CDialogEx)

MySettingAccountNum::MySettingAccountNum(CWnd* pParent /*=NULL*/)
	: CDialogEx(MySettingAccountNum::IDD, pParent)
{

}

MySettingAccountNum::~MySettingAccountNum()
{
}

void MySettingAccountNum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MySettingAccountNum, CDialogEx)
END_MESSAGE_MAP()


// MySettingAccountNum 消息处理程序
