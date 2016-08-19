#pragma once

#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")

#include <vector>
using namespace std;

typedef struct tagDbInfo
{
	tagDbInfo()
		:strPotatoName(_T(""))
		,nId(0)
	{}
	CString strPotatoName;					
	int nId;			
}DBINFO,*PSDBINFO;

class MySqlite3
{
public:
	MySqlite3();
	~MySqlite3();
	sqlite3* conn;
	// 打开数据库
	int OpenDb(CString strDbFile);
	// 关闭数据库
	int CloseDb(void);
	int CreateTable(CString strSQL);
	CString m_strDbFile;
	vector<DBINFO> m_vDbInfo;
	int InsertTable(CString strSQL);
	int SelectTableStmt(void);
	int SelectTable(void);
};

