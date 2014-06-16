//*************************************************************************************************//
#include "stdafx.h"
#include "PrintWindowsCfg.h"
#include "Ini.h"
//*************************************************************************************************//
namespace MG
{
	PrintWindowsCfg::PrintWindowsCfg()
	{
	}

	//--------------------------------------------------------------------------
	PrintWindowsCfg::~PrintWindowsCfg()
	{
	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool PrintWindowsCfg::loadFile( std::wstring fileName, IMGExternalPackManager* packManager/* = NULL*/ )
	{
		assert(fileName.length() > 4);

		//读取Ini文件
		UINI ini;
		// MG_CN_MODIFY
		if ( ini.create( fileName, packManager ) )
		{
			//根据Index取出ini内容

			PrintWindowsCfgInfo newInfo;

			if (false == ini.hasGroup(L"PrintWindow"))
			{
				DYNAMIC_ASSERT(0);
				return false;
			}

			ini.setGroup(L"PrintWindow");
			
			MGStrOp::toI32( ini.getValue(L"printMap", L"0" ).c_str()			, newInfo.printMap);
			MGStrOp::toI32( ini.getValue(L"printPlayer", L"0" ).c_str()			, newInfo.printPlayer);
			MGStrOp::toI32( ini.getValue(L"printPlayerCharacter", L"0" ).c_str(), newInfo.printPlayerCharacter);

			DYNAMIC_ASSERT((newInfo.printMap == 0 || newInfo.printMap == 1) && 
							(newInfo.printPlayer == 0 || newInfo.printPlayer == 1) && 
							(newInfo.printPlayerCharacter == 0 || newInfo.printPlayerCharacter == 1) );

			//存贮ini文件信息。
			mPrintWindowConfigList.push_back( newInfo );

			return true;
		}
		return false;
	}


	//--------------------------------------------------------------------------
	PrintWindowsCfgInfo* PrintWindowsCfg::getConfig()
	{
		return &(mPrintWindowConfigList.at(0));
	}

	Int PrintWindowsCfg::getPrintMap()
	{
		return getConfig()->printMap;
	}

	Int PrintWindowsCfg::getPrintPlayer()
	{
		return getConfig()->printPlayer;
	}

	Int PrintWindowsCfg::getPrintPlayerCharacter()
	{
		return getConfig()->printPlayerCharacter;
	}
	//--------------------------------------------------------------------------
}