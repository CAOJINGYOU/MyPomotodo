#include "StdAfx.h"
#include "CharTool.h"

// UNICODE µ½ MBCS
CStringA CharTool::WideCharToMultiByteCString(CStringW wstr)
{
	if (wstr.GetLength() <=0 )
	{
		return "";
	}

	int nTxtLen = WideCharToMultiByte(CP_ACP,
		0,
		wstr.GetBuffer(0),
		-1,
		NULL,
		0,
		NULL,
		NULL);

	char *szTxt = new char[nTxtLen + 1];
	WideCharToMultiByte(CP_ACP,
		0,
		wstr.GetBuffer(0),
		wstr.GetLength()+1,
		szTxt,
		nTxtLen + 1,
		NULL,
		NULL);

	CStringA strA(szTxt);

	delete []szTxt; 
	szTxt = NULL;

	return strA;
}

// MBCS µ½ UNICODE
CStringW CharTool::MultiByteCStringToWideChar(CStringA astr)
{
	if (astr.GetLength() <=0 )
	{
		return _T("");
	}

	int nTxtLen = MultiByteToWideChar(CP_ACP,
		0,
		astr.GetBuffer(0),
		-1,
		NULL,
		0);

	wchar_t *szTxt = new wchar_t[nTxtLen + 1];
	MultiByteToWideChar(CP_ACP,
		0,
		astr.GetBuffer(0),
		astr.GetLength()+1,
		szTxt,
		nTxtLen + 1);

	CStringW strW(szTxt);

	delete []szTxt; 
	szTxt = NULL;

	return strW;
}

// UNICODE µ½ MBCS
CStringA CharTool::WideCharToUtf8CString(CStringW wstr)
{
	if (wstr.GetLength() <=0 )
	{
		return "";
	}

	int nTxtLen = WideCharToMultiByte(CP_UTF8,
		0,
		wstr.GetBuffer(0),
		-1,
		NULL,
		0,
		NULL,
		NULL);

	char *szTxt = new char[nTxtLen + 1];
	WideCharToMultiByte(CP_UTF8,
		0,
		wstr.GetBuffer(0),
		wstr.GetLength()+1,
		szTxt,
		nTxtLen + 1,
		NULL,
		NULL);

	CStringA strA(szTxt);

	delete []szTxt; 
	szTxt = NULL;

	return strA;
}