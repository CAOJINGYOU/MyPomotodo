#include "StdAfx.h"
#include "MyMp3.h"


CMyMp3::CMyMp3(void)
	: m_bInitSuce(false)
{
	m_pGrap = NULL;
	m_pControl = NULL;
	m_pEnvent = NULL;

	CoInitialize(NULL);

	Init();
}


CMyMp3::~CMyMp3(void)
{
	m_pGrap->Release();
	m_pControl->Release();
	m_pEnvent->Release();

	CoUninitialize();
}


bool CMyMp3::Init(void)
{
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGrap);

	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pGrap->QueryInterface(IID_IMediaControl, (void**)&m_pControl);

	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pControl->QueryInterface(IID_IMediaEvent, (void**)&m_pEnvent);

	if (FAILED(hr))
	{
		return false;
	}

	m_bInitSuce = true;

	return m_bInitSuce;
}


bool CMyMp3::Run(void)
{

	m_pControl->RenderFile(_T("metalbell.mp3"));

	if (m_bInitSuce)
	{
		m_pControl->Run();
		long lEvent = -1;
		m_pEnvent->WaitForCompletion(INFINITE, &lEvent);
	}

	return false;
}
