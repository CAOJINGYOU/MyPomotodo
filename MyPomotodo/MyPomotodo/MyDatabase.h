#pragma once
#include "MySqlite3.h"
#include "MySqlite3.h"
#include <vector>
using namespace std;

typedef struct tagPotatoInfo
{
	tagPotatoInfo()
		:strPotatoName(_T(""))
		,nId(0)
		,bPin(FALSE)
	{}
	CString strPotatoName;					
	int nId;
	BOOL bPin;
}POTATOINFO,*PSPOTATOINFO;


typedef struct tagTomatoInfo
{
	tagTomatoInfo()
		:nId(0)
		,strTomatoName(_T(""))
		,strBeigTime(_T(""))
		,strEndTime(_T(""))
	{}
	int nId;
	CString strTomatoName;
	CString strBeigTime;
	CString strEndTime;

}TOMATOINFO,*PTOMATOINFO;

class CMyDatabase
{
public:
	CMyDatabase(void);
	~CMyDatabase(void);
	MySqlite3 m_MySqlite3;
	// 创建土豆表
	int CreateTablePotato(void);
	// db数据库文件名称
	CString m_strDbFile;
	vector<POTATOINFO> m_vPotatos;
	vector<TOMATOINFO> m_vTomatoInfo;
	int InsertTablePotato(CString strPotatoName);
	int SelectTablePotato(void);
	int SelectTablePotatoStmt(void);
	// 创建系统配置表
	int CreateSysConfigInfo(void);
	// 初始化
	int init(void);
	int CreateViewPotato(void);
	int InitSysConfigInfo(INISYSCONFIGINFO *SysConfigInfo);
	int UpdateSql(CString strUpdateSql);
	int InsertSysConfigInfo(void);
	int CreateTableTomato(void);
	int InsertTomato(CString strInsert);
	int SelectTableTomato(void);
	int UpdateSysConfigInfo(INISYSCONFIGINFO *SysConfigInfo);
};

