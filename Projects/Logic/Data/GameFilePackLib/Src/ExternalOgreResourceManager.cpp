#include "stdafx.h"
#include "GameFilePackManager.h"
#include "ExternalOgreResourceManager.h"

namespace MG
{
	ExOgreResourceManager::ExOgreResourceManager( GameFilePackManager* packManager )
		:mPackManager(packManager)
	{

	}

	ExOgreResourceManager::~ExOgreResourceManager()
	{

	}

	std::string ExOgreResourceManager::getWholeFilePath( const std::string& fileName, const std::string& type )
	{
		return mPackManager->getWholeFilePath(fileName, type);
	}

	bool ExOgreResourceManager::isFileExist( const std::string& filename )
	{
		return mPackManager->isFileExist(filename);
	}

	bool ExOgreResourceManager::extractPackFile( const std::string& pathfilename, MGExtractedPackFile& file )
	{
		return mPackManager->extractPackFile(pathfilename, file);
	}

	StringMap ExOgreResourceManager::findZip( const std::string& path, const std::string& pattern )
	{
		return mPackManager->findZip(path, pattern);
	}

	FileInfoVec ExOgreResourceManager::findZipFileInfo( const std::string& path, const std::string& pattern )
	{
		return mPackManager->findZipFileInfo(path, pattern);
	}

	bool ExOgreResourceManager::isPackResEmpty()
	{
		return mPackManager->isPackResEmpty();
	}

}
