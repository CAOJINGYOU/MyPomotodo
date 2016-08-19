#include "stdafx.h"
#include "MySqlite3.h"
#include "FileUtil.h"
#include "CharTool.h"

typedef int (*sqlite3_callback)(void*,int,char**, char**);

int LoadMyInfo( void * para, int n_column, char ** column_value, char ** column_name )
{
	//para是你在 sqlite3_exec 里传入的 void * 参数

	//通过para参数，你可以传入一些特殊的指针（比如类指针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据

	//n_column是这一条记录有多少个字段 (即这条记录有多少列)

	// char ** column_value 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char * 值，是一个字段内容（用字符串来表示，以/0结尾）

	//char ** column_name 跟 column_value是对应的，表示这个字段的字段名称

	//这里，我不使用 para 参数。忽略它的存在.

	int i;

	for( i = 0 ; i < n_column; i ++ )
	{
		CStringA strTemp;
		char* A = column_name[i];
		char* B = column_value[i];
	}

	DBINFO dbinfo;
	((vector<DBINFO>*)para)->push_back(dbinfo);

	return 0;
}

MySqlite3::MySqlite3()
	: conn(NULL)
	, m_strDbFile(_T(""))
{
}


MySqlite3::~MySqlite3()
{
}


// 打开数据库
int MySqlite3::OpenDb(CString strDbFile)
{
	m_strDbFile = strDbFile;

	int result = SQLITE_OK;
	
	CString strModuleFile = CFileUtil::NewFullFileName(strDbFile);

	result = sqlite3_open(CharTool::WideCharToUtf8CString(strModuleFile), &conn);

	if (result != SQLITE_OK)
	{
		CString str;
		str.Format(_T("%d--%s"),result,sqlite3_errmsg(conn));
		AfxMessageBox(str);
		result = -1;
	}

	return result;
}


// 关闭数据库
int MySqlite3::CloseDb(void)
{
	int result = SQLITE_OK;

	if (conn != NULL)
	{
		sqlite3_close(conn);
		conn = NULL;
	}
	return result;
}


int MySqlite3::CreateTable(CString strSQL)
{
	int result = SQLITE_OK;
	char * errmsg = NULL;

	OpenDb(m_strDbFile);

	result = sqlite3_exec( conn, CharTool::WideCharToMultiByteCString(strSQL), NULL, NULL, &errmsg );

	if(result != SQLITE_OK )
	{
		CString strTemp;
		strTemp.Format(_T("创建表失败，错误码:%d，错误SQL:%s，错误原因:%s/n"), result, strSQL, errmsg);
		AfxMessageBox(strTemp);
	}

	CloseDb();

	return result;
}


int MySqlite3::InsertTable(CString strSQL)
{
	int result = SQLITE_OK;
	char * errmsg = NULL;

	OpenDb(m_strDbFile);

	result = sqlite3_exec(conn, CharTool::WideCharToMultiByteCString(strSQL), NULL, NULL, &errmsg );

	if(result != SQLITE_OK )
	{
		CString strTemp;
		strTemp.Format(_T("插入表数据失败，错误码:%d，错误原因:%s/n"), result, errmsg);
		AfxMessageBox(strTemp);
	}

	CloseDb();

	return result;
}


int MySqlite3::SelectTableStmt(void)
{
	int result = SQLITE_OK;

	OpenDb(m_strDbFile);

	//5. 构造查询表数据的sqlite3_stmt对象。
	const char *selectSQL = "select * from MyPotato_view";
	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(conn, selectSQL, strlen(selectSQL), &stmt, NULL) != SQLITE_OK)
	{
		if (stmt)
			sqlite3_finalize(stmt);
		sqlite3_close(conn);
		result = -1;
		return result;
	}

	int fieldCount = sqlite3_column_count(stmt);

	do
	{
		int r = sqlite3_step(stmt);
		if (r == SQLITE_ROW)
		{
			for (int i = 0; i < fieldCount; ++i)
			{
				const char *vName = sqlite3_column_name(stmt, i);
				//这里需要先判断当前记录当前字段的类型，再根据返回的类型使用不同的API函数
				//获取实际的数据值。
				int vtype = sqlite3_column_type(stmt, i);
				if (vtype == SQLITE_INTEGER)
				{
					int v = sqlite3_column_int(stmt, i);
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
					printf("The TEXT value is %s.\n", v);
				}
				else if (vtype == SQLITE_NULL)
				{
					printf("This value is NULL.\n");
				}
			}
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
			sqlite3_close(conn);
			result = -1;
			return result;
		}
	}
	while (true);
	sqlite3_finalize(stmt);

	CloseDb();

	return result;
}


int MySqlite3::SelectTable(void)
{
	int result = SQLITE_OK;
	char * errmsg = NULL;

	OpenDb(m_strDbFile);

	CString strSQL = _T("select * from MyPotato_view");

	result = sqlite3_exec( conn, CharTool::WideCharToMultiByteCString(strSQL), LoadMyInfo, &m_vDbInfo, &errmsg );

	if(result != SQLITE_OK )
	{
		CString strTemp;
		strTemp.Format(_T("创建表失败，错误码:%d，错误SQL:%s，错误原因:%s/n"), result, strSQL, errmsg);
		AfxMessageBox(strTemp);
	}

	CloseDb();

	return result;
}
