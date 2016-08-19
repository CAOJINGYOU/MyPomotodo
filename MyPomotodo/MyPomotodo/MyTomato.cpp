// MyTomato.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyTomato.h"
#include "afxdialogex.h"
#include "CharTool.h"

#define	 WM_INITTOMATO (WM_USER + 3)

#define BUTTONEVEN 200000

extern CMyDatabase g_MyDatabase;
// CMyTomato 对话框

IMPLEMENT_DYNAMIC(CMyTomato, CDialogEx)

CMyTomato::CMyTomato(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyTomato::IDD, pParent)
{

}

CMyTomato::~CMyTomato()
{
}

void CMyTomato::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyTomato, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CMyTomato 消息处理程序


HBRUSH CMyTomato::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return CreateSolidBrush(RGB(250, 250, 250));
}


void CMyTomato::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()  
}


BOOL CMyTomato::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CMyTomato::GetScrollPos(int nBar, UINT nSBCode)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
	GetScrollInfo(nBar, &si);

	const int minPos = si.nMin;
	const int maxPos = si.nMax - (si.nPage - 1);

	int result = -1;

	    /* SB_BOTTOM 滑到底部

    SB_ENDSCROLL 滑动结束.

    SB_LINEDOWN 向下滑动一行.

    SB_LINEUP 向上滑动一行.

    SB_PAGEDOWN 向下滑动一页.

    SB_PAGEUP 向上滑动一页.

    SB_THUMBPOSITION 滑动到了现在所在的位置，位置在nPos参数中提供

    SB_THUMBTRACK 滑块正在被拖动，滑块现在所处的位置由nPos参数提供

    SB_TOP 滑块滑动到顶部了 */

	switch(nSBCode)
	{
	case SB_LINEUP /*SB_LINELEFT*/:
		result = max(si.nPos - 1, minPos);
		break;
	case SB_LINEDOWN /*SB_LINERIGHT*/:
		result = min(si.nPos + 1, maxPos);
		break;
	case SB_PAGEUP /*SB_PAGELEFT*/:
		result = max(si.nPos - (int)si.nPage, minPos);
		break;
	case SB_PAGEDOWN /*SB_PAGERIGHT*/:
		result = min(si.nPos + (int)si.nPage, maxPos);
		break;
	case SB_THUMBPOSITION:
		// do nothing
		break;
	case SB_THUMBTRACK:
		result = si.nTrackPos;
		break;
	case SB_TOP /*SB_LEFT*/:
		result = minPos;
		break;
	case SB_BOTTOM /*SB_RIGHT*/:
		result = maxPos;
		break;
	case SB_ENDSCROLL:
		// do nothing
		break;
	}

	return result;
}

void CMyTomato::VScrool(int nBar, UINT nSBCode)
{
	const int scrollPos = GetScrollPos(nBar, nSBCode);

	if(scrollPos == -1)
		return;

	SetScrollPos(nBar, scrollPos, TRUE);
	ScrollClient(nBar, scrollPos);
}

//void CMyTomato::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	VScrool(SB_VERT, nSBCode);
//	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
//}


void CMyTomato::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	VScrool(SB_VERT, nSBCode);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyTomato::ScrollClient(int nBar, int nPos)
{
	static int s_prevx = 1;
	static int s_prevy = 1;

	int cx = 0;
	int cy = 0;

	int &delta = cy;
	int &prev = s_prevy;

	delta = prev - nPos;
	prev = nPos;

	if(cx || cy)
	{
		ScrollWindow(cx, cy, NULL, NULL);
	}
}

int CMyTomato::updateList(void)
{
	for (int i = 0;i<m_arrTomatoList.GetSize();i++)
	{
		CMyTomatoButton* myButtonTest = (CMyTomatoButton*)m_arrTomatoList.GetAt(i);
		if (myButtonTest!=NULL)
		{
			delete myButtonTest;
			myButtonTest = NULL;
		}
	}

	init();

	return 0;
}


void CMyTomato::init(void)
{
	CRect rect,rcS;

	GetClientRect(&rect);
	rect.top+=6;
	rcS = rect;

	for (int i = 0;i<m_arrTomatoList.GetSize();i++)
	{
		CMyTomatoButton* myButtonTest = (CMyTomatoButton*)m_arrTomatoList.GetAt(i);
		if (myButtonTest!=NULL)
		{
			delete myButtonTest;
			myButtonTest = NULL;
		}
	}

	m_arrTomatoList.RemoveAll();

	g_MyDatabase.SelectTableTomato();

	int i=0;

	std::vector<TOMATOINFO>::iterator iter;
	CTime tmepTime;
	int nYear = 0, nMonth = 0 , nDay = 0;
	CString strTemp = _T("");
	for(iter=g_MyDatabase.m_vTomatoInfo.begin();iter!=g_MyDatabase.m_vTomatoInfo.end();iter++)
	{
		tmepTime = StringToTime(iter->strEndTime);

		if (nYear!=0&&nMonth!=0&&nDay!=0)
		{
			strTemp = _T("");
			if (nYear != tmepTime.GetYear())
			{
				strTemp.Format(_T("%d年"),tmepTime.GetYear());
				CMyTomatoButton* myButton = new CMyTomatoButton(iter->strBeigTime,iter->strEndTime,strTemp,YEAR);

				myButton->Create(_T("Tomato"),WS_VISIBLE | WS_CHILD|BS_OWNERDRAW /*|WS_DISABLED*/,CRect(rect.left,rect.top+50*i,rect.right,rect.top+50*(i+1)),this,BUTTONEVEN+i);

				m_arrTomatoList.Add(myButton);

				if (rcS.bottom<rect.top+50*(i+1))
				{
					rcS.bottom = rect.top+50*(i+1);
				}

				i++;
			}
			if (nMonth != tmepTime.GetMonth()||nDay != tmepTime.GetDay())
			{
				strTemp.Format(_T("%2d月%2d日 星期"),tmepTime.GetMonth(),tmepTime.GetDay());

				switch (tmepTime.GetDayOfWeek())
				{
				case 1:
					strTemp+=_T("天");
					break;
				case 2:
					strTemp+=_T("一");
					break;
				case 3:
					strTemp+=_T("二");
					break;
				case 4:
					strTemp+=_T("三");
					break;
				case 5:
					strTemp+=_T("四");
					break;
				case 6:
					strTemp+=_T("五");
					break;
				case 7:
					strTemp+=_T("六");
					break;
				}

				CMyTomatoButton* myButton = new CMyTomatoButton(iter->strBeigTime,iter->strEndTime,strTemp,DAY);

				myButton->Create(_T("Tomato"),WS_VISIBLE | WS_CHILD|BS_OWNERDRAW /*|WS_DISABLED*/,CRect(rect.left,rect.top+50*i,rect.right,rect.top+50*(i+1)),this,BUTTONEVEN+i);

				m_arrTomatoList.Add(myButton);

				if (rcS.bottom<rect.top+50*(i+1))
				{
					rcS.bottom = rect.top+50*(i+1);
				}

				i++;
			}
		}
		nYear = tmepTime.GetYear();
		nMonth = tmepTime.GetMonth();
		nDay = tmepTime.GetDay();

		CMyTomatoButton* myButton = new CMyTomatoButton(iter->strBeigTime,iter->strEndTime,iter->strTomatoName,BUTTON);

		myButton->Create(_T("Tomato"),WS_VISIBLE | WS_CHILD|BS_OWNERDRAW /*|WS_DISABLED*/,CRect(rect.left,rect.top+50*i,rect.right,rect.top+50*(i+1)),this,BUTTONEVEN+i);

		m_arrTomatoList.Add(myButton);

		if (rcS.bottom<rect.top+50*(i+1))
		{
			rcS.bottom = rect.top+50*(i+1);
		}

		i++;
	}

	//MoveWindow(rect);

	m_page = 1;
	const SIZE sz = { rcS.right - rcS.left, rcS.bottom - rcS.top };    

	SCROLLINFO si;    
	si.cbSize = sizeof(SCROLLINFO);    
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;    
	si.nPos = si.nMin = 1;    

	si.nMax = sz.cy*m_page;    
	si.nPage = rect.bottom - rect.top;    
	SetScrollInfo(SB_VERT, &si, FALSE); 

	if (rect.bottom==rcS.bottom)
	{
		ModifyStyle(WS_VSCROLL,0);
	}

	InvalidateRect(rect,TRUE);
	UpdateWindow();
	Invalidate();
}


BOOL CMyTomato::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	BOOL bOk=CDialogEx::DestroyWindow();

	for (int i = 0;i<m_arrTomatoList.GetSize();i++)
	{
		CMyTomatoButton* myButtonTest = (CMyTomatoButton*)m_arrTomatoList.GetAt(i);
		if (myButtonTest!=NULL)
		{
			delete myButtonTest;
			myButtonTest = NULL;
		}
	}

	m_arrTomatoList.RemoveAll();

	return bOk;
}


void CMyTomato::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nID==WM_INITTOMATO&&this->IsWindowVisible())
	{
		init();
	}  
	CDialogEx::OnSysCommand(nID, lParam);
}


CTime CMyTomato::StringToTime(CString strTime)
{
	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
	sscanf(CharTool::WideCharToMultiByteCString(strTime),    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   

	return CTime(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
}
