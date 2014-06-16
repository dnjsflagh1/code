/******************************************************************************/
#include "stdafx.h"
#include <fstream>
#include "AppDataConfig.h"

/******************************************************************************/

namespace SceneEditor {
	AppDataManager* AppDataManager::instance = NULL;

	///---------------------------------------------------
	AppDataManager* AppDataManager::getInstance()
	{
		if (AppDataManager::instance == NULL)
		{
			AppDataManager::instance = new AppDataManager();
		}

		return AppDataManager::instance;
	}

	///---------------------------------------------------
	void AppDataManager::destroyInstance()
	{
		if (instance != NULL)
		{
			delete instance;
			instance = NULL;
		}
	}

	///---------------------------------------------------
	AppDataManager::AppDataManager()
		:mFileName("Config.ini"),mFilePath("")
	{
		mAppData = new AppData();
		mAppData->mapFilePath = "";
		mAppData->enableLightMap = true;
		mAppData->receiveShadow = true;
		mAppData->shadowType = 2;
		mAppData->fogLevel = 3;
	}

	///---------------------------------------------------
	AppDataManager::AppDataManager( const AppDataManager& mgr )
	{
		mAppData = mgr.mAppData;
		mFileName = mgr.mFileName;
		mFilePath = mgr.mFilePath;
	}

	///---------------------------------------------------
	AppDataManager::~AppDataManager()
	{
		delete mAppData;
		mAppData = NULL;
	}

	///---------------------------------------------------
	std::string AppDataManager::getMapFilePath()
	{
		return mAppData->mapFilePath;
	}

	///---------------------------------------------------
	void AppDataManager::setMapFilePath( const std::string path )
	{
		mAppData->mapFilePath = path;
	}

	///---------------------------------------------------
	bool AppDataManager::isLightMapEnbale()
	{
		return mAppData->enableLightMap;
	}

	///---------------------------------------------------
	void AppDataManager::setLightMapEnable( bool enable )
	{
		mAppData->enableLightMap = enable;
	}

	///---------------------------------------------------
	unsigned int AppDataManager::getShadowType()
	{
		return mAppData->shadowType;
	}

	///---------------------------------------------------
	void AppDataManager::setShadowType(unsigned int type)
	{
		mAppData->shadowType = type;
	}


	///---------------------------------------------------
	bool AppDataManager::isReceiveShadow()
	{
		return mAppData->receiveShadow;
	}

	///---------------------------------------------------
	void AppDataManager::setReceiveShadow( bool bReceive )
	{
		mAppData->receiveShadow = bReceive;
	}

	///---------------------------------------------------
	unsigned int AppDataManager::getFogLevel()
	{
		return mAppData->fogLevel;
	}

	///---------------------------------------------------
	void AppDataManager::setFogLevel( unsigned int level )
	{
		mAppData->fogLevel = level;
	}

	///---------------------------------------------------
	void AppDataManager::saveToFile( const std::string fileName, const std::string path )
	{
		std::fstream stream;
		std::string fullName = path+"\\"+fileName;
		stream.open(fullName.c_str(),std::ios_base::out|std::ios_base::trunc);
		if (stream.is_open())
		{
			stream<<mAppData->mapFilePath<<std::endl;
			stream<<mAppData->enableLightMap<<std::endl;
			stream<<mAppData->receiveShadow<<std::endl;
			stream<<mAppData->shadowType<<std::endl;
			stream<<mAppData->fogLevel<<std::endl;

			mFilePath = path;
			mFileName = fileName;
		}
		stream.close();
	}

	///---------------------------------------------------
	void AppDataManager::loadFromFile( const std::string fileName, const std::string path )
	{
		std::fstream stream;
		std::string fullName = path+"\\"+fileName;
		stream.open(fullName.c_str(),std::ios_base::in);
		if (stream.is_open())
		{
			//stream>>mAppData->mapFilePath>>mAppData->receiveShadow>>mAppData->fogLevel;
			std::string str1,str2,str3,str4,str5;
			std::getline(stream,str1,'\n');
			std::getline(stream,str2,'\n');
			std::getline(stream,str3,'\n');
			std::getline(stream,str4,'\n');
			std::getline(stream,str5,'\n');
			mAppData->mapFilePath   = str1;
			mAppData->enableLightMap = (bool)atoi(str2.c_str());
			mAppData->receiveShadow = (bool)atoi(str3.c_str());
			mAppData->shadowType    = (unsigned int)atoi(str4.c_str());
			mAppData->fogLevel      = (unsigned int)atoi(str5.c_str());

			mFilePath = path;
			mFileName = fileName;
		}
		stream.close();
	}

	///---------------------------------------------------
	AppDataManager& AppDataManager::operator=( const AppDataManager& mgr )
	{
		mAppData = mgr.mAppData;
		mFileName = mgr.mFileName;
		mFilePath = mgr.mFilePath;

		return *this;
	}
}