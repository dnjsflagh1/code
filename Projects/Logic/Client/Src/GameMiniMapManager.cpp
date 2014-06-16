/******************************************************************************/
#include "stdafx.h"
#include "GameMiniMapManager.h"
#include "GameRadar.h"
/******************************************************************************/

namespace MG
{
	//-------------------------------------------------------------------------
	GameMiniMapManager::GameMiniMapManager()
	{
		
	}
	//-------------------------------------------------------------------------
	GameMiniMapManager::~GameMiniMapManager()
	{
		uninitilize();
	}
	//-------------------------------------------------------------------------
	GameMiniMap* GameMiniMapManager::getMiniMap(Str name)
	{
		std::map<Str, GameMiniMap*>::iterator iter = mMiniMaps.find(name);
		if ( iter != mMiniMaps.end() )
		{
			return iter->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------
	GameMiniMap* GameMiniMapManager::createOrReteriveMiniMap( Str name, MINIMAP_TYPE miniMapType )
	{
		GameMiniMap* miniMap = getMiniMap(name);
		if ( miniMap )
			return miniMap;
		
		if ( miniMapType == MINIMAP_RADAR )
		{
			miniMap = MG_NEW GameRadar( name );
		}
		
		if ( miniMap )
		{
			miniMap->init();
			mMiniMaps[miniMap->getName()] = miniMap;
		}

		return miniMap;
	}
	//-------------------------------------------------------------------------
	void GameMiniMapManager::destroyMiniMap( Str name )
	{
		std::map<Str, GameMiniMap*>::iterator iter = mMiniMaps.find(name);
		if ( iter != mMiniMaps.end() )
		{
			GameMiniMap* minimap = iter->second;
			minimap->unInit();
			MG_DELETE minimap;

			mMiniMaps.erase( iter );
		}

		return;
	}
	//-------------------------------------------------------------------------
	Bool GameMiniMapManager::initilize()
	{
		return true;
	}	
	//-------------------------------------------------------------------------
	void GameMiniMapManager::uninitilize()
	{
		std::map<Str, GameMiniMap*>::iterator iter = mMiniMaps.begin();
		for ( ; iter != mMiniMaps.end(); iter++)
		{
			GameMiniMap* minimap = iter->second;
			minimap->unInit();
			MG_DELETE minimap;
		}

		mMiniMaps.clear();
	}
	//-------------------------------------------------------------------------
	void GameMiniMapManager::update(Flt delta)
	{
		std::map<Str, GameMiniMap*>::iterator iter = mMiniMaps.begin();
		for ( ; iter != mMiniMaps.end(); )
		{
			GameMiniMap* minimap = iter->second;

			if ( !minimap->isInitialized() )
			{
				minimap->unInit();
				MG_DELETE minimap;
				iter = mMiniMaps.erase( iter );
			}
			else
			{
				minimap->update(delta);
				iter++;
			}
		}
	}
	//-------------------------------------------------------------------------

}
