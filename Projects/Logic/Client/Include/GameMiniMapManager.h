#ifndef _GAME_MINIMAP_MANAGER_H
#define _GAME_MINIMAP_MANAGER_H
/******************************************************************************/
#include "ClientPreqs.h"
#include "IEngineMain.h"
/******************************************************************************/
namespace MG
{
	class GameMiniMap;
	class GameMiniMapListener
	{
	public:
		virtual void onMiniMapUnLoad(GameMiniMap* miniMap){}
		virtual void onMiniMapLoaded(GameMiniMap* miniMap){}
	};
	/******************************************************************************/
	//游戏小地图
	/******************************************************************************/

	class GameMiniMap
	{

	public:

		explicit GameMiniMap( Str name)
			:mapName( name )
			,mMiniMapSize( VecI2(0,0) )
			,mVisibleWorldSize( Vec2(0,0))
			,mInitialized(false)
			,mMapLoaded(false)
			,mListener(NULL)
		{ 
			mapGroup = "GameMiniMap";
		}

		//获取小地图的名称
		Str					getName() { return mapName; }
		//获取小地图的像素尺寸
		VecI2				getMiniMapSize() { return mMiniMapSize; }
		//获得小地图显示的地图范围
		Vec2				getVisibleWorldSize() { return mVisibleWorldSize; }
		//是否已经初始化
		Bool				isInitialized() { return mInitialized; }
		//是否地图已经加载
		Bool				isMapLoaded() { return mMapLoaded; }
		//加入监听器
		void				setListener( GameMiniMapListener* listener) { mListener = listener; };

		/////////////////////////////////////////////////////////////////////////////////////

		virtual Bool		init() = 0;

		virtual void		unInit() = 0;

		virtual Bool		loadMap( Str name, Str path, Vec2 visibleWorldSize, Vec2 worldCenter ) = 0;

		virtual void		unloadMap() = 0;

		virtual void		update(Flt delta) = 0;

		/////////////////////////////////////////////////////////////////////////////////////

	protected:

		VecI2					mMiniMapSize;

		Vec2					mVisibleWorldSize;
		Vec2					mVisibleWorldCenter;

		Str						mapName;
		Str						mapGroup;

		Bool					mInitialized;
		Bool					mMapLoaded;

		GameMiniMapListener*	mListener;
	};
	/******************************************************************************/
	//游戏小地图管理器
	/******************************************************************************/
	class GameMiniMapManager
	{
	public:

		enum MINIMAP_TYPE
		{
			MINIMAP_RADAR = 1,
		};

	public:

		GameMiniMapManager();
		~GameMiniMapManager();
		SINGLETON_INSTANCE(GameMiniMapManager)

	public:

		////////////////////////////////////////////////////////////////////
		//基本方法
		////////////////////////////////////////////////////////////////////
		Bool			initilize();

		void			update(Flt delta);

		void			uninitilize();

		////////////////////////////////////////////////////////////////////
		//创建和获取
		////////////////////////////////////////////////////////////////////
		GameMiniMap*	createOrReteriveMiniMap( Str name, MINIMAP_TYPE miniMapType );

		void			destroyMiniMap( Str name );

		GameMiniMap*	getMiniMap(Str name);
		////////////////////////////////////////////////////////////////////

	private:

		std::map<Str, GameMiniMap*> mMiniMaps;
	};
}

/******************************************************************************/
#endif