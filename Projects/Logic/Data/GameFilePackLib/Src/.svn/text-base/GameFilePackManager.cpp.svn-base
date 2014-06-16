//*************************************************************************************************//

#include "stdafx.h"
#include "GameFilePackManager.h"
#include "ZipArchive.h"

const static char RES_PACK_PASSWORD[32] = "aosheng!yingxiongzhi@mg#cn$8858";
//*************************************************************************************************//
namespace MG
{
    //-----------------------------------------------------------------------------
    GameFilePackManager::GameFilePackManager()
    {
		mPackManager = new MGPackManager();
    }

    //-----------------------------------------------------------------------------
    GameFilePackManager::~GameFilePackManager()
    {
		delete mPackManager;
    }

	void GameFilePackManager::load()
	{
		findAndLoadPackFile("Config", "*.cn");
		findAndLoadPackFile("Media", "*.cn");
	}

	void GameFilePackManager::unload()
	{
		unloadAllPackFile();

		ResClassifyPathMap::iterator iter = mClassifyPathMap.begin();
		for (; iter != mClassifyPathMap.end(); iter++)
		{
			if (iter->second)
				delete iter->second;
		}

		ResClassifyPathTypeMap::iterator itertype = mClassifyPathTypeMap.begin();
		for(; itertype != mClassifyPathTypeMap.end(); itertype++)
		{
			if (itertype->second)
				delete itertype->second;
		}

		if (mPackManager)
			delete mPackManager;
	}

	MG::Bool GameFilePackManager::extractPackFile( const std::string& pathfilename, MGExtractedPackFile& file )
	{
		std::string filenametemp = pathfilename;
		MGStrOp::str_replace(filenametemp, "\\\\", "\\");
		MGStrOp::str_replace(filenametemp, "//", "/");
		std::replace( filenametemp.begin(), filenametemp.end(), '\\', '/' );

		IMGPackFileSet *packfileset = getPackFileSetFromPath(filenametemp);
		if (packfileset)
		{
			return packfileset->extractPackFile(filenametemp, file);
		}
		else
			return false;
	}

	MG::Bool GameFilePackManager::extractPackFile( const std::string& pathfilename, char*& buf, Int& size )
	{
		std::string filenametemp = pathfilename;
		MGStrOp::str_replace(filenametemp, "\\\\", "\\");
		MGStrOp::str_replace(filenametemp, "//", "/");
		std::replace( filenametemp.begin(), filenametemp.end(), '\\', '/' );

		IMGPackFileSet *packfileset = getPackFileSetFromPath(filenametemp);
		if (packfileset)
		{
			return packfileset->extractPackFile(filenametemp, buf, size);
		}
		else
			return false;
	}

	MG::Bool GameFilePackManager::extractPackFile( const std::string& pathfilename, wchar_t*& buf )
	{
		std::string filenametemp = pathfilename;
		MGStrOp::str_replace(filenametemp, "\\\\", "\\");
		MGStrOp::str_replace(filenametemp, "//", "/");
		std::replace( filenametemp.begin(), filenametemp.end(), '\\', '/' );

		IMGPackFileSet *packfileset = getPackFileSetFromPath(filenametemp);
		if (packfileset)
		{
			return packfileset->extractPackFile(filenametemp, buf);
		}
		else
			return false;
	}

	bool GameFilePackManager::isFileExist( const std::string& filename )
	{
		std::string filenametemp = filename;
		MGStrOp::str_replace(filenametemp, "\\\\", "\\");
		MGStrOp::str_replace(filenametemp, "//", "/");
		std::replace( filenametemp.begin(), filenametemp.end(), '\\', '/' );

		IMGPackFileSet *packfileset = getPackFileSetFromPath(filenametemp);
		if (packfileset)
		{	
			return packfileset->isFileExist(filenametemp);
		}	
		else
			return false;
	}

	MG::StringMap GameFilePackManager::findZip( const std::string& path, const std::string& pattern )
	{
		StringMap ret;
		std::string pathcopy = path;
		std::replace( pathcopy.begin(), pathcopy.end(), '\\', '/' );
		MGStrOp::str_replace(pathcopy, "\\", "/");
		MGStrOp::str_replace(pathcopy, "//", "/");

		MGStrOp::makeLower(pathcopy);

		if (pathcopy.find_last_of('/') == pathcopy.size() - 1)
			pathcopy = pathcopy.substr(0, pathcopy.size() - 1);

		std::string pathnametofind = pathcopy;
		MGStrOp::makeLower(pathnametofind);

		ResClassifyPathMap::iterator filemapIter;
		filemapIter = mClassifyPathMap.begin();
		for (; filemapIter != mClassifyPathMap.end(); filemapIter++)
		{
			ClassifyPathMap* filepathMap = filemapIter->second;
			if (filepathMap)
			{
				ClassifyPathMap::iterator filepathIter = filepathMap->find(pathnametofind);

				if (filepathIter != filepathMap->end())
				{
					FileInfoVec fileVec = filepathIter->second;
					FileInfoVec::iterator iter = fileVec.begin();
					for (; iter != fileVec.end(); iter++)
						ret.insert(std::make_pair((*iter).basename, ""));
				}

			}
		}

		return ret;
	}

	MG::FileInfoVec GameFilePackManager::findZipFileInfo( const std::string& path, const std::string& pattern )
	{
		FileInfoVec returnvec;

		std::string name, type;
		MGStrOp::splitTypename(pattern, name, type);

		bool patternIsFile = false;
		std::string pat;
		if (strcmp(name.c_str(), "*") != 0)
		{
			pat = pattern;
			patternIsFile = true;
		}
		else
		{
			patternIsFile = false;
			int pos =  pattern.find(".", 0);
			if (pos != std::string.npos)
			{
				pat = pattern.substr(pos+1, pattern.size()-pos+1);
			}
			else
				pat = pattern;

			if (pat == "cgfx")
				pat = "cg";
		}
		MGStrOp::makeLower(pat);

		std::string pathcopy = path;
		std::replace( pathcopy.begin(), pathcopy.end(), '\\', '/' );
		MGStrOp::str_replace(pathcopy, "\\", "/");
		MGStrOp::str_replace(pathcopy, "//", "/");

		MGStrOp::makeLower(pathcopy);

		ResClassifyPathTypeMap::iterator filemapIter;
		filemapIter = mClassifyPathTypeMap.begin();
		// 遍历资源包
		for (; filemapIter != mClassifyPathTypeMap.end(); filemapIter++)
		{
			ClassifyPathTypeMap *filepathMap = filemapIter->second;
			// 找路径
			ClassifyPathTypeMap::iterator filepathIter = filepathMap->find(pathcopy);
			if (filepathIter != filepathMap->end())
			{
				ClassifyPathMulMap filemap = filepathIter->second;
				ClassifyPathMulMap::iterator iter = filemap.begin();
				for (; iter != filemap.end(); iter++)
				{
					if (!patternIsFile)
					{
						std::string filetype = (*iter).first;
						MGStrOp::makeLower(filetype);
						if (pat == filetype)
							returnvec.push_back(iter->second);
					}
					else
					{
						std::string filename = iter->second.basename;
						MGStrOp::makeLower(filename);
						if (pat == filename)
							returnvec.push_back(iter->second);
					}
				}
			}	
		}
		return returnvec;
	}

	bool GameFilePackManager::isPackResEmpty()
	{
		if (mPathPackType.size() == 0)
			return true;
		else
			return false;
	}

	std::string GameFilePackManager::getWholeFilePath( const std::string& fileName, const std::string& type )
	{
		if (mPackSet[type])
		{
			StringMap filePathMap = mPackSet[type]->getFilePathMap();
			StringMap::iterator iter = filePathMap.find(fileName);
			if (iter != filePathMap.end())
				return iter->second;
			else
				return "";
		}
		else
			return "";
	}

	void GameFilePackManager::findAndLoadPackFile( LPCSTR Path, LPCSTR filter)
	{
		WIN32_FIND_DATA FindData;
		HANDLE hError;
		int FileCount = 0;
		char FilePathName[1024];
		// 构造路径
		char FullPathName[1024];
		strcpy(FilePathName, Path);
		wsprintf(FilePathName, "%s/%s", FilePathName, filter);
		hError = FindFirstFile(FilePathName, &FindData);
		if (INVALID_HANDLE_VALUE == hError)
		{
			return;
		}
		while(TRUE)
		{
			if (FindData.cFileName[0] != '.')
			{
				wsprintf(FullPathName, "%s/%s", Path,FindData.cFileName);
				loadPackFile(FullPathName, RES_PACK_PASSWORD);
			}
			if(!FindNextFile(hError,&FindData)) break;
		}
		FindClose(hError);
	}

	void GameFilePackManager::loadPackFile( const std::string& filename, const char* password )
	{
		// 解析出资源类型
		std::string filepath, restype;
		std::string filenametemp = filename;
		MGStrOp::splitFilename(filenametemp, restype, filepath);

		std::string packName, packtypetemp;
		MGStrOp::splitTypename(filenametemp, restype, packtypetemp);

		ClassifyPathMap *pathMap = new ClassifyPathMap();
		ClassifyPathTypeMap *pathfiletypeMap = new ClassifyPathTypeMap();
		MGStrOp::makeLower(restype);
		if (!mPackSet[restype])
		{
			IMGPackFileSet* packfileset = mPackManager->loadPackFileSet(filename, password);
			mPackSet[restype] = packfileset;

			pathMap = packfileset->getPathFileInfoMap();
			mClassifyPathMap[restype] = pathMap;

			pathfiletypeMap = packfileset->getPathFileInfoTypeMap();
			mClassifyPathTypeMap[restype] = pathfiletypeMap;

			StringMap packTypeMapTemp = packfileset->getPathPackTypeMap();
			StringMap::iterator iter = packTypeMapTemp.begin();
			for (; iter != packTypeMapTemp.end(); iter++)
			{
				std::string pathlower = iter->first;
				MGStrOp::makeLower(pathlower);
				mPathPackType.insert(std::make_pair(pathlower, iter->second));
			}
 
		}
	}

	void GameFilePackManager::unloadAllPackFile()
	{
		ZIP_ARC_MAP_ITER packiter = mPackSet.begin();
		for (; packiter != mPackSet.end(); packiter++)
		{
			mPackManager->unloadPackFileSet(packiter->second);
		}
	}

	IMGPackFileSet* GameFilePackManager::getPackFileSetFromPath( const std::string& filePath )
	{
		std::string pathtemp = filePath;

		std::string packtype;
		// 解析出路径出来再查找,路径末尾不要去掉/
		std::string filenametemp, filepathtemp;
		MGStrOp::splitFilename(pathtemp, filenametemp, filepathtemp);

		MGStrOp::makeLower(filepathtemp);
		StringMap::iterator iter = mPathPackType.find(filepathtemp);
		if (iter != mPathPackType.end())
		{
			packtype = iter->second;
			return mPackSet[packtype];
		}
		else
			return NULL;

	}

	IMGPackFileSet* GameFilePackManager::getPackFileSetFromType( const std::string& type )
	{
		return mPackSet[type];
	}

}

//*************************************************************************************************//