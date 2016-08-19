#include "stdafx.h"
#include "MySqlite3.h"
#include "FileUtil.h"
#include "CharTool.h"

typedef int (*sqlite3_callback)(void*,int,char**, char**);

int LoadMyInfo( void * para, int n_column, char ** column_value, char ** column_name )
{
	//para������ sqlite3_exec �ﴫ��� void * ����

	//ͨ��para����������Դ���һЩ�����ָ�루������ָ�롢�ṹָ�룩��Ȼ����������ǿ��ת���ɶ�Ӧ�����ͣ���������void*���ͣ�����ǿ��ת����������Ͳſ��ã���Ȼ�������Щ����

	//n_column����һ����¼�ж��ٸ��ֶ� (��������¼�ж�����)

	// char ** column_value �Ǹ��ؼ�ֵ������������ݶ������������ʵ�����Ǹ�1ά���飨��Ҫ��Ϊ��2ά���飩��ÿһ��Ԫ�ض���һ�� char * ֵ����һ���ֶ����ݣ����ַ�������ʾ����/0��β��

	//char ** column_name �� column_value�Ƕ�Ӧ�ģ���ʾ����ֶε��ֶ�����

	//����Ҳ�ʹ�� para �������������Ĵ���.

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


// �����ݿ�
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


// �ر����ݿ�
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
		strTemp.Format(_T("������ʧ�ܣ�������:%d������SQL:%s������ԭ��:%s/n"), result, strSQL, errmsg);
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
		strTemp.Format(_T("���������ʧ�ܣ�������:%d������ԭ��:%s/n"), result, errmsg);
		AfxMessageBox(strTemp);
	}

	CloseDb();

	return result;
}


int MySqlite3::SelectTableStmt(void)
{
	int result = SQLITE_OK;

	OpenDb(m_strDbFile);

	//5. �����ѯ�����ݵ�sqlite3_stmt����
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
				//������Ҫ���жϵ�ǰ��¼��ǰ�ֶε����ͣ��ٸ��ݷ��ص�����ʹ�ò�ͬ��API����
				//��ȡʵ�ʵ�����ֵ��
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
		strTemp.Format(_T("������ʧ�ܣ�������:%d������SQL:%s������ԭ��:%s/n"), result, strSQL, errmsg);
		AfxMessageBox(strTemp);
	}

	CloseDb();

	return result;
}
