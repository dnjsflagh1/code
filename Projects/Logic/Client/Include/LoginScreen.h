/******************************************************************************/
#ifndef _LOGINSCREEN_H_
#define _LOGINSCREEN_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "GameSettingManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // 游戏登入相关功能
    /******************************************************************************/
    class LoginScreen : public IScreen, public IAnimationControllerListener, public ResourceLoadListener, public GameSettingManagerListener
    {
    public:

        SINGLETON_INSTANCE(LoginScreen)
        LoginScreen();
        virtual ~LoginScreen();

        virtual void		update( Flt delta );
        virtual bool		isFinished();
        virtual void		onEnter();
        virtual void		onLeave();

		///////////////////////////////////////////////////////////////

		// 【事件】

	public:
		
		// 场景逻辑对象事件

        virtual void		onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void		onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void		onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );

		// 资源读取相关的事件

		virtual void		onInitResourceLoadListener();
		virtual void		onClearResourceLoadListener();

		virtual void		preLoadTerrainChunk( UInt index, UInt total );
		virtual void		postLoadTerrainChunk( UInt index, UInt total );

		virtual void		preloadObject( UInt index, UInt total );
		virtual void		postloadObject( ISceneObject* entity, UInt index, UInt total );

		virtual void		preloadCustomObject( UInt index, UInt total );
		virtual void		postloadCustomObject( ISceneObject* entity, UInt index, UInt total );

		// 游戏配置相关的事件
		virtual void		onApplyDisplayConfig();

	protected:

		Flt					mCustomObjectProgress;
		
	protected:

		// 动画的事件

		virtual void		onAnimationStop(CChar* animName);

		//////////////////////////////////////////////////////////////////////////////

	public:


		//【引擎实体管理】

		// entity index
		enum
		{
			FOCUS_ENTITY_SEIRYU = 0,
			FOCUS_ENTITY_BIAKKO,
			FOCUS_ENTITY_SUSAKU,
			FOCUS_ENTITY_KENBU,
			FOCUS_ENTITY_MAX
		};

		enum
		{
			//create Clan 

			ENTITY_SCENE_CENTER = 0,

			ENTITY_SUSAKU,
			ENTITY_BIAKKO,
			ENTITY_KENBU,
			ENTITY_SEIRYU,

			ENTITY_SUSAKU_FRONT,
			ENTITY_BIAKKO_FRONT,
			ENTITY_KENBU_FRONT,
			ENTITY_SEIRYU_FRONT,

			ENTITY_SUSAKU_BACK,
			ENTITY_BIAKKO_BACK,
			ENTITY_KENBU_BACK,
			ENTITY_SEIRYU_BACK,

			ENTITY_SKYDOM_1,
			ENTITY_SKYDOM_2,
			ENTITY_SKYDOM_3,

			//create\select general 

			ENTITY_CAMERA_1,
			ENTITY_CAMERA_2,
			ENTITY_CAMERA_TARGET_1,
			ENTITY_CAMERA_TARGET_2,

			ENTITY_HALL_PART_1,
			ENTITY_HALL_PART_2,

			ENTITY_CRECHAR_SEAT_POINT,

			ENTITY_CRECHAR_STAND_POINT_1,
			ENTITY_CRECHAR_STAND_POINT_2,
			ENTITY_CRECHAR_STAND_POINT_3,
			ENTITY_CRECHAR_STAND_POINT_4,
			ENTITY_CRECHAR_STAND_POINT_5,
			ENTITY_CRECHAR_STAND_POINT_6,
			ENTITY_CRECHAR_STAND_POINT_7,
			ENTITY_CRECHAR_STAND_POINT_8,

			ENTITY_CRECHAR_STAND_ROW_1,
			ENTITY_CRECHAR_STAND_ROW_2,
			ENTITY_CRECHAR_STAND_ROW_3,
			ENTITY_CRECHAR_STAND_ROW_4,

			ENTITY_SELCHAR_SEAT_POINT,
			ENTITY_SELCHAR_SEAT_POINT_LEFT,
			ENTITY_SELCHAR_SEAT_POINT_RIGHT,

			ENTITY_SELCHAR_STAND_POINT_1,
			ENTITY_SELCHAR_STAND_POINT_2,
			ENTITY_SELCHAR_STAND_POINT_3,
			ENTITY_SELCHAR_STAND_POINT_4,
			ENTITY_SELCHAR_STAND_POINT_5,
			ENTITY_SELCHAR_STAND_POINT_6,
			ENTITY_SELCHAR_STAND_POINT_7,
			ENTITY_SELCHAR_STAND_POINT_8,

			ENTITY_SLOT_MAX,
			
		};

		// 获得实体
		IEntity*			getEntity( Int index );
		// 获得实体
		IEntity*			getEntity( Str8 name );
		// 设置场景物件不可见
		void				setAllEntitysVisible( Bool isVisible );

	private:

		//对象名称列表
		std::vector<Str>	mEntityList;
		
		///////////////////////////////////////////////////////////////

	public:

		//【逻辑管理】

		// 获取创建武将的索引	
		I32					getTempCharIndex(CCharacterSceneEntity* characterSceneEntity);

		// 获取创建好的武将
		I32					getSelectCharIndex() { return mSelectedGeneralIndex; }

		// 准备进入游戏状态
		void				prepareJoiningGame();

		// 准备选中
		void				prepareSelectGeneral(CCharacterSceneEntity* characterSceneEntity);

		// 准备创建角色
		void				prepareCreateGeneral();

		// 选中角色
		void				selectGeneral(CCharacterSceneEntity* characterSceneEntity);

		// 通过索引，随机选择一个武将
		void				randomGeneralbyId(U32 randomId);

		// 选中角色， 暂时不使用该函数
		void				selectGeneral2(CCharacterSceneEntity* characterSceneEntity);

	protected:

		//创建模版角色武将的索引列表
		std::map<I32, CPlayerCharacterEntity*>	mTempCharEntityList;

		//选中的
		I32					mSelectedGeneralIndex;

	public:

		void				clearEnterGameDirty() { mSceneFinishDirty = false;}

		Bool				getEnterGameDirty() { return mSceneFinishDirty; }					

	protected:

		Bool				mSceneFinishDirty;

		///////////////////////////////////////////////////////////////

    public:

		//【场景管理】

		// 加载选择氏族的场景
		Bool				loadCreateClanScene();
		// 销毁选择氏族的场景
		void				destroyCreateClanScene();

		// 加载选择武将的场景
		Bool				loadSelectGeneralScene();
		// 销毁武将选择的场景
		void				destroySelectGeneralScene();

		// 加载创建武将的场景
		Bool				loadCreateGeneralScene();
		// 销毁创建武将的场景
		void				destroyCreateGeneralScene();

	private:

		// 场景开始读取回调
		void				beginLoadScene(CChar* newPath, I32 ctrlType);
		// 场景读取
		void				loadScene(CChar* mapName, I32 ctrlType);
		// 场景读取结束回调
		void				endLoadScene(CChar* newPath, I32 ctrlType);

	private:

		// 重置绘制状态
		void				initManualRenderState(I32 ctrlType);

    protected:

        static Str			STATE_NAME;
		

    };

}

/******************************************************************************/

#endif

