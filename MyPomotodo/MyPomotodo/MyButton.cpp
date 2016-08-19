// MyButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPomotodo.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton(CString strBtnDown, CString strBtnOver, CString strBtnNormal, CString strBtnDisabled, CString strBtnFocus)
{
	init();

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
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, &CMyButton::OnBnDoubleclicked)
	ON_CONTROL_REFLECT(BN_KILLFOCUS, &CMyButton::OnBnKillfocus)
END_MESSAGE_MAP()



// CMyButton ��Ϣ�������




void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����

	CDC ButtonDC;
	CRect rc;

	ButtonDC.Attach(lpDrawItemStruct->hDC); //�õ����ڻ��ư�ť��DC    
	rc = lpDrawItemStruct->rcItem; //��ȡ��ť��ռ�ľ��δ�С   

	UINT state = lpDrawItemStruct->itemState; //��ȡ��ťĿǰ������״̬�����ݲ�ͬ��״̬���Ʋ�ͬ�İ�ť    

	if (state&ODS_DISABLED && m_pImgDisable)
	{
		m_pImgDisable->Draw(ButtonDC.GetSafeHdc(), rc);
	}
	else
	{
		if (m_bLBtnDown && m_pImgDown)
		{
			m_pImgDown->Draw(ButtonDC.GetSafeHdc(), rc);
		}
		else if (m_bMouseOver && m_pImgOver)
		{
			m_pImgOver->Draw(ButtonDC.GetSafeHdc(), rc);
		}
		else if (state&ODS_FOCUS && m_pImgFocus)
		{
			m_pImgFocus->Draw(ButtonDC.GetSafeHdc(), rc);
		}
		else if (m_pImgNormal)
		{
			m_pImgNormal->Draw(ButtonDC.GetSafeHdc(), rc);
		}
	}
}


void CMyButton::OnDestroy()
{
	CButton::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

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
}


BOOL CMyButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
	//return CButton::OnEraseBkgnd(pDC);
}


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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


void CMyButton::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_bMouseOver = FALSE;
	m_bTracking = FALSE;
	m_bLBtnDown = FALSE;
	PaintParent();

	CButton::OnMouseLeave();
}


void CMyButton::PaintParent()
{
	CRect   rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);
}


void CMyButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_bMouseOver = TRUE;
	PaintParent();
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	//CButton::OnMouseHover(nFlags, point);
}


BOOL CMyButton::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style |= BS_OWNERDRAW;

	return CButton::PreCreateWindow(cs);
}


BOOL CMyButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL OK = CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
	ModifyStyleEx(0, WS_EX_TRANSPARENT);// WS_EX_LAYERED||WS_EX_TRANSPARENT

	return OK; 
	//return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}


void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLBtnDown = TRUE;
	PaintParent();
	CButton::OnLButtonDown(nFlags, point);
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
}


void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_bLBtnDown = FALSE;
	PaintParent();
	CButton::OnLButtonUp(nFlags, point);
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
}


void CMyButton::OnBnDoubleclicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));
}


void CMyButton::OnBnKillfocus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	PaintParent();
}


// ��ʼ��
void CMyButton::init(void)
{
	m_pImgNormal = NULL;
	m_pImgOver = NULL;
	m_pImgDown = NULL;
	m_pImgFocus = NULL;
	m_pImgDisable = NULL;
	m_bTracking = FALSE;
	m_bMouseOver = FALSE;
	m_bLBtnDown = FALSE;
}


int CMyButton::GetImageType(CString& strImageName)
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
