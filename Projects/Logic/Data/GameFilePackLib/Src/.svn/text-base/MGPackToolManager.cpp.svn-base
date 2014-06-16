#include "stdafx.h"
#include "GameFilePackManager.h"
#include "MGPackToolManager.h"
#include "MGMd5.h"
#include "imagehlp.h"

const static char RES_PACK_PASSWORD[32] = "aosheng!yingxiongzhi@mg#cn$8858";
namespace MG
{
	MGPackToolManager::MGPackToolManager()
	{
		mPackManager = new MGPackManager();
	}

	MGPackToolManager::~MGPackToolManager()
	{
		delete mPackManager;
	}

	bool MGPackToolManager::packGameRes(const std::string& src, const std::string& des)
	{
		return mPackManager->packRes(src, des, RES_PACK_PASSWORD);
	}

	void MGPackToolManager::loadNewResFolder( LPCSTR newResPath )
	{
		if (mNewResPath.empty())
			mNewResPath = newResPath;

		WIN32_FIND_DATA FindData;
		HANDLE hError;
		int FileCount = 0;
		char FilePathName[1024];
		// 构造路径
		char FullPathName[1024];
		strcpy(FilePathName, newResPath);
		strcat(FilePathName, "/*.*");

		hError = FindFirstFile(FilePathName, &FindData);
		if (INVALID_HANDLE_VALUE == hError)
		{
			return;
		}

		while(::FindNextFile(hError, &FindData))
		{
			if (strcmp(FindData.cFileName, ".") == 0
				|| strcmp(FindData.cFileName, "..") == 0 )
			{
				continue;
			}

			wsprintf(FullPathName, "%s/%s", newResPath,FindData.cFileName);

			std::string fullpathtemp = FullPathName;
			std::string subpath;
			subpath = fullpathtemp.substr(strlen(mNewResPath.c_str())+1, strlen(fullpathtemp.c_str()));
			//如果是目录的话,递归
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				int count = fullpathtemp.find_last_of("/");
				if (count != std::string::npos)
				{
					std::string typestr = fullpathtemp.substr(count+1, strlen(fullpathtemp.c_str()));
					if (typestr == ".svn")
					{
						continue;
					}
				}

				loadNewResFolder(FullPathName);
			}
			else
				mNewResFileList.push_back(subpath);

		}
		FindClose(hError);
	}

	bool MGPackToolManager::compareAndCopy(LPCSTR lastResPath, LPCSTR newResPath, LPCSTR packFolder)
	{
		char lastResPathTemp[1024], newResPathTemp[1024],packcopyFolder[1024];

		std::list<std::string>::iterator iter = mNewResFileList.begin();
		for (; iter != mNewResFileList.end(); iter++)
		{
			strcpy(lastResPathTemp, lastResPath);
			strcpy(newResPathTemp, newResPath);
			strcpy(packcopyFolder, packFolder);

			std::string fileStrtemp = (*iter).c_str();
			std::replace( fileStrtemp.begin(), fileStrtemp.end(), '/', '\\' );

			wsprintf(lastResPathTemp, "%s\\%s", lastResPathTemp, fileStrtemp.c_str());

			wsprintf(newResPathTemp, "%s\\%s", newResPathTemp, fileStrtemp.c_str());
			wsprintf(packcopyFolder, "%s\\%s", packcopyFolder, fileStrtemp.c_str());

			std::string filename,pathname;
			MGStrOp::splitFilename(packcopyFolder, filename, pathname);
			MGStrOp::str_replace(pathname, "/", "\\\\");
			if (!MakeSureDirectoryPathExists(pathname.c_str())) 
				return false;

			FILE *file = fopen(lastResPathTemp, "r");
			if (!file)
			{
				// 直接拷贝
				if (!CopyFile(newResPathTemp, packcopyFolder, FALSE))
				{
					int a = GetLastError();
					return false;
				}
			}
			else
			{
				FILE *filetemp1, *filetemp2;
				filetemp1 = fopen(lastResPathTemp, "r");
				filetemp2 = fopen(newResPathTemp, "r");
				// 对比MD5码
				if (!compareMD5(filetemp1, filetemp2))
				{
					if (!CopyFile(newResPathTemp, packcopyFolder, FALSE))
							return false;
				}
			}
		}
		return true;
	}

	bool MGPackToolManager::compareMD5(FILE* lastResFile,FILE* newResFile )
	{
		std::string lastfileMD5, newfileMD5;
		lastfileMD5 = MGMd5::md5FileStr(lastResFile);
		newfileMD5 = MGMd5::md5FileStr(newResFile);
		
		return (lastfileMD5 != newfileMD5)? false : true;
	}

}