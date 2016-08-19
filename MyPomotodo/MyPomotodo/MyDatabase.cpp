#include "StdAfx.h"
#include "MyDatabase.h"
#include "FileUtil.h"
#include "CharTool.h"

typedef int (*sqlite3_callback)(void*,int,char**, char**);

int LoadMyPomotoInfoDb( void * para, int n_column, char ** column_value, char ** column_name )
{
	//para是你在 sqlite3_exec 里传入的 void * 参数

	//通过para参数，你可以传入一些特殊的指针（比如类指针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据

	//n_column是这一条记录有多少个字段 (即这条记录有多少列)

	// char ** column_value 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char * 值，是一个字段内容（用字符串来表示，以/0结尾）

	//char ** column_name 跟 column_value是对应的，表示这个字段的字段名称

	//这里，我不使用 para 参数。忽略它的存在.

	int i;

	POTATOINFO potoinfo;
	
	for( i = 0 ; i < n_column; i ++ )
	{
		CString strTemp;
		strTemp = CharTool::MultiByteCStringToWideChar(column_value[i]);
		if (i==0)
		{
			potoinfo.strPotatoName = strTemp;
		}
		if (i==1)
		{
			potoinfo.nId = atoi(column_value[i]);
		}
		if (i==2)
		{
			potoinfo.bPin = atoi(column_value[i]);
		}
	}
	((vector<POTATOINFO>*)para)->push_back(potoinfo);

	return 0;
}

int LoadMyTomatoInfoDb( void * para, int n_column, char ** column_value, char ** column_name )
{
	//para是你在 sqlite3_exec 里传入的 void * 参数

	//通过para参数，你可以传入一些特殊的指针（比如类指针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据

	//n_column是这一条记录有多少个字段 (即这条记录有多少列)

	// char ** column_value 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char * 值，是一个字段内容（用字符串来表示，以/0结尾）

	//char ** column_name 跟 column_value是对应的，表示这个字段的字段名称

	//这里，我不使用 para 参数。忽略它的存在.

	int i;

	TOMATOINFO tomatoInfo;

	for( i = 0 ; i < n_column; i ++ )
	{
		CString strTemp;
		strTemp = CharTool::MultiByteCStringToWideChar(column_value[i]);
		if (i==0)
		{
			tomatoInfo.nId = atoi(column_value[i]);
		}
		if (i==1)
		{
			tomatoInfo.strTomatoName = strTemp;
		}
		if (i==2)
		{
			tomatoInfo.strBeigTime = strTemp;
		}
		if (i==3)
		{
			tomatoInfo.strEndTime = strTemp;
		}
	}
	((vector<TOMATOINFO>*)para)->push_back(tomatoInfo);

	return 0;
}

CMyDatabase::CMyDatabase(void)
	: m_strDbFile(_T("MyPomotodo.db"))
{
	m_MySqlite3.m_strDbFile = m_strDbFile;
}


CMyDatabase::~CMyDatabase(void)
{
}


// 创建土豆表
int CMyDatabase::CreateTablePotato(void)
{
	int result = SQLITE_OK;

	CString strSQL = _T("CREATE TABLE IF NOT EXISTS [MyPotato] (				\
		[ID] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,						\
		[CreateTime] TIMESTAMP DEFAULT (datetime('now','localtime')) NOT NULL,	\
		[PotatoName] NVARCHAR(256)  NULL,										\
		[Finish] BOOLEAN DEFAULT '0' NOT NULL,									\
		[Pin] BOOLEAN DEFAULT '0' NOT NULL										\
		)");

	result = m_MySqlite3.CreateTable(strSQL);

	return result;
}


int CMyDatabase::InsertTablePotato(CString strPotatoName)
{
	int result = 1;
	char * errmsg = NULL;

	m_MySqlite3.OpenDb(m_strDbFile);

	CString strSQL;
	strSQL.Format(_T("insert into MyPotato( PotatoName ) values (\"%s\")"), strPotatoName);

	result = m_MySqlite3.InsertTable(strSQL);

	return result;
}


int CMyDatabase::SelectTablePotato(void)
{
	//m_vPotatos.clear();
	vector<POTATOINFO>().swap(m_vPotatos); 

	int result = SQLITE_OK;
	char * errmsg = NULL;

	m_MySqlite3.OpenDb(m_strDbFile);

	CString strSQL = _T("select * from MyPotato_view");

	result = sqlite3_exec( m_MySqlite3.conn, CharTool::WideCharToMultiByteCString(strSQL), LoadMyPomotoInfoDb, &m_vPotatos, &errmsg );

	if(result != SQLITE_OK )
	{
		CString strTemp;
		strTemp.Format(_T("查询表失败，错误码:%d，错误SQL:%s，错误原因:%s/n"), result, strSQL, errmsg);
		AfxMessageBox(strTemp);
	}

	m_MySqlite3.CloseDb();

	return result;
}


int CMyDatabase::SelectTablePotatoStmt(void)
{
	m_MySqlite3.OpenDb(m_strDbFile);

	//5. 构造查询表数据的sqlite3_stmt对象。
	const char *selectSQL = "select * from MyPotato_view";
	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(m_MySqlite3.conn, selectSQL, strlen(selectSQL), &stmt, NULL) != SQLITE_OK)
	{
		if (stmt)
			sqlite3_finalize(stmt);
		sqlite3_close(m_MySqlite3.conn);
		return 0;
	}
	int fieldCount = sqlite3_column_count(stmt);
	//int fieldDataCount = sqlite3_data_count(stmt);
	do
	{
		int r = sqlite3_step(stmt);
		if (r == SQLITE_ROW)
		{
			CString c1 = _T("");
			int c2 = 0;

			for (int i = 0; i < fieldCount; ++i)
			{
				const char *vName = sqlite3_column_name(stmt, i);
				//这里需要先判断当前记录当前字段的类型，再根据返回的类型使用不同的API函数
				//获取实际的数据值。
				int vtype = sqlite3_column_type(stmt, i);
				if (vtype == SQLITE_INTEGER)
				{
					int v = sqlite3_column_int(stmt, i);
					c2 = v;
					printf("The INTEGER value is %d.\n", v);
				}
				else if (vtype == SQLITE_FLOAT)
				{
					double v = sqlite3_column_double(stmt, i);
					printf("The DOUBLE value is %f.\n", v);
				}
				else if (vtype == SQLITE_TEXT)
				{
					const char *v = (const char *)sqlite3_column_text(stmt, i);
					c1 = v;
					printf("The TEXT value is %s.\n", v);
				}
				else if (vtype == SQLITE_NULL)
				{
					printf("This value is NULL.\n");
				}
			}
			//m_vPotatos->push_back(c1, c2);
		}
		else if (r == SQLITE_DONE)
		{
			printf("Select Finished.\n");
			break;
		}
		else
		{
			printf("Failed to SELECT.\n");
			sqlite3_finalize(stmt);
			sqlite3_close(m_MySqlite3.conn);
			return 0;
		}
	}
	while (true);
	sqlite3_finalize(stmt);

	m_MySqlite3.CloseDb();

	return 0;
}


// 创建系统配置表
int CMyDatabase::CreateSysConfigInfo(void)
{
	int result = SQLITE_OK;

	CString strSQL = _T("CREATE TABLE IF NOT EXISTS[SysConfigInfo] (\
		[TomatoTime] INTEGER DEFAULT '25' NOT NULL,\
		[RestTime] INTEGER DEFAULT '5' NOT NULL,\
		[LongRestTime] INTEGER DEFAULT '15' NOT NULL,\
		[LongRestInterval] INTEGER DEFAULT '4' NOT NULL,\
		[strWorkSound] NVARCHAR(256)  NULL,\
		[strThatSound] NVARCHAR(256)  NULL,\
		[DisplaySystemNotifications] BOOLEAN DEFAULT '1' NOT NULL,\
		[PlayTick] BOOLEAN DEFAULT '0' NOT NULL,\
		[PlayPromptSound] BOOLEAN DEFAULT '1' NOT NULL,\
		[RunningWithSystem] BOOLEAN DEFAULT '0' NOT NULL,\
		[FromSystemTray] BOOLEAN DEFAULT '0' NOT NULL,\
		[AutoAdjustSize] BOOLEAN DEFAULT '0' NOT NULL,\
		[State] INTEGER DEFAULT '0' NOT NULL,\
		[WorkTime] NVARCHAR(256) NULL,\
		[WorkRestTime] NVARCHAR(256) NULL\
		)");

	result = m_MySqlite3.CreateTable(strSQL);

	return result;
}


// 初始化
int CMyDatabase::init(void)
{
	CreateTablePotato();
	CreateViewPotato();
	CreateTableTomato();

	CreateSysConfigInfo();

	return 0;
}


int CMyDatabase::CreateViewPotato(void)
{
	int result = SQLITE_OK;

	CString strSQL = _T("CREATE VIEW IF NOT EXISTS [MyPotato_view] AS\
		select PotatoName,ID,Pin from MyPotato where Finish = 0 order by Pin DESC,CreateTime DESC,ID DESC\
						");

	result = m_MySqlite3.CreateTable(strSQL);

	return result;
}


int CMyDatabase::InitSysConfigInfo(INISYSCONFIGINFO *SysConfigInfo)
{
	int result = SQLITE_OK;

	m_MySqlite3.OpenDb(m_strDbFile);

	//5. 构造查询表数据的sqlite3_stmt对象。
	const char *selectSQL = "select * from SysConfigInfo";
	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(m_MySqlite3.conn, selectSQL, strlen(selectSQL), &stmt, NULL) != SQLITE_OK)
	{
		if (stmt)
			sqlite3_finalize(stmt);
		sqlite3_close(m_MySqlite3.conn);
		return 0;
	}
	int fieldCount = sqlite3_column_count(stmt);
	//int fieldDataCount = sqlite3_data_count(stmt);
	do
	{
		int r = sqlite3_step(stmt);
		if (r == SQLITE_ROW)
		{
			CString c1 = _T("");
			int c2 = 0;

			for (int i = 0; i < fieldCount; ++i)
			{
				const char *vName = sqlite3_column_name(stmt, i);
				//这里需要先判断当前记录当前字段的类型，再根据返回的类型使用不同的API函数
				//获取实际的数据值。
				int vtype = sqlite3_column_type(stmt, i);
				if (vtype == SQLITE_INTEGER)
				{
					int v = sqlite3_column_int(stmt, i);
					c2 = v;
					//printf("The INTEGER value is %d.\n", v);
				}
				else if (vtype == SQLITE_FLOAT)
				{
					double v = sqlite3_column_double(stmt, i);
					//printf("The DOUBLE value is %f.\n", v);
				}
				else if (vtype == SQLITE_TEXT)
				{
					const char *v = (const char *)sqlite3_column_text(stmt, i);
					c1 = v;
					//printf("The TEXT value is %s.\n", v);
				}
				else if (vtype == SQLITE_NULL)
				{
					//printf("This value is NULL.\n");
				}

				switch (i)
				{
				case 0:
					SysConfigInfo->lTomatoTime = c2;
					break;
				case 1:
					SysConfigInfo->lRestTime = c2;
					break;
				case 2:
					SysConfigInfo->lLongRestTime = c2;
					break;
				case 3:
					SysConfigInfo->uLongRestInterval = c2;
					break;
				case 4:
					SysConfigInfo->strWorkSound = c1;
					break;
				case 5:
					SysConfigInfo->strThatSound = c1;
					break;
				case 6:
					SysConfigInfo->bDisplaySystemNotifications = c2;
					break;
				case 7:
					SysConfigInfo->bPlayTick = c2;
					break;
				case 8:
					SysConfigInfo->bPlayPromptSound = c2;
					break;
				case 9:
					SysConfigInfo->bRunningWithSystem = c2;
					break;
				case 10:
					SysConfigInfo->bFromSystemTray = c2;
					break;
				case 11:
					SysConfigInfo->bAutoAdjustSize = c2;
					break;
				case 12:
					SysConfigInfo->uState = c2;
					break;
				case 13:
					SysConfigInfo->strWorkTime = c1;
					break;
				case 14:
					SysConfigInfo->strWorkRestTime = c1;
					break;
				default:
					break;
				}
			}
			//m_vPotatos->push_back(c1, c2);
			break;
		}
		else if (r == SQLITE_DONE)
		{
			result = SQLITE_DONE;
			break;
		}
		else
		{
			result = 1;
			sqlite3_finalize(stmt);
			sqlite3_close(m_MySqlite3.conn);
			return 0;
		}
	}
	while (true);

	sqlite3_finalize(stmt);

	m_MySqlite3.CloseDb();

	return result;
}


int CMyDatabase::UpdateSql(CString strUpdateSql)
{
	int result = SQLITE_OK;

	result = m_MySqlite3.CreateTable(strUpdateSql);

	return result;
}


int CMyDatabase::InsertSysConfigInfo(void)
{
	int result = SQLITE_OK;
	CString strInsert = _T("insert into SysConfigInfo values (25, 5, 15, 4, \"\", \"\", 1, 0, 1, 0, 0, 0, 0,datetime('now','localtime'),datetime('now','localtime'))");
	result = m_MySqlite3.CreateTable(strInsert);

	return result;
}


int CMyDatabase::CreateTableTomato(void)
{
	int result = SQLITE_OK;
	CString strInsert = _T("CREATE TABLE IF NOT EXISTS [MyTomato] (\
		[ID] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,\
		[TomatoName] NVARCHAR(256)  NULL,\
		[BeigTime] TIMESTAMP DEFAULT (datetime('now','localtime')) NOT NULL,\
		[EndTime] TIMESTAMP DEFAULT (datetime('now','localtime')) NOT NULL\
		)");
	result = m_MySqlite3.CreateTable(strInsert);

	return result;
}


int CMyDatabase::InsertTomato(CString strInsert)
{
	int result = SQLITE_OK;
	result = m_MySqlite3.CreateTable(strInsert);

	return result;
}


int CMyDatabase::SelectTableTomato(void)
{
	vector<TOMATOINFO>().swap(m_vTomatoInfo); 

	int result = SQLITE_OK;
	char * errmsg = NULL;

	m_MySqlite3.OpenDb(m_strDbFile);

	CString strSQL = _T("select * from MyTomato order by ID DESC");

	result = sqlite3_exec( m_MySqlite3.conn, CharTool::WideCharToMultiByteCString(strSQL), LoadMyTomatoInfoDb, &m_vTomatoInfo, &errmsg );

	if(result != SQLITE_OK )
	{
		CString strTemp;
		strTemp.Format(_T("查询表失败，错误码:%d，错误SQL:%s，错误原因:%s/n"), result, strSQL, errmsg);
		AfxMessageBox(strTemp);
	}

	m_MySqlite3.CloseDb();

	return result;
}


int CMyDatabase::UpdateSysConfigInfo(INISYSCONFIGINFO *SysConfigInfo)
{
	int result = SQLITE_OK;

	CString strUpdate;
	strUpdate.Format(_T("update SysConfigInfo set \
		TomatoTime=%I64d,\
		RestTime=%I64d,\
		LongRestTime=%I64d,\
		LongRestInterval=%d,\
		DisplaySystemNotifications=%d,\
		PlayTick=%d,\
		PlayPromptSound=%d,\
		RunningWithSystem=%d,\
		FromSystemTray=%d,\
		AutoAdjustSize=%d"),
		SysConfigInfo->lTomatoTime,
		SysConfigInfo->lRestTime,
		SysConfigInfo->lLongRestTime,
		SysConfigInfo->uLongRestInterval,
		SysConfigInfo->bDisplaySystemNotifications,
		SysConfigInfo->bPlayTick,
		SysConfigInfo->bPlayPromptSound,
		SysConfigInfo->bRunningWithSystem,
		SysConfigInfo->bFromSystemTray,
		SysConfigInfo->bAutoAdjustSize
		);

	result = UpdateSql(strUpdate);

	return result;
}
