// FileUtil.cpp: implementation of the CFileUtil class.
//

#include "stdafx.h"
#include "FileUtil.h"
#include <io.h>
#include <Shlwapi.h>
#include <shlobj.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static inline BOOL IsPathSlash(TCHAR ch)
{
	return ('\\' == ch || '/' == ch);
}

CString CFileUtil::SlashDir(LPCTSTR lpDirName)
{
	TCHAR szPath[MAX_PATH] = { 0 };
	lstrcpy(szPath, lpDirName);

	PathAddBackslash(szPath);

	return szPath;
}

BOOL CFileUtil::IsFileOrDirExist(LPCTSTR lpName)
{
	return (_taccess(lpName, 0) == 0);
}

// 为一个文件全名级联创建中间目录
BOOL CFileUtil::CreateDirectory(LPCTSTR pszFileName, BOOL bIsPath)
{
	TCHAR szPath[MAX_PATH];
	int i, nLen;
	TCHAR cSaveChar;

	if (NULL == pszFileName || 0 == pszFileName[0])
	{
		return FALSE;
	}

	lstrcpyn(szPath, pszFileName, MAX_PATH);
	if (bIsPath)
	{
		PathAddBackslash(szPath);
	}
	else
	{
		PathRemoveFileSpec(szPath);
		PathAddBackslash(szPath);
	}

	nLen = lstrlen(szPath);

	if (_taccess(szPath, 0) == 0)
		return TRUE;

    for (i = 2; i < nLen; i++)
    {
		if (IsPathSlash(szPath[i]) && szPath[i-1] != ':')
		{
	    	cSaveChar = szPath[i];
	    	szPath[i] = '\0';
	    	::CreateDirectory(szPath, NULL);
	    	szPath[i] = cSaveChar;
		}
    }
	
    return (_taccess(szPath, 0) == 0);
}

// 相对路径转换为绝对路径
CString CFileUtil::RelToAbs(LPCTSTR pszRefFile, LPCTSTR pszRel, BOOL bIsPath)
{
	ASSERT(pszRel != NULL && pszRefFile != NULL);
	TCHAR szPath[MAX_PATH];

	if (PathIsRelative(pszRel))
	{
		lstrcpy(szPath, pszRefFile);
		PathRemoveFileSpec(szPath);
		PathAppend(szPath, pszRel);
	}
	else
		lstrcpy(szPath, pszRel);
	
	if (bIsPath)
		PathAddBackslash(szPath);
	
	return szPath;
}

// 绝对路径转换为相对路径
CString CFileUtil::AbsToRel(LPCTSTR pszRefFile, LPCTSTR pszAbs, BOOL bIsPath)
{
	ASSERT(pszAbs != NULL && pszRefFile != NULL);
	TCHAR szPath[MAX_PATH];
	
	if (!PathRelativePathTo(szPath, pszRefFile, FILE_ATTRIBUTE_NORMAL, 
		pszAbs, bIsPath ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL))
	{
		lstrcpyn(szPath, pszAbs, MAX_PATH);
	}

	return szPath;
}

BOOL CFileUtil::Rename(LPCTSTR lpOld, LPCTSTR lpNew)
{
	return (_trename(lpOld, lpNew) == 0);
}

BOOL CFileUtil::CopyOneFile(LPCTSTR lpSourceFile, LPCTSTR lpDesFile, BOOL bFailIfExists)
{
	return CopyFile(lpSourceFile, lpDesFile, bFailIfExists);
}

// 拷贝文件
BOOL CFileUtil::CopyFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir,
		BOOL bFailIfExists)
{
	CStringArray aryStr;
	GetFilesOnDir(lpSourceDir, aryStr);
	if (aryStr.GetSize() > 0)
	{
		CString strSource;
		CString strDes;
		strSource = SlashDir(lpSourceDir);
		strDes = SlashDir(lpDesDir);
		for(int i = 0; i < aryStr.GetSize(); i++)
		{
			if (!CopyFile(strSource + aryStr[i], strDes + aryStr[i], bFailIfExists))
				return FALSE;
		}
	}

	return TRUE;
}

// 只拷贝某一个扩展名的文件
BOOL CFileUtil::CopyFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir, 
					  LPCTSTR lpExtra, BOOL bFailIfExists)
{
	CStringArray arrFiles;
	
	GetFilesOnDir(lpSourceDir,arrFiles,lpExtra);

	size_t nCount = arrFiles.GetSize();
	CString strPath = SlashDir(lpDesDir);
	CString strSourceDir = SlashDir(lpSourceDir);
	CString strFileName;

	for (size_t i = 0; i < nCount; i++)
	{
		if (!GetFileNameInPath(strSourceDir + arrFiles[i],strFileName))
			return FALSE;

		if (!CopyOneFile(strSourceDir + arrFiles[i],strPath + strFileName,bFailIfExists))
			return FALSE;
	}

	return TRUE;
}

// 拷贝文件和子文件夹
BOOL CFileUtil::CopyDirsAndFiles(LPCTSTR lpSourceDir, LPCTSTR lpDesDir)
{
	TCHAR szFrom[MAX_PATH];
	TCHAR szTo[MAX_PATH];
	memset(szFrom, 0, sizeof(TCHAR) * MAX_PATH);
	memset(szTo, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(szFrom, lpSourceDir);
	lstrcpy(szTo, lpDesDir);
	PathAddBackslash(szFrom);
	lstrcat(szFrom, _T("*.*"));

	SHFILEOPSTRUCT   fileOp;  
	memset(&fileOp, 0, sizeof(fileOp));  
	fileOp.wFunc = FO_COPY;  
	fileOp.fFlags = FOF_NOCONFIRMATION;  
	fileOp.pFrom = szFrom;  
	fileOp.pTo = szTo;  

	return 0 == ::SHFileOperation(&fileOp);  
}

// 深度搜索，
int CFileUtil::GetFilesOnDirEx(LPCTSTR lpDirName, CStringArray& aryStr, LPCTSTR lpExtra/* = NULL*/)
{
	CStringArray arrFiles;
	int nCount = GetFilesOnDir(lpDirName, arrFiles, lpExtra);
	CString strPath = SlashDir(lpDirName);

	for (int i = 0; i < nCount; i++)
	{
		aryStr.Add(strPath + arrFiles[i]);
	}

	CStringArray arrSubDir;
	if(GetSubDir(lpDirName,arrSubDir) > 0)
	{
		for (int j = 0; j < arrSubDir.GetSize(); j++)
		{
			GetFilesOnDirEx(strPath + arrSubDir[j] , aryStr, lpExtra);
		}
	}

	return (int)aryStr.GetSize();
}

int CFileUtil::GetFilesOnDir(LPCTSTR lpDirName, CStringArray& aryStr, LPCTSTR lpExtra/* = NULL*/)
{
	aryStr.RemoveAll();
	CString strDir;
	strDir = SlashDir(lpDirName);
	CString strExtra(lpExtra);
	if (strExtra.IsEmpty())
	{		
		strDir += _T("*.*");
	}
	else
		strDir += _T("*.") + strExtra;

	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(strDir, &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) ||
				((data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0) ||
				((data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0))
				continue;
			if ((lstrcmp(data.cFileName, _T(".")) == 0) || 
				(lstrcmp(data.cFileName, _T("..")) == 0))
				continue;

			aryStr.Add(data.cFileName);
		} 
		while(FindNextFile(hFind, &data));
	}

	return (int)aryStr.GetSize();
}

// 获取目录下的第一级子目录名称
int CFileUtil::GetSubDir(LPCTSTR lpDirName, CStringArray& aryStr)
{
	aryStr.RemoveAll();
	CString strDir;
	strDir = SlashDir(lpDirName);
	strDir += _T("*.*");

	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(strDir, &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) ||
				((data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0) ||
				((data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0))
			{
				continue;
			}
			
			if ((lstrcmp(data.cFileName, _T(".")) == 0) || 
				(lstrcmp(data.cFileName, _T("..")) == 0))
			{
				continue;
			}

			aryStr.Add(data.cFileName);
		} 
		while(FindNextFile(hFind, &data));

		// 关闭查找的文件句柄
		FindClose(hFind);
	}

	return (int)aryStr.GetSize();
}

// 删除文件夹和文件夹内的内容
BOOL CFileUtil::DeleteDir(LPCTSTR lpDirName)
{
	CString strFile;
	strFile = SlashDir(lpDirName);
	CString strDir(strFile);
	strFile += _T("*.*");	

	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(strFile, &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (((data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0) ||
				((data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0))
				continue;
			if ((lstrcmp(data.cFileName, _T(".")) == 0) || 
				(lstrcmp(data.cFileName, _T("..")) == 0))
				continue;

			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
				DeleteDir(CString(strDir) + data.cFileName);
			else 
				DeleteOneFile(CString(strDir) + data.cFileName);
		} 
		while(FindNextFile(hFind, &data));
	}

	FindClose(hFind);
	return RemoveDirectory(lpDirName);
}

BOOL CFileUtil::DeleteOneFile(LPCTSTR lpFileName)
{
	// 去掉只读属性
	if (FILE_ATTRIBUTE_NORMAL != GetFileAttributes(lpFileName)) 
		SetFileAttributes(lpFileName, FILE_ATTRIBUTE_NORMAL);
	
	return DeleteFile(lpFileName);
}

static int CALLBACK 
BrowseCallbackProc(HWND hwnd,		// Window handle to the browse dialog box
				   UINT uMsg,		// Value identifying the event
				   LPARAM lParam,	// Value dependent upon the message
				   LPARAM lpData)	// Application-defined value that was
				   // specified in the lParam member of the BROWSEINFO structure
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:		// sent when the browse dialog box has finished initializing. 
		{
			// set initial directory
			::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		}
		break;

	case BFFM_SELCHANGED:		// sent when the selection has changed
		{
			TCHAR szDir[MAX_PATH] = { 0 };

			// fail if non-filesystem
			BOOL bRet = SHGetPathFromIDList((LPITEMIDLIST) lParam, szDir);
			if (bRet)
			{
				// fail if folder not accessible
				if (_taccess(szDir, 0) != 0)
				{
					bRet = FALSE;
				}
				else
				{
					SHFILEINFO sfi;
					::SHGetFileInfo((LPCTSTR)lParam, 0, &sfi, sizeof(sfi), 
						SHGFI_PIDL | SHGFI_ATTRIBUTES);

					// fail if pidl is a link
					if (sfi.dwAttributes & SFGAO_LINK)
					{
						bRet = FALSE;
					}
				}
			}

			// if invalid selection, disable the OK button
			if (!bRet)
			{
				::EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
			}
		}
		break;
	}

	return 0;
}

BOOL CFileUtil::SelectFolder(HWND hwndOwner, LPCTSTR pszTitle, LPTSTR pszFolder)
{
	BOOL bRet = FALSE;

	// must call this if using BIF_USENEWUI
	if (SUCCEEDED(::OleInitialize(NULL)))
	{
		BROWSEINFO bi;
		LPITEMIDLIST pidl;

		// Get help on BROWSEINFO struct - it's got all the bit settings.
		ZeroMemory(&bi, sizeof(bi));
		bi.hwndOwner = hwndOwner;
		bi.pszDisplayName = pszFolder;
		bi.lpszTitle = pszTitle;
		bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
		bi.lpfn = BrowseCallbackProc;
		bi.lParam = (LPARAM) pszFolder;

		// This next call issues the dialog box.
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
		{
			if (::SHGetPathFromIDList(pidl, pszFolder))
			{
				// At this point pszFolder contains the selected path
				bRet = TRUE;
			}
			// Free the PIDL allocated by SHBrowseForFolder.
			::CoTaskMemFree(pidl);
		}
		::OleUninitialize();
	}

	return bRet;
}


BOOL CFileUtil::GetFileNameInPath(const CString strPath, CString& strFile, BOOL bWithEx)
{
	int nIndex = strPath.ReverseFind('\\');
	int nLen = strPath.GetLength();

	if (nIndex == nLen)
		return FALSE;

	strFile = strPath.Right(nLen - nIndex - 1);

	if (!bWithEx)
	{
		int nEx = strFile.ReverseFind('.');
		CString strName = strFile.Left(nEx);

		strFile = strName;
	}
	
	return TRUE;
}

// 从文件的全路径中解析出文件的目录
BOOL CFileUtil::GetFilePath(CString& strPath, const CString& strFile)
{
	int nIndex = strFile.ReverseFind('\\');
	int nLen = strFile.GetLength();

	if (nIndex == nLen)
		return FALSE;

	strPath = strFile.Left(nIndex + 1);

	return TRUE;
}

BOOL CFileUtil::IsPathFileExists(LPCTSTR pszFileName, BOOL bWrite)
{
	return (pszFileName != NULL && pszFileName[0] != 0
		&& _taccess(pszFileName, bWrite ? 6 : 0) == 0);
}

BOOL CFileUtil::NewFilePath(CString& strPath1, const CString& strPath2)
{
	TCHAR szFilePath[MAX_PATH] = { 0 };
	lstrcpy(szFilePath, strPath1);

	PathAppend(szFilePath, strPath2);
	PathAddBackslash(szFilePath);

	strPath1 = szFilePath;

	return TRUE;
}

CString CFileUtil::NewFilePath2(const CString& strMidPath)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TCHAR szPathFile[MAX_PATH] = { 0 };

	GetModuleFileName(AfxGetApp()->m_hInstance, szPathFile, MAX_PATH);

	PathRemoveFileSpec(szPathFile);
	PathAppend(szPathFile, strMidPath);

	PathAddBackslash(szPathFile);

	return szPathFile;
}


CString CFileUtil::PathAddFileName(const CString& strPath,const CString& strFileName)
{
	CString strPathFile;
	strPathFile.Format(_T("%s%s"), strPath, strFileName);

	return strPathFile;
}

CString CFileUtil::ChangeFileNameSuffix(LPCTSTR pszFileName, LPCTSTR pszSuffix)
{
	TCHAR szNewFile[MAX_PATH] = { 0 };

	if (pszFileName != NULL && pszSuffix != NULL)
	{
		ASSERT('.' == pszSuffix[0]);
		lstrcpyn(szNewFile, pszFileName, MAX_PATH);
		PathRenameExtension(szNewFile, pszSuffix);
	}

	return szNewFile;
}

CString CFileUtil::GetFileNameNoSuffix(const CString& strFullPathName)
{
	TCHAR szFileName[MAX_PATH] = { 0 };

	lstrcpy(szFileName, strFullPathName.Mid(strFullPathName.ReverseFind('\\') + 1));
	PathRemoveExtension(szFileName);

	return szFileName;
}

CString CFileUtil::NewFullFileName(const CString& strFileName)
{
	/*AFX_MANAGE_STATE(AfxGetStaticModuleState());*/

	TCHAR szPathFile[MAX_PATH] = { 0 };

	GetModuleFileName(AfxGetApp()->m_hInstance, szPathFile, MAX_PATH);

	PathRemoveFileSpec(szPathFile);
	PathAppend(szPathFile, strFileName);

	return szPathFile;
}

CString CFileUtil::NewFullFileName2(const CString& strMidPath,
									const CString& strFileName)
{
	/*AFX_MANAGE_STATE(AfxGetStaticModuleState());*/

	TCHAR szPathFile[MAX_PATH] = { 0 };

	GetModuleFileName(AfxGetApp()->m_hInstance, szPathFile, MAX_PATH);
	
	PathRemoveFileSpec(szPathFile);
	PathAppend(szPathFile, strMidPath);
	PathAppend(szPathFile, strFileName);

	return szPathFile;
}

BOOL CFileUtil::DeletePathFile(LPCTSTR pszFileName)
{
	ASSERT(pszFileName != NULL && !PathIsRelative(pszFileName));
	BOOL bRet = TRUE;
	if (IsPathFileExists(pszFileName))
	{
		SHFILEOPSTRUCT op;
		ZeroMemory(&op, sizeof(op));
		op.hwnd = HWND_DESKTOP;
		op.wFunc = FO_DELETE;
		op.pFrom = pszFileName;
		op.pTo = NULL;
		op.fFlags = FOF_SILENT|FOF_NOERRORUI|FOF_NOCONFIRMATION|FOF_ALLOWUNDO;
		bRet = (SHFileOperation(&op) == 0);
	}

	return bRet;
}

void CFileUtil::AddBackslash(CString& strPath)
{
	TCHAR szPath[MAX_PATH] = { 0 };
	lstrcpy(szPath, strPath);

	PathAddBackslash(szPath);

	strPath = szPath;
}

void CFileUtil::RemoveBackslash(CString& strPath)
{
	PathRemoveBackslash(strPath.GetBuffer(MAX_PATH));
	strPath.ReleaseBuffer();
}

BOOL CFileUtil::WriteLog(const CString& strErrMsg)
{
	/*AFX_MANAGE_STATE(AfxGetStaticModuleState());*/

	CString strModuleFile,strLogMsg,strTime;
	SYSTEMTIME localTime;

	// log 路径
	GetModuleFileName(AfxGetApp()->m_hInstance, strModuleFile.GetBuffer(MAX_PATH), MAX_PATH);
	strModuleFile.ReleaseBuffer();
	PathRenameExtension(strModuleFile.GetBuffer(MAX_PATH),_T(".log"));
	strModuleFile.ReleaseBuffer();

	// 打开文件，不存在就创建
	CStdioFile file(strModuleFile,CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate);
	
	file.SeekToEnd();//先定位到文件尾部

	// 写日志信息
	GetLocalTime(&localTime);
	CTime tm(localTime);
	strTime = tm.Format("%Y-%m-%d %H:%M:%S");

	strLogMsg.Format(_T("\nTime:%s; ErrInfo:%s"),strTime,strErrMsg);
	 
	file.WriteString(strLogMsg);

	// 关闭文件
	file.Close();

	return TRUE;
}

CString CFileUtil::OpenFileDlg()
{
	CString m_sourcePath = _T("");
	CString strFilter;
	strFilter="XML Files(*.xml)|*.xml||";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_EXPLORER|OFN_HIDEREADONLY|
		OFN_ENABLESIZING|OFN_FILEMUSTEXIST,strFilter);
	
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME);

	if(dlg.DoModal() == IDOK )
	{
		m_sourcePath=dlg.GetPathName();
	}
    
	return m_sourcePath;
}
