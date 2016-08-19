#pragma once
#include "atltime.h"
class CMyTime
{
public:
	CMyTime(void);
	~CMyTime(void);
private:
	CTime m_gStartTime;
public:
	CTime GetStartTime() const { return m_gStartTime; }
	void SetStartTime(CTime val) { m_gStartTime = val; }

	CTime GetNowTime(void);
	LONG GetTimeSpanSeconds(void);
	LONGLONG GetTimeSpanTotalSeconds(void);
	CTimeSpan GetTimeSpan(void);
	LONG GetTimeSpanMinutes(void);
	LONGLONG GetTimeSpanTotalMinutes(void);
	LONG GetTimeSpanHours(void);
	LONGLONG GetTimeSpanTotalHours(void);
	LONGLONG GetTimeSpanDays(void);
	CTime StringToTime(CString strTime);
	CString TimeToString(CTime tTime);
};

