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
	//��ϷС��ͼ
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

		//��ȡС��ͼ������
		Str					getName() { return mapName; }
		//��ȡС��ͼ�����سߴ�
		VecI2				getMiniMapSize() { return mMiniMapSize; }
		//���С��ͼ��ʾ�ĵ�ͼ��Χ
		Vec2				getVisibleWorldSize() { return mVisibleWorldSize; }
		//�Ƿ��Ѿ���ʼ��
		Bool				isInitialized() { return mInitialized; }
		//�Ƿ��ͼ�Ѿ�����
		Bool				isMapLoaded() { return mMapLoaded; }
		//���������
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
	//��ϷС��ͼ������
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
		//��������
		////////////////////////////////////////////////////////////////////
		Bool			initilize();

		void			update(Flt delta);

		void			uninitilize();

		////////////////////////////////////////////////////////////////////
		//�����ͻ�ȡ
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