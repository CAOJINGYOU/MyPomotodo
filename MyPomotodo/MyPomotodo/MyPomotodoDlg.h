
// MyPomotodoDlg.h : 头文件
//

#pragma once

#include "MyButton.h"
#include "MyPotato.h"
#include "mytime.h"
#include "..\MyMouseHook\MouseHook.h"
#include "MyDatabase.h"
#include "MyTomato.h"
#include "afxwin.h"

#include "LibMP3DLL.h"


#define  WM_SHOWTASK (WM_USER + 1)
#define  WM_TOTASK (WM_USER + 2)
#define	 WM_INITTOMATO (WM_USER + 3)


static INISYSCONFIGINFO *g_SysConfigInfo;


// CMyPomotodoDlg 对话框
class CMyPomotodoDlg : public CDialogEx
{
// 构造
public:
	CMyPomotodoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPOMOTODO_DIALOG };
#endif

	typedef struct tagInitDlgInfo
	{
		tagInitDlgInfo()
			:uDialogTemplate(0)
		{
		};
		
		UINT		uDialogTemplate;
	}INITDLGINFO, *PINITDLGINFO;

	typedef struct tagInitButtonInfo
	{
		tagInitButtonInfo()
			:uButtonTemplate(0)
		{
		};

		UINT		uButtonTemplate;
	}INITBUTTONINFO, *PINITBUTTONINFO;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CLibMP3DLL m_playerDll;
	bool playing;
	bool pause;
	static bool FileExists(const TCHAR *fileName);
	int GetVolume();
	BOOL m_bTick;

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CDialog** m_pDlg;
	afx_msg void OnDestroy();
	// 创建子窗口
	void CreateChildDialog(CDialog *pDialogEx, UINT uIDTemplate, CWnd *pStatic, CWnd *pParent, int iCmdShow);
	// 对话框初始信息
	PINITDLGINFO m_pInitDlgInfo;
	//	Button初始化信息
	PINITBUTTONINFO m_pInitButtonInfo;
	//CMyButton* m_btnPotatoButton;
	virtual BOOL DestroyWindow();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//CMyButton* m_btnTomatoButton;
	CMyButton** m_btnButton;
	void SetButtonShow(int nIndex);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int Start(void);
	CMyTime m_myTime;
	CString GetStrTimeSpan(bool &bEnd, double &dRatio);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	void ToTray(void);
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMyAbout();
	afx_msg void OnMySetting();
	afx_msg void OnMyHelp();
	//删除托盘中图标
	void DeleteTray();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CMouseHook m_MyMouseHook;

	
	BOOL m_bInitState;
	CEdit m_EditAddTomato;
	// 时钟第一次运行
	BOOL m_bTimeStartFirst;
	void initHear(void);
	void ToRest(void);
	void ToInitialState(void);
	void ToFill(void);
private:
	void PlayMp3(void);
public:
	void StopMp3(void);
	void PauseMp3(void);
protected:
	afx_msg void OnPaymetalbell();
};
