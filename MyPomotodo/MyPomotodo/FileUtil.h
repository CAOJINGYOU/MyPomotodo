// FileUtil.h: interface for the CFileUtil class.
//

#if !defined(AFX_FILEUTIL_H__727B17A0_5514_4A8A_9D4F_957C5A4FF93F__INCLUDED_)
#define AFX_FILEUTIL_H__727B17A0_5514_4A8A_9D4F_957C5A4FF93F__INCLUDED_

#pragma once

class CFileUtil
{
public:
	static CString SlashDir(LPCTSTR lpDirName);
	//! 为一个文件全名级联创建中间目录
	/*!
	\param[in] pszFileName 文件或目录的全名
	\param[in] bIsPath 是路径名还是文件名
	\return 是否创建成功
	*/
	static BOOL CreateDirectory(LPCTSTR pszFileName, BOOL bIsPath);
	
	// 相对路径转换为绝对路径
	static CString RelToAbs(LPCTSTR pszRefFile, LPCTSTR pszRel, BOOL bIsPath);

	// 绝对路径转换为相对路径
	static CString AbsToRel(LPCTSTR pszRefFile, LPCTSTR pszAbs, BOOL bIsPath);
	
	static BOOL IsFileOrDirExist(LPCTSTR lpName);
	static BOOL Rename(LPCTSTR lpOld, LPCTSTR lpNew);
	static BOOL CopyOneFile(LPCTSTR lpSourceFile, LPCTSTR lpDesFile, BOOL bFailIfExists);
	
	// 拷贝文件
	static BOOL CopyFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir, BOOL bFailIfExists);
	// 只拷贝某一个扩展名的文件
	static BOOL CopyFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir, LPCTSTR lpExtra,BOOL bFailIfExists);
	
	// 拷贝文件和子文件夹
	static BOOL CopyDirsAndFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir);

	// 删除文件夹和文件夹内的内容
	static BOOL DeleteDir(LPCTSTR lpDirName);
	static BOOL DeleteOneFile(LPCTSTR lpFileName);
	// 查找目录下的文件
	static int GetFilesOnDir(LPCTSTR lpDirName, CStringArray& aryStr, LPCTSTR lpExtra = NULL);
	// 深度搜索，查找目录下的文件
	static int GetFilesOnDirEx(LPCTSTR lpDirName, CStringArray& aryStr, LPCTSTR lpExtra = NULL);

	// 获取目录下的第一级子目录名称
	static int GetSubDir(LPCTSTR lpDirName, CStringArray& aryStr);

	//! 选择目录对话框
	static BOOL SelectFolder(HWND hParent, LPCTSTR lpTitle, LPTSTR lpPath);

	//! 从路径中解析出文件名称
	static BOOL GetFileNameInPath(const CString strPath, CString& strFile, BOOL bWithEx = TRUE);

	//! 从文件的全路径中解析出文件的目录
	static BOOL GetFilePath(CString& strPath, const CString& strFile);

	//! 检查一个目录或文件是否存在
	/*!
	\param[in] pszFileName 目录或文件的文件全名，如果是目录则末尾要有反斜号
	\param[in] bWrite 是否检查可写
	\return 目录或文件是否存在，如果bWrite为TRUE则同时要求可读写
	*/
	static BOOL IsPathFileExists(LPCTSTR pszFileName, BOOL bWrite = FALSE);

	//! 生成一个文件路径字符串
	/*!
	\param[in,out] strPath1 路径1
	\param[in] strPath2 路径2
	\return 是否生成成功
	*/
	static BOOL NewFilePath(CString& strPath1,const CString& strPath2);

	//! 在可执行文件路径下生成一个指定路径 如应用程序目录为C:\debug,则返回的是：C:\debug\strMidPath
	/*!
	\param[in,out] strMidPath 路径1
	\return 返回新的路径
	*/
	static CString CFileUtil::NewFilePath2(const CString& strMidPath);
	//! 改变文件全名的后缀名

	//! 为指定的路径加上文件名
	static CString PathAddFileName(const CString& strPath,const CString& strFileName);

	//! 改变文件全名的后缀名
	/*!\
	\param[in] pszFileName 给定的文件全名，和文件是否存在无关
	\param[in] pszSuffix 新的后缀名，以点开头形如".txt"
	\return 新的文件全名
	*/
	static CString ChangeFileNameSuffix(LPCTSTR pszFileName, LPCTSTR pszSuffix);

	//! 由全路径文件名得到文件名，不包括后缀名
	/*!\
	\param[in,out] strFullPathName 给定的全路径的文件名，输出文件名
	\return 是否成功
	*/
	static CString GetFileNameNoSuffix(const CString& strFullPathName);

	//! 在应用程序的目录下生成一个文件路径，如应用程序目录为C:\debug,则返回的是：C:\debug\strFileName
	/*!\
	\param[in] strFileName 要生成的文件名
	\return 返回新生成的文件名
	*/
	static CString NewFullFileName(const CString& strFileName);

	//! 在应用程序的目录下生成一个文件路径，如应用程序目录为C:\debug,则返回的是：C:\debug\strMidPath\strFileName
	/*!\
	\param[in] strMidPath  中间路径名
	\param[in] strFileName 要生成的文件名
	\return 返回新生成的文件名
	*/
	static CString NewFullFileName2(const CString& strMidPath,const CString& strFileName);

	//! 删除一个目录或文件到回收站中
	/*!
	\param[in] pszFileName 目录或文件的文件全名，如果是目录则末尾要有反斜号，特别注意该字符串的最后一个字符必须是'\0'
	\return 是否执行成功
	*/
	static BOOL DeletePathFile(LPCTSTR pszFileName);

	//! 写日志文件
	static BOOL WriteLog(const CString& strErrMsg);

	//! 给指定的目录加上反斜杠
	static void AddBackslash(CString& strPath);
	//! 去掉指定目录的反斜杠
	static void RemoveBackslash(CString& strPath);
	//! 打开选择文件对话框,返回选中的文件路径
	static CString OpenFileDlg();

};

#endif // !defined(AFX_FILEUTIL_H__727B17A0_5514_4A8A_9D4F_957C5A4FF93F__INCLUDED_)
