#pragma once

class CharTool
{
public:
	static CStringA WideCharToMultiByteCString(CStringW wstr);
	static CStringW MultiByteCStringToWideChar(CStringA astr);
	static CStringA WideCharToUtf8CString(CStringW wstr);
};
