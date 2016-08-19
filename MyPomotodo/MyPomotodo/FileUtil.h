// FileUtil.h: interface for the CFileUtil class.
//

#if !defined(AFX_FILEUTIL_H__727B17A0_5514_4A8A_9D4F_957C5A4FF93F__INCLUDED_)
#define AFX_FILEUTIL_H__727B17A0_5514_4A8A_9D4F_957C5A4FF93F__INCLUDED_

#pragma once

class CFileUtil
{
public:
	static CString SlashDir(LPCTSTR lpDirName);
	//! Ϊһ���ļ�ȫ�����������м�Ŀ¼
	/*!
	\param[in] pszFileName �ļ���Ŀ¼��ȫ��
	\param[in] bIsPath ��·���������ļ���
	\return �Ƿ񴴽��ɹ�
	*/
	static BOOL CreateDirectory(LPCTSTR pszFileName, BOOL bIsPath);
	
	// ���·��ת��Ϊ����·��
	static CString RelToAbs(LPCTSTR pszRefFile, LPCTSTR pszRel, BOOL bIsPath);

	// ����·��ת��Ϊ���·��
	static CString AbsToRel(LPCTSTR pszRefFile, LPCTSTR pszAbs, BOOL bIsPath);
	
	static BOOL IsFileOrDirExist(LPCTSTR lpName);
	static BOOL Rename(LPCTSTR lpOld, LPCTSTR lpNew);
	static BOOL CopyOneFile(LPCTSTR lpSourceFile, LPCTSTR lpDesFile, BOOL bFailIfExists);
	
	// �����ļ�
	static BOOL CopyFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir, BOOL bFailIfExists);
	// ֻ����ĳһ����չ�����ļ�
	static BOOL CopyFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir, LPCTSTR lpExtra,BOOL bFailIfExists);
	
	// �����ļ������ļ���
	static BOOL CopyDirsAndFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir);

	// ɾ���ļ��к��ļ����ڵ�����
	static BOOL DeleteDir(LPCTSTR lpDirName);
	static BOOL DeleteOneFile(LPCTSTR lpFileName);
	// ����Ŀ¼�µ��ļ�
	static int GetFilesOnDir(LPCTSTR lpDirName, CStringArray& aryStr, LPCTSTR lpExtra = NULL);
	// �������������Ŀ¼�µ��ļ�
	static int GetFilesOnDirEx(LPCTSTR lpDirName, CStringArray& aryStr, LPCTSTR lpExtra = NULL);

	// ��ȡĿ¼�µĵ�һ����Ŀ¼����
	static int GetSubDir(LPCTSTR lpDirName, CStringArray& aryStr);

	//! ѡ��Ŀ¼�Ի���
	static BOOL SelectFolder(HWND hParent, LPCTSTR lpTitle, LPTSTR lpPath);

	//! ��·���н������ļ�����
	static BOOL GetFileNameInPath(const CString strPath, CString& strFile, BOOL bWithEx = TRUE);

	//! ���ļ���ȫ·���н������ļ���Ŀ¼
	static BOOL GetFilePath(CString& strPath, const CString& strFile);

	//! ���һ��Ŀ¼���ļ��Ƿ����
	/*!
	\param[in] pszFileName Ŀ¼���ļ����ļ�ȫ���������Ŀ¼��ĩβҪ�з�б��
	\param[in] bWrite �Ƿ����д
	\return Ŀ¼���ļ��Ƿ���ڣ����bWriteΪTRUE��ͬʱҪ��ɶ�д
	*/
	static BOOL IsPathFileExists(LPCTSTR pszFileName, BOOL bWrite = FALSE);

	//! ����һ���ļ�·���ַ���
	/*!
	\param[in,out] strPath1 ·��1
	\param[in] strPath2 ·��2
	\return �Ƿ����ɳɹ�
	*/
	static BOOL NewFilePath(CString& strPath1,const CString& strPath2);

	//! �ڿ�ִ���ļ�·��������һ��ָ��·�� ��Ӧ�ó���Ŀ¼ΪC:\debug,�򷵻ص��ǣ�C:\debug\strMidPath
	/*!
	\param[in,out] strMidPath ·��1
	\return �����µ�·��
	*/
	static CString CFileUtil::NewFilePath2(const CString& strMidPath);
	//! �ı��ļ�ȫ���ĺ�׺��

	//! Ϊָ����·�������ļ���
	static CString PathAddFileName(const CString& strPath,const CString& strFileName);

	//! �ı��ļ�ȫ���ĺ�׺��
	/*!\
	\param[in] pszFileName �������ļ�ȫ�������ļ��Ƿ�����޹�
	\param[in] pszSuffix �µĺ�׺�����Ե㿪ͷ����".txt"
	\return �µ��ļ�ȫ��
	*/
	static CString ChangeFileNameSuffix(LPCTSTR pszFileName, LPCTSTR pszSuffix);

	//! ��ȫ·���ļ����õ��ļ�������������׺��
	/*!\
	\param[in,out] strFullPathName ������ȫ·�����ļ���������ļ���
	\return �Ƿ�ɹ�
	*/
	static CString GetFileNameNoSuffix(const CString& strFullPathName);

	//! ��Ӧ�ó����Ŀ¼������һ���ļ�·������Ӧ�ó���Ŀ¼ΪC:\debug,�򷵻ص��ǣ�C:\debug\strFileName
	/*!\
	\param[in] strFileName Ҫ���ɵ��ļ���
	\return ���������ɵ��ļ���
	*/
	static CString NewFullFileName(const CString& strFileName);

	//! ��Ӧ�ó����Ŀ¼������һ���ļ�·������Ӧ�ó���Ŀ¼ΪC:\debug,�򷵻ص��ǣ�C:\debug\strMidPath\strFileName
	/*!\
	\param[in] strMidPath  �м�·����
	\param[in] strFileName Ҫ���ɵ��ļ���
	\return ���������ɵ��ļ���
	*/
	static CString NewFullFileName2(const CString& strMidPath,const CString& strFileName);

	//! ɾ��һ��Ŀ¼���ļ�������վ��
	/*!
	\param[in] pszFileName Ŀ¼���ļ����ļ�ȫ���������Ŀ¼��ĩβҪ�з�б�ţ��ر�ע����ַ��������һ���ַ�������'\0'
	\return �Ƿ�ִ�гɹ�
	*/
	static BOOL DeletePathFile(LPCTSTR pszFileName);

	//! д��־�ļ�
	static BOOL WriteLog(const CString& strErrMsg);

	//! ��ָ����Ŀ¼���Ϸ�б��
	static void AddBackslash(CString& strPath);
	//! ȥ��ָ��Ŀ¼�ķ�б��
	static void RemoveBackslash(CString& strPath);
	//! ��ѡ���ļ��Ի���,����ѡ�е��ļ�·��
	static CString OpenFileDlg();

};

#endif // !defined(AFX_FILEUTIL_H__727B17A0_5514_4A8A_9D4F_957C5A4FF93F__INCLUDED_)
