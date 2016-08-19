// MySettingTomatoRelated.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MySettingTomatoRelated.h"
#include "afxdialogex.h"


// MySettingTomatoRelated �Ի���

IMPLEMENT_DYNAMIC(MySettingTomatoRelated, CDialogEx)

MySettingTomatoRelated::MySettingTomatoRelated(CWnd* pParent /*=NULL*/)
	: CDialogEx(MySettingTomatoRelated::IDD, pParent)
	, m_editLTomato(0)
	, m_editRestTime(0)
	, m_editLongRestTime(0)
	, m_editULongRestInterval(0)
{

}

MySettingTomatoRelated::~MySettingTomatoRelated()
{
}

void MySettingTomatoRelated::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LTOMATOTIME, m_editLTomato);
	DDV_MinMaxInt(pDX, m_editLTomato, 1, 2500);
	DDX_Control(pDX, IDC_SPIN_LTOMATOTIME, m_spinLTomato);
	DDX_Text(pDX, IDC_EDIT_RESTTIME, m_editRestTime);
	DDV_MinMaxInt(pDX, m_editRestTime, 1, 500);
	DDX_Control(pDX, IDC_SPIN_RESTTIME, m_spinRestTime);
	DDX_Text(pDX, IDC_EDIT_ILONGRESTTIME, m_editLongRestTime);
	DDV_MinMaxInt(pDX, m_editLongRestTime, 1, 1500);
	DDX_Control(pDX, IDC_SPIN_ILONGRESTTIME, m_spinLongRestTime);
	DDX_Text(pDX, IDC_EDIT_ULONGRESTINTERVAL, m_editULongRestInterval);
	DDV_MinMaxUInt(pDX, m_editULongRestInterval, 1, 400);
	DDX_Control(pDX, IDC_SPIN_ULONGRESTINTERVAL, m_spinULongRestInterval);
}


BEGIN_MESSAGE_MAP(MySettingTomatoRelated, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_LTOMATOTIME, &MySettingTomatoRelated::OnEnChangeEditLtomatotime)
END_MESSAGE_MAP()


// MySettingTomatoRelated ��Ϣ�������


BOOL MySettingTomatoRelated::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_editLTomato = g_SysConfigInfo->lTomatoTime;
	m_editRestTime = g_SysConfigInfo->lRestTime;
	m_editLongRestTime = g_SysConfigInfo->lLongRestTime;
	m_editULongRestInterval = g_SysConfigInfo->uLongRestInterval;


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_spinLTomato.SetRange(1, 2500);
	m_spinLTomato.SetPos(m_editLTomato);
	m_spinLTomato.SetBase(1);

	m_spinRestTime.SetRange(1, 500);
	m_spinRestTime.SetPos(m_editRestTime);
	m_spinRestTime.SetBase(1);

	m_spinLongRestTime.SetRange(1, 1500);
	m_spinLongRestTime.SetPos(m_editLongRestTime);
	m_spinLongRestTime.SetBase(1);

	m_spinULongRestInterval.SetRange(1, 400);
	m_spinULongRestInterval.SetPos(m_editULongRestInterval);
	m_spinULongRestInterval.SetBase(1);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void MySettingTomatoRelated::OnEnChangeEditLtomatotime()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
