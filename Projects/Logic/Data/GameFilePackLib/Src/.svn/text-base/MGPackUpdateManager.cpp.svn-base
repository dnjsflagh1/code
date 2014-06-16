#include "stdafx.h"
#include "GameFilePackManager.h"
#include "MGPackUpdateManager.h"

#include <Imagehlp.h>
#include <strsafe.h>
#include <ShellAPI.h>

namespace MG
{
	MGPackUpdateManager::MGPackUpdateManager()
	{
		mPackManager = MG_NEW MGPackManager();
	}

	MGPackUpdateManager::~MGPackUpdateManager()
	{
		MG_SAFE_DELETE(mPackManager);
	}

	bool MGPackUpdateManager::resUpdate( const std::string& zipname, const std::string& unzipfolder,
		const std::string& gamefolder, const std::string& tempGamefolder)
	{
		if(!unZip(zipname, unzipfolder))
			return false;
		else 
		if (!findCopyPackFile(unzipfolder.c_str(), gamefolder.c_str(), tempGamefolder.c_str()))
			return false;
		else 
		if (!injectPack(unzipfolder, tempGamefolder, mPackFileMap))
			return false;
		else 
		if (!traverseResAndCopy(tempGamefolder.c_str(),gamefolder.c_str()))
			return false;

		return true;
	}

	bool MGPackUpdateManager::unZip( const std::string& zipname, const std::string& unzipfolder )
	{
		return mPackManager->unZip(zipname, unzipfolder);
	}

	bool MGPackUpdateManager::copyClientRes(LPCSTR filename, LPCSTR gamefolder, LPCSTR tempClienResfolder )
	{
		// 文件名(不含路径), 游戏资源目录, 放拷贝游戏资源的目录
		std::string filenametemp, gamefoldertemp, tempClienResfoldertemp;
		filenametemp = filename;
		gamefoldertemp = gamefolder;
		tempClienResfoldertemp = tempClienResfolder;

		std::replace( filenametemp.begin(), filenametemp.end(), '/', '\\' );
		std::replace( gamefoldertemp.begin(), gamefoldertemp.end(), '/', '\\' );
		std::replace( tempClienResfoldertemp.begin(), tempClienResfoldertemp.end(), '/', '\\' );

		// 路径不存在的话,创建目录(路径后面一定要\\)
		if (!MakeSureDirectoryPathExists(tempClienResfoldertemp.c_str())) 
			return false;

		WIN32_FIND_DATA FileData; 
		HANDLE hSearch;
		DWORD dwAttrs;
		// 放拷贝游戏资源的目录
		char szDirPath[MAX_PATH]; 
		strcpy(szDirPath, tempClienResfoldertemp.c_str());
		StringCchCat(szDirPath, MAX_PATH, filenametemp.c_str());

		// 游戏资源完整文件名(包含路径)
		char FilePathName[1024];
		strcpy(FilePathName, gamefoldertemp.c_str());
		StringCchCat(FilePathName, MAX_PATH, filenametemp.c_str());

		// 游戏资源目录,在目录里查找所有的.cn文件
		char szSearchFilePath[MAX_PATH]; 
		wsprintf(szSearchFilePath, "%s\*.cn", gamefoldertemp.c_str());
		hSearch = FindFirstFile(szSearchFilePath, &FileData); 
		if (INVALID_HANDLE_VALUE == hSearch) 
			return false;

		while (TRUE) 
		{ 
			if (FileData.cFileName[0] != '.')
			{
				char szComparePath[MAX_PATH];
				wsprintf(szComparePath, "%s\%s", gamefoldertemp.c_str(), FileData.cFileName);
				std::string tempS1, tempS2;
				tempS1 = FilePathName;
				tempS2 = szComparePath;
				// 找到跟要拷贝的文件名匹配
				if (tempS1 == tempS2)
				{
					// 拷贝文件
					if (!CopyFile(FilePathName, szDirPath, FALSE))
						return false;
				}
			}

			if (!FindNextFile(hSearch, &FileData)) 
				break;
		} 

		FindClose(hSearch);

		return true;
	}

	bool MGPackUpdateManager::copyinjectResToGame(LPCSTR filename, LPCSTR gamefolder, LPCSTR tempClienResfolder)
	{
		// 文件名(不含路径), 游戏资源目录, 放拷贝游戏资源的目录
		std::string filenametemp, gamefoldertemp, tempClienResfoldertemp;
		filenametemp = filename;
		gamefoldertemp = gamefolder;
		tempClienResfoldertemp = tempClienResfolder;

		std::replace( filenametemp.begin(), filenametemp.end(), '/', '\\' );
		std::replace( gamefoldertemp.begin(), gamefoldertemp.end(), '/', '\\' );
		std::replace( tempClienResfoldertemp.begin(), tempClienResfoldertemp.end(), '/', '\\' );

		WIN32_FIND_DATA FileData; 
		HANDLE hSearch;
		DWORD dwAttrs;
		// 放拷贝游戏资源的目录
		char szDirPath[MAX_PATH]; 
		strcpy(szDirPath, tempClienResfoldertemp.c_str());
		StringCchCat(szDirPath, MAX_PATH, filenametemp.c_str());

		// 游戏资源完整文件名(包含路径)
		char FilePathName[1024];
		strcpy(FilePathName, gamefoldertemp.c_str());
		StringCchCat(FilePathName, MAX_PATH, filenametemp.c_str());

		// 合并后的资源目录,在目录里查找所有的.cn文件
		char szSearchFilePath[MAX_PATH]; 
		wsprintf(szSearchFilePath, "%s*.cn", tempClienResfoldertemp.c_str());
		hSearch = FindFirstFile(szSearchFilePath, &FileData); 
		if (INVALID_HANDLE_VALUE == hSearch) 
			return false;

		while (TRUE) 
		{ 
			if (FileData.cFileName[0] != '.')
			{
				char szComparePath[MAX_PATH];
				wsprintf(szComparePath, "%s%s", gamefoldertemp.c_str(), FileData.cFileName);
				std::string tempS1, tempS2;
				tempS1 = FilePathName;
				tempS2 = szComparePath;
				// 找到跟要拷贝的文件名匹配
				if (tempS1 == tempS2)
				{
					// 拷贝文件
					if (!CopyFile(szDirPath, FilePathName, FALSE))
						return false;
				}
			}

			if (!FindNextFile(hSearch, &FileData)) 
				break;
		} 

		FindClose(hSearch);

		return true;
	}

	bool MGPackUpdateManager::injectPack( const std::string& unzipfolder, const std::string& tempClienResfolder, StringMap &filemap)
	{
		return mPackManager->injectPack(unzipfolder, tempClienResfolder, filemap);
	}

	bool MGPackUpdateManager::traverseResAndCopy(LPCSTR tempGamefolder, LPCSTR gamefolder)
	{
		char tempGamefolderStr[1024], gamefolderStr[1024];
		strcpy(tempGamefolderStr, tempGamefolder);
		strcpy(gamefolderStr, gamefolder);

		StringMap::iterator iter = mPackFileMap.begin();
		for (; iter != mPackFileMap.end(); iter++)
		{
			std::string outbasename, outpathname;

			std::string filename = iter->first;
			MGStrOp::splitFilename(filename, outbasename, outpathname);

			if (strcmp(tempGamefolderStr, "") == 0)
				wsprintf(tempGamefolderStr, "%s\\", iter->second.c_str());
			else
				wsprintf(tempGamefolderStr, "%s\\%s\\", tempGamefolderStr, iter->second.c_str());

			if (strcmp(gamefolderStr, "") == 0)
				wsprintf(gamefolderStr, "%s\\", iter->second.c_str());
			else
				wsprintf(gamefolderStr, "%s\\%s\\", gamefolderStr, iter->second.c_str());

			//wsprintf(tempGamefolderStr, "%s\\%s\\", tempGamefolderStr, iter->second.c_str());
			//wsprintf(gamefolderStr, "%s\\%s\\", gamefolderStr, iter->second.c_str());

			if (!copyinjectResToGame(outbasename.c_str(), gamefolderStr, tempGamefolderStr))
				return false;

			strcpy(tempGamefolderStr, tempGamefolder);
			strcpy(gamefolderStr, gamefolder);
		}
		
		return true;
	}

	bool MGPackUpdateManager::findCopyPackFile(LPCSTR Path, LPCSTR gamefolder, LPCSTR tempGamefolder)
	{
		WIN32_FIND_DATA FindData;
		HANDLE hError;

		// 构造路径
		char FullPathName[1024];

		// 做查询用的
		char FilePathName[1024];
		strcpy(FilePathName, Path);
		strcat(FilePathName, "/*.*");
		
		// 这两个路径做非svn散包文件的拷贝
		char szDirPath[1024], szSrcPath[1024];
		strcpy(szDirPath, tempGamefolder);
		strcpy(szSrcPath, gamefolder);
		
		hError = FindFirstFile(FilePathName, &FindData);
		if (INVALID_HANDLE_VALUE == hError)
		{
			return false;
		}
	
		while(::FindNextFile(hError, &FindData))
		{
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0 )
			{
				continue;
			}

			wsprintf(FullPathName, "%s/%s", Path,FindData.cFileName);

			//如果是目录的话,递归
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (mfindtempPath.empty())
					mfindtempPath = Path;

				findCopyPackFile(FullPathName, gamefolder, tempGamefolder);
			}
			else
			{
				std::string outbasename, outpath, subpath;
				MGStrOp::splitFilename(FilePathName, outbasename, outpath);
				outpath = outpath.substr(0, strlen(outpath.c_str())-1);

				if (mfindtempPath != outpath)
				{
					subpath = outpath.substr(strlen(mfindtempPath.c_str()));
				}

				// 客户端路径和客户端临时目录
				char gamepathtemp[1024], tempgamepathtemp[1024];
				memset(gamepathtemp, 0, sizeof(gamepathtemp));
				memset(tempgamepathtemp, 0, sizeof(tempgamepathtemp));

				if (mfindtempPath != Path)
				{
					if (!mfindtempPath.empty())
					{
						std::string subPathtemp1 = subpath;
						std::string subPathtemp2 = subpath;
							 
						// 当客户端资源跟客户端临时目录的路径为空,则需要去掉subPath路径前的/
						if (strcmp(gamefolder,"") == 0)
						{
							subPathtemp1 = subPathtemp1.substr(1, strlen(subPathtemp1.c_str())-1);
							wsprintf(gamepathtemp, "%s/", subPathtemp1.c_str());
						}
						else
							wsprintf(gamepathtemp, "%s%s/", gamefolder,subPathtemp1.c_str());

						if (strcmp(tempGamefolder,"") == 0)
						{
							subPathtemp2 = subPathtemp2.substr(1, strlen(subPathtemp2.c_str())-1);
							wsprintf(tempgamepathtemp, "%s/", subPathtemp2.c_str());
						}
						else
							wsprintf(tempgamepathtemp, "%s%s/", tempGamefolder,subPathtemp2.c_str());

					}
					else // 新一次的递归
						mfindtempPath = outpath;
				}

				std::string outname, outtype;
				MGStrOp::splitTypename(FindData.cFileName, outname, outtype);
				// 如果是cn类型
				if (outtype == "cn")
				{
					std::string subpathtemp = subpath;
					subpathtemp = subpathtemp.substr(1, strlen(subpathtemp.c_str())-1);

					char tempstr[1024];
					strcpy(tempstr, subpathtemp.c_str());
					strcat(tempstr, "/");
					strcat(tempstr, FindData.cFileName);
					mPackFileMap.insert(std::make_pair(tempstr, subpathtemp));

					if (!copyClientRes(FindData.cFileName, gamepathtemp, tempgamepathtemp))
						return false;
				}
				// 非svn散包文件
				else if(outtype != "svn")
				{
					char unzipPath[1024];
					strcpy(unzipPath, Path);

					wsprintf(unzipPath, "%s/%s", unzipPath, FindData.cFileName);
					wsprintf(gamepathtemp, "%s%s", gamepathtemp, FindData.cFileName);

					// 散包文件直接拷贝
					if (!CopyFile(unzipPath, gamepathtemp, FALSE))
						return false;
				}
			}

		}
		FindClose(hError);

		return true;
	}

	bool MGPackUpdateManager::deleteTempFolder(LPCSTR lpszPath)
	{
		if (!deleteFiles(lpszPath))
			return false;
		else
		if (!RemoveDirectory(lpszPath))
			return false;

		return true;
	}

	bool MGPackUpdateManager::deleteFiles(LPCSTR lpszPath) 
	{ 
		WIN32_FIND_DATA FindData;
		HANDLE hError;
		char FilePathName[1024];
		// 构造路径
		char FullPathName[1024];
		strcpy(FilePathName, lpszPath);
		strcat(FilePathName, "/*.*");

		hError = FindFirstFile(FilePathName, &FindData);
		if (INVALID_HANDLE_VALUE == hError)
		{
			return false;
		}

		while(::FindNextFile(hError, &FindData))
		{
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0 )
			{
					continue;
			}

			wsprintf(FullPathName, "%s/%s", lpszPath,FindData.cFileName);

			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				mDeleteDirectory = FullPathName;
				deleteFiles(FullPathName);
			}
			else
			{
				if (!DeleteFile(FullPathName))
					return false;
			}

		}
		{
			FindClose(hError);
			if (!mDeleteDirectory.empty())
			{
				if (!RemoveDirectory(mDeleteDirectory.c_str()))
					return false;
				else
					mDeleteDirectory.clear();
			}
		}


		return true;
	} 

}