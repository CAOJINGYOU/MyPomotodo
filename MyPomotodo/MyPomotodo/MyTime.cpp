#include "StdAfx.h"
#include "MyTime.h"
#include "CharTool.h"


CMyTime::CMyTime(void)
	: m_gStartTime(0)
{
}


CMyTime::~CMyTime(void)
{
}


CTime CMyTime::GetNowTime(void)
{
	return CTime::GetCurrentTime();
}


LONG CMyTime::GetTimeSpanSeconds(void)
{
	return GetTimeSpan().GetSeconds();
}

LONGLONG CMyTime::GetTimeSpanTotalSeconds(void)
{
	return GetTimeSpan().GetTotalSeconds();
}

CTimeSpan CMyTime::GetTimeSpan(void)
{
	return GetNowTime()-GetStartTime();
}


LONG CMyTime::GetTimeSpanMinutes(void)
{
	return GetTimeSpan().GetMinutes();
}


LONGLONG CMyTime::GetTimeSpanTotalMinutes(void)
{
	return GetTimeSpan().GetTotalMinutes();
}


LONG CMyTime::GetTimeSpanHours(void)
{
	return GetTimeSpan().GetHours();
}

LONGLONG CMyTime::GetTimeSpanTotalHours(void)
{
	return GetTimeSpan().GetTotalHours();
}


LONGLONG CMyTime::GetTimeSpanDays(void)
{
	return GetTimeSpan().GetDays();
}


CTime CMyTime::StringToTime(CString strTime)
{
	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
	sscanf(CharTool::WideCharToMultiByteCString(strTime),    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
	
	return CTime(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
}


CString CMyTime::TimeToString(CTime tTime)
{
	return tTime.Format("%Y-%m-%d %H:%M:%S");
}
