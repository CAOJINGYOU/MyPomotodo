// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyPotatoListButton.h"

#define WM_DELETEPOTATO (WM_USER + 3)
#define WM_POTATOTOTOMATO (WM_USER + 8)


// CMyPotatoListButton

IMPLEMENT_DYNAMIC(CMyPotatoListButton, CButton)

	CMyPotatoListButton::CMyPotatoListButton(int nId, CString strBtnDown, CString strBtnOver, CString strBtnNormal, 
		CString strBtnSelectedNormal, CString strBtnPinOver, CString strBtnPinSelectedOver, 
		CString strBtnPinDown, CString strBtnDisabled, CString strBtnFocus, 
		CString strBtnName)
	: m_strButtonName(_T(""))
	, m_nID(0)
{
	init();

	m_nID = nId;

	if (strBtnNormal.GetLength() > 0)
	{
		if (!m_pImgNormal)
			m_pImgNormal = new CxImage(strBtnNormal.GetBuffer(),GetImageType(strBtnNormal));
	}

	if (strBtnFocus.GetLength() > 0)
	{
		if (!m_pImgFocus)
			m_pImgFocus = new CxImage(strBtnFocus.GetBuffer(),GetImageType(strBtnFocus));
	}

	if (strBtnDown.GetLength() > 0)
	{
		if (!m_pImgDown)
			m_pImgDown = new CxImage(strBtnDown.GetBuffer(),GetImageType(strBtnDown));
	}

	if (strBtnDisabled.GetLength() > 0)
	{
		if (!m_pImgDisable)
			m_pImgDisable = new CxImage(strBtnDisabled.GetBuffer(),GetImageType(strBtnDisabled));
	}

	if (strBtnOver.GetLength() > 0)
	{
		if (!m_pImgOver)
			m_pImgOver = new CxImage(strBtnOver.GetBuffer(),GetImageType(strBtnOver));
	}

	if (strBtnPinOver.GetLength() > 0)
	{
		if (!m_pImgPinOver)
			m_pImgPinOver = new CxImage(strBtnPinOver.GetBuffer(),GetImageType(strBtnPinOver));
	}

	if (strBtnPinDown.GetLength() > 0)
	{
		if (!m_pImgPinDown)
			m_pImgPinDown = new CxImage(strBtnPinDown.GetBuffer(),GetImageType(strBtnPinDown));
	}

	if (strBtnSelectedNormal.GetLength() > 0)
	{
		if (!m_pImgSelectedNormal)
			m_pImgSelectedNormal = new CxImage(strBtnSelectedNormal.GetBuffer(),GetImageType(strBtnSelectedNormal));
	}

	if (strBtnPinSelectedOver.GetLength() > 0)
	{
		if (!m_pImgPinSelectedOver)
			m_pImgPinSelectedOver = new CxImage(strBtnPinSelectedOver.GetBuffer(),GetImageType(strBtnPinSelectedOver));
	}

	m_strButtonName = strBtnName;
}

CMyPotatoListButton::~CMyPotatoListButton()
{
	if (m_pImgNormal)
	{
		m_pImgNormal->Destroy();
		delete m_pImgNormal;
		m_pImgNormal = NULL;
	}
	if (m_pImgOver)
	{
		m_pImgOver->Destroy();
		delete m_pImgOver;
		m_pImgOver = NULL;
	}
	if (m_pImgDown)
	{
		m_pImgDown->Destroy();
		delete m_pImgDown;
		m_pImgDown = NULL;
	}
	if (m_pImgFocus)
	{
		m_pImgFocus->Destroy();
		delete m_pImgFocus;
		m_pImgFocus = NULL;
	}
	if (m_pImgDisable)
	{
		m_pImgDisable->Destroy();
		delete m_pImgDisable;
		m_pImgDisable = NULL;
	}
	if (m_pImgPinOver)
	{
		m_pImgPinOver->Destroy();
		delete m_pImgPinOver;
		m_pImgPinOver = NULL;
	}
	if (m_pImgPinDown)
	{
		m_pImgPinDown->Destroy();
		delete m_pImgPinDown;
		m_pImgPinDown = NULL;
	}
	if (m_pImgSelectedNormal)
	{
		m_pImgSelectedNormal->Destroy();
		delete m_pImgSelectedNormal;
		m_pImgSelectedNormal = NULL;
	}
	if (m_pImgPinSelectedOver)
	{
		m_pImgPinSelectedOver->Destroy();
		delete m_pImgPinSelectedOver;
		m_pImgPinSelectedOver = NULL;
	}
}


BEGIN_MESSAGE_MAP(CMyPotatoListButton, CButton)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, &CMyPotatoListButton::OnBnDoubleclicked)
	ON_CONTROL_REFLECT(BN_KILLFOCUS, &CMyPotatoListButton::OnBnKillfocus)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CMyPotatoListButton 消息处理程序




void CMyPotatoListButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项

	CDC ButtonDC;
	CRect rcAll,rc,rcRight,rcCenter;

	ButtonDC.Attach(lpDrawItemStruct->hDC); //得到用于绘制按钮的DC    
	rcAll = lpDrawItemStruct->rcItem; //获取按钮所占的矩形大小 
	rc = rcAll;
	rcRight = rcAll;
	rc.right = rc.left+40;
	rcRight.left = rcRight.right-40;
	rcCenter = rcAll;
	rcCenter.left+=40;
	rcCenter.right-=40;

	

	UINT state = lpDrawItemStruct->itemState; //获取按钮目前所处的状态，根据不同的状态绘制不同的按钮    

	if (state&ODS_DISABLED && m_pImgDisable)
	{
		m_pImgDisable->Draw(ButtonDC.GetSafeHdc(), rc);
	}
	else
	{
		if (m_bLBtnDown && m_pImgDown)
		{
			//m_pImgDown->Draw(ButtonDC.GetSafeHdc(), rc);

			if (m_bSelected)
			{
				ButtonDC.FillRect(rcAll, &m_BrushSelectedOver);
				m_pImgSelectedNormal->Draw(ButtonDC.GetSafeHdc(), rc);

				m_pImgPinSelectedOver->Draw(ButtonDC.GetSafeHdc(), rcRight);
			} 
			else
			{
				ButtonDC.FillRect(rcAll, &m_BrushOver);


				m_pImgOver->Draw(ButtonDC.GetSafeHdc(), rc);
				m_pImgPinOver->Draw(ButtonDC.GetSafeHdc(), rcRight);
			}
		}
		else if (m_bMouseOver && m_pImgOver)
		{
			/*CBrush brush;
			brush.CreateSolidBrush(::GetSysColor(RGB(250,250,250)));
			::FillRect(lpDrawItemStruct->hDC,&rcAll,(HBRUSH)brush.m_hObject);  
			::SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);*/
			
			if (m_bSelected)
			{
				ButtonDC.FillRect(rcAll, &m_BrushSelectedOver);
				m_pImgSelectedNormal->Draw(ButtonDC.GetSafeHdc(), rc);

				m_pImgPinSelectedOver->Draw(ButtonDC.GetSafeHdc(), rcRight);
			} 
			else
			{
				ButtonDC.FillRect(rcAll, &m_BrushOver);


				m_pImgOver->Draw(ButtonDC.GetSafeHdc(), rc);
				m_pImgPinOver->Draw(ButtonDC.GetSafeHdc(), rcRight);
			}
			
		}
		else if (state&ODS_FOCUS && m_pImgFocus)
		{
			//m_pImgFocus->Draw(ButtonDC.GetSafeHdc(), rc);
			if (m_bSelected)
			{
				ButtonDC.FillRect(rcAll, &m_BrushSelectedOver);
				m_pImgSelectedNormal->Draw(ButtonDC.GetSafeHdc(), rc);

				if (m_bTracking)
				{
					m_pImgPinSelectedOver->Draw(ButtonDC.GetSafeHdc(), rcRight);
				}
				
			} 
			else
			{
				ButtonDC.FillRect(rcAll, &m_BrushOver);


				m_pImgOver->Draw(ButtonDC.GetSafeHdc(), rc);

				if (m_bTracking)
				{
					m_pImgPinOver->Draw(ButtonDC.GetSafeHdc(), rcRight);
				}
				
			}
		}
		else if (m_pImgNormal)
		{
			if (m_bSelected)
			{
				ButtonDC.FillRect(rcAll, &m_BrushSelectedOver);
				m_pImgSelectedNormal->Draw(ButtonDC.GetSafeHdc(), rc);
			} 
			else
			{
				ButtonDC.FillRect(rcAll, &m_BrushgNormal);
				m_pImgNormal->Draw(ButtonDC.GetSafeHdc(), rc);
			}
		}
	}

	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	//绘制按钮文字

	CFont* oldFont = NULL;
	if (m_bSelected)
	{
		oldFont = pDC->SelectObject(&m_StrikeFont);
	} 
	else
	{
		oldFont = pDC->SelectObject(&m_Font);
	}
	pDC->SetTextColor(RGB(34, 34, 34));
	pDC->SetBkMode( TRANSPARENT );

	pDC->DrawText( m_strButtonName, &rcCenter, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	

	pDC->SelectObject ( oldFont); 
	
	/*pDC->DrawText( m_strButtonName, &rcCenter, DT_SINGLELINE | DT_CENTER
	| DT_VCENTER | DT_END_ELLIPSIS);*/
	//::SetTextColor (lpDrawItemStruct->hDC,RGB (0, 155, 255));
	//::SetBkMode (lpDrawItemStruct->hDC,TRANSPARENT);
	//::DrawText(lpDrawItemStruct->hDC,m_strButtonName, m_strButtonName.GetLength(), rcCenter, DT_SINGLELINE | DT_LEFT | DT_VCENTER); //显示文本
}


void CMyPotatoListButton::OnDestroy()
{
	CButton::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	if (m_pImgNormal)
	{
		m_pImgNormal->Destroy();
		delete m_pImgNormal;
		m_pImgNormal = NULL;
	}
	if (m_pImgOver)
	{
		m_pImgOver->Destroy();
		delete m_pImgOver;
		m_pImgOver = NULL;
	}
	if (m_pImgDown)
	{
		m_pImgDown->Destroy();
		delete m_pImgDown;
		m_pImgDown = NULL;
	}
	if (m_pImgFocus)
	{
		m_pImgFocus->Destroy();
		delete m_pImgFocus;
		m_pImgFocus = NULL;
	}
	if (m_pImgDisable)
	{
		m_pImgDisable->Destroy();
		delete m_pImgDisable;
		m_pImgDisable = NULL;
	}
	if (m_pImgPinOver)
	{
		m_pImgPinOver->Destroy();
		delete m_pImgPinOver;
		m_pImgPinOver = NULL;
	}
	if (m_pImgPinDown)
	{
		m_pImgPinDown->Destroy();
		delete m_pImgPinDown;
		m_pImgPinDown = NULL;
	}
	if (m_pImgSelectedNormal)
	{
		m_pImgSelectedNormal->Destroy();
		delete m_pImgSelectedNormal;
		m_pImgSelectedNormal = NULL;
	}
	if (m_pImgPinSelectedOver)
	{
		m_pImgPinSelectedOver->Destroy();
		delete m_pImgPinSelectedOver;
		m_pImgPinSelectedOver = NULL;
	}
}


BOOL CMyPotatoListButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
	//return CButton::OnEraseBkgnd(pDC);
}


void CMyPotatoListButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bMouseOver = TRUE;
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT   tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE | TME_HOVER; //   
		tme.hwndTrack = GetSafeHwnd();
		tme.dwHoverTime = 8;
		_TrackMouseEvent(&tme);
		m_bTracking = TRUE;
	}
	CButton::OnMouseMove(nFlags, point);
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
}


void CMyPotatoListButton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bMouseOver = FALSE;
	m_bTracking = FALSE;
	m_bLBtnDown = FALSE;

	
	PaintParent();
	


	CButton::OnMouseLeave();
}


void CMyPotatoListButton::PaintParent()
{
	CRect   rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);
}


void CMyPotatoListButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bMouseOver = TRUE;
	PaintParent();
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	//CButton::OnMouseHover(nFlags, point);
}


BOOL CMyPotatoListButton::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.style |= BS_OWNERDRAW;

	return CButton::PreCreateWindow(cs);
}


BOOL CMyPotatoListButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类

	BOOL OK = CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
	ModifyStyleEx(0, WS_EX_TRANSPARENT);// WS_EX_LAYERED||WS_EX_TRANSPARENT

	return OK; 
	//return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}


void CMyPotatoListButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLBtnDown = TRUE;

	CRect   rect;
	//GetWindowRect(&rect);
	GetClientRect(&rect);
	rect.right = rect.left + 40;
	/*GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);*/
	if(point.x>=rect.left&&point.x<=rect.right&&point.y>=rect.top&&point.y<=rect.bottom)
	{
		m_bSelected = !m_bSelected;
	}

	if (m_bSelected)
	{
		GetClientRect(&rect);
		rect.left = rect.right - 40;
		if(point.x>=rect.left&&point.x<=rect.right&&point.y>=rect.top&&point.y<=rect.bottom)
		{
			GetParent()->PostMessage(WM_SYSCOMMAND, WM_DELETEPOTATO,0);
		}
	}
	
	GetClientRect(&rect);
	rect.left += 40;
	rect.right -= 40;
	if(point.x>=rect.left&&point.x<=rect.right&&point.y>=rect.top&&point.y<=rect.bottom)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_SYSCOMMAND, WM_POTATOTOTOMATO,(LPARAM)(LPCTSTR)m_strButtonName);
	}
	
	PaintParent();
	CButton::OnLButtonDown(nFlags, point);
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
}


void CMyPotatoListButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bLBtnDown = FALSE;
	PaintParent();
	CButton::OnLButtonUp(nFlags, point);
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
}


void CMyPotatoListButton::OnBnDoubleclicked()
{
	// TODO: 在此添加控件通知处理程序代码
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));
}


void CMyPotatoListButton::OnBnKillfocus()
{
	// TODO: 在此添加控件通知处理程序代码

	PaintParent();
}


// 初始化
void CMyPotatoListButton::init(void)
{
	m_pImgNormal = NULL;
	m_pImgOver = NULL;
	m_pImgDown = NULL;
	m_pImgFocus = NULL;
	m_pImgDisable = NULL;
	m_pImgPinOver = NULL;
	m_pImgPinDown = NULL;
	m_pImgSelectedNormal = NULL;
	m_pImgPinSelectedOver = NULL;

	m_bTracking = FALSE;
	m_bMouseOver = FALSE;
	m_bLBtnDown = FALSE;
	m_bSelected = FALSE;

	m_BrushOver.CreateSolidBrush(RGB(255,255,255));
	m_BrushSelectedOver.CreateSolidBrush(RGB(240,250,239));
	m_BrushgNormal.CreateSolidBrush(RGB(249, 249, 249));
	

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

	m_StrikeFont.CreateFont(
		20, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		FW_NORMAL, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		1, // cStrikeOut
		ANSI_CHARSET, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision
		CLIP_DEFAULT_PRECIS, // nClipPrecision
		DEFAULT_QUALITY, // nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("宋体") // nPitchAndFamily Arial
		);
}


int CMyPotatoListButton::GetImageType(CString& strImageName)
{
	int nType = 0;
	CString strExt = PathFindExtension(strImageName);
	strExt = strExt.Mid(1);

	if (strExt.CompareNoCase(_T("bmp")) == 0)     nType = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (strExt.CompareNoCase(_T("jpg")) == 0 || strExt.CompareNoCase(_T("jpeg")) == 0) nType = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (strExt.CompareNoCase(_T("gif")) == 0)    nType = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (strExt.CompareNoCase(_T("png")) == 0)    nType = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (strExt.CompareNoCase(_T("mng")) == 0 || strExt.CompareNoCase(_T("jng")) == 0) nType = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (strExt.CompareNoCase(_T("ico")) == 0)    nType = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (strExt.CompareNoCase(_T("tiff")) == 0 || strExt.CompareNoCase(_T("tif")) == 0) nType = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (strExt.CompareNoCase(_T("tga")) == 0)    nType = CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (strExt.CompareNoCase(_T("pcx")) == 0)    nType = CXIMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (strExt.CompareNoCase(_T("wbmp")) == 0)    nType = CXIMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (strExt.CompareNoCase(_T("wmf")) == 0 || strExt.CompareNoCase(_T("emf")) == 0) nType = CXIMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (strExt.CompareNoCase(_T("jbg")) == 0)    nType = CXIMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (strExt.CompareNoCase(_T("jp2")) == 0 || strExt.CompareNoCase(_T("j2k")) == 0) nType = CXIMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (strExt.CompareNoCase(_T("jpc")) == 0 || strExt.CompareNoCase(_T("j2c")) == 0) nType = CXIMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (strExt.CompareNoCase(_T("pgx")) == 0)    nType = CXIMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (strExt.CompareNoCase(_T("ras")) == 0)    nType = CXIMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (strExt.CompareNoCase(_T("pnm")) == 0 ||strExt.CompareNoCase(_T("pgm")) == 0 ||strExt.CompareNoCase(_T("ppm")) == 0) nType = CXIMAGE_FORMAT_PNM;
#endif
#if CXIMAGE_SUPPORT_SKA
	else if (strExt.CompareNoCase(_T("ska")) == 0)    nType = CXIMAGE_FORMAT_SKA;
#endif
#if CXIMAGE_SUPPORT_RAW
	else if (strExt.CompareNoCase(_T("raw")) == 0)    nType = CXIMAGE_FORMAT_RAW;
#endif
#if CXIMAGE_SUPPORT_PSD
	else if (strExt.CompareNoCase(_T("psd")) == 0)    nType = CXIMAGE_FORMAT_PSD;
#endif
	else nType = CXIMAGE_FORMAT_UNKNOWN;

	return nType;
}


HBRUSH CMyPotatoListButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CButton::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (m_bMouseOver && m_pImgOver)
	{
		//return CreateSolidBrush(RGB(250, 250, 250));
	}
	return hbr;
}
