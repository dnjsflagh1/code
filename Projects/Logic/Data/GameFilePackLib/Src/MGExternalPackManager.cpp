#include "stdafx.h"
#include "GameFilePackManager.h"
#include "MGExternalPackManager.h"

namespace MG
{
	MGExternalPackManager::MGExternalPackManager( GameFilePackManager* packManager )
		:mPackManager(packManager)
	{

	}

	MGExternalPackManager::~MGExternalPackManager()
	{

	}

	bool MGExternalPackManager::extractPackFile( const std::string& pathfilename, MG::MGExtractedPackFile& file )
	{
		return mPackManager->extractPackFile(pathfilename, file);
	}

	bool MGExternalPackManager::extractPackFile( const std::string& pathfilename, char*& buf, int& size )
	{
		return mPackManager->extractPackFile(pathfilename, buf, size);
	}

	bool MGExternalPackManager::extractPackFile( const std::string& pathfilename, wchar_t*& buf )
	{
		return mPackManager->extractPackFile(pathfilename, buf);
	}

	bool MGExternalPackManager::isPackResEmpty()
	{
		return mPackManager->isPackResEmpty();
	}

}