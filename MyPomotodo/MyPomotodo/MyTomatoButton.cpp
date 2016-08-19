// MyTomatoButton.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyTomatoButton.h"


// CMyTomatoButton

IMPLEMENT_DYNAMIC(CMyTomatoButton, CButton)

	CMyTomatoButton::CMyTomatoButton()
	: m_strContent(_T(""))
	, m_strBeigTime(_T(""))
	, m_strEndTime(_T(""))
	, m_nType(0)
{

}
CMyTomatoButton::CMyTomatoButton(CString strBeigTime,CString strEndTime,CString strContent,int nType)
	: m_strContent(strContent)
	, m_strBeigTime(strBeigTime)
	, m_strEndTime(strEndTime)
	, m_nType(nType)
{
	m_Font.CreateFont(
		20, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		FW_NORMAL, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		ANSI_CHARSET, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision
		CLIP_DEFAULT_PRECIS, // nClipPrecision
		DEFAULT_QUALITY, // nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("宋体") // nPitchAndFamily Arial
		);
	int nHeight = 0;
	switch(m_nType)
	{
	case BUTTON:
		nHeight = 18;
		break;
	case DAY:
		nHeight = 22;
		break;
	case YEAR:
		nHeight = 26;
		break;
	default:
		nHeight = 18;
	}
	m_Font1.CreateFont(
		nHeight, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		FW_NORMAL, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		ANSI_CHARSET, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision
		CLIP_DEFAULT_PRECIS, // nClipPrecision
		DEFAULT_QUALITY, // nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("宋体") // nPitchAndFamily Arial
		);
}

CMyTomatoButton::~CMyTomatoButton()
{
}


BEGIN_MESSAGE_MAP(CMyTomatoButton, CButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMyTomatoButton 消息处理程序




void CMyTomatoButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	CDC ButtonDC;
	CRect rcAll,rcT,rcB;

	ButtonDC.Attach(lpDrawItemStruct->hDC); //得到用于绘制按钮的DC    
	rcAll = lpDrawItemStruct->rcItem; //获取按钮所占的矩形大小 

	rcB = rcAll;

	rcB.left+=40;
	rcB.right-=40;
	rcT = rcB;

	rcT.bottom-=25;
	rcB.top+=25;
	rcB.left+=20;

	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	//绘制按钮文字

	CFont* oldFont = NULL;
	
	oldFont = pDC->SelectObject(&m_Font1);
	
	pDC->SetBkMode( TRANSPARENT );

	if (m_nType==BUTTON)
	{
		pDC->SetTextColor(RGB(153, 153, 153));
		pDC->DrawText( m_strBeigTime, &rcT, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		pDC->DrawText( m_strEndTime, &rcT, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

		pDC->SelectObject ( oldFont);
		oldFont = pDC->SelectObject(&m_Font);
		pDC->SetTextColor(RGB(0, 0, 0));

		pDC->DrawText( m_strContent, &rcB, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	}

	if (m_nType==DAY)
	{
		pDC->SetTextColor(RGB(62,149,96));
		pDC->DrawText( m_strContent, &rcAll, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	if (m_nType==YEAR)
	{
		pDC->SetTextColor(RGB(226,66,66));
		pDC->DrawText( m_strContent, &rcAll, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	
	pDC->SelectObject ( oldFont); 
}


void CMyTomatoButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}
