#include "stdafx.h"
#include "GameFilePackManager.h"
#include "ExternalSTPackManager.h"

namespace MG
{
	ExternalSTPackManager::ExternalSTPackManager( GameFilePackManager* packManager )
		:mPackManager(packManager)
	{

	}

	ExternalSTPackManager::~ExternalSTPackManager()
	{

	}

	bool ExternalSTPackManager::extractPackFile( const char* pathfilename, char*& buf, int& size )
	{
		return mPackManager->extractPackFile(pathfilename, buf, size);
	}

	bool ExternalSTPackManager::extractPackFile( const char* pathfilename, wchar_t*& buf)
	{
		return mPackManager->extractPackFile(pathfilename, buf);
	}

}