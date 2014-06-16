/******************************************************************************/
#ifndef _CSCENEMANAGER_H_
#define _CSCENEMANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#define  ATTACKFORCEMAXNUM 5
#define  DEFENSEFORCEMAXNUM 5
#include "MapListCsv.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//管理整个3d场景中游戏场景逻辑相关的显示对象
	/******************************************************************************/
	class CSceneManager
	{

		friend class GameRadar;
		friend class GameObjectOpCtrl;

	public:

		CSceneManager();
		virtual ~CSceneManager();
		SINGLETON_INSTANCE(CSceneManager)

    public:

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [主要方法]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

		// 游戏场景更新
		void                                update( Flt delta );
        // 得到引擎场景对象
        IScene*                             getEngineScene();
        // 得到技能特效系统
        CSkillEffectSystem*                 getSkillEffectSystem();
        
    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [场景加载和释放]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

		// 场景的加载
		Bool                                loadRegionScene(RegionIdType regionId, REGION_OBJ_TYPE regionObjType);
		Bool                                loadRegionScene(const Str& baseFilePath, const Str& filepath);
		// 销毁据点场景
		void                                destroyRegionScene();
		// 销毁场景信息
		void								destroyRegionInfo() { mCurrRegion = NULL; }
        // 是否据点场景有效
        Bool                                isRegionSceneLoaded();
		// 设置是否场景有效
		void								setRegionSceneLoaded(Bool isLoadScene);
        // 得到据点编号
        IdType                              getRegionId();

		CRegionObject*						getCurrRegion();
		// 得到地图类型
		REGION_OBJ_TYPE                     getRegionObjType();
        // 得到地图类型
        MapType                             getMapType();

        // 更新加载场景
        void                                updateLoadScene();
        // 当开始加载场景
        void                                onLoadSceneStart();
        // 当结束加载场景
        void                                onLoadSceneEnd();
        // 设置结束加载场景标志位
        void                                setLoadSceneEndDirty();
		// 设置结束加载场景标志位
		Bool                                isLoadingScene();

		// 设置和得到是否支持动态寻路
		void								setDynamicPathFindEnable( Bool enable );
		Bool								getDynamicPathFindEnable();

		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [场景元素加载和释放]
		//×××××××××××××××××××××××××××××××××××××××××××××××××

        //--------------------------------------------------------------------------------------------------------------

        // 得到场景实体对象
        CSceneEntity*                       getSceneEntity(IdType id, GAMEOBJ_TYPE type);
        CCharacterSceneEntity*              getCharacterSceneEntity( GAMEOBJ_TYPE type, IdType id, UInt index = 0 );

        //--------------------------------------------------------------------------------------------------------------
        
        // 创建玩家角色
        CPlayerCharacterEntity*             createPlayerCharacterEntity(PlayerCharacterEntityData* data);
		// 删除玩家角色
		void                                destroyPlayerCharacterEntity(IdType id);
		// 获得一个玩家对象
		CPlayerCharacterEntity*             getPlayerCharacterEntity(IdType id);
        // 获得一个玩家对象
		CPlayerCharacterEntity*             getPlayerCharacterEntityByName(Char16* name);

        // 更新所有玩家角色
        void                                updatePlayerCharacterEntitys( Flt delta );
        // 销毁所有玩家角色
        void                                destroyPlayerCharacterEntitys();

        //--------------------------------------------------------------------------------------------------------------

		// 创建怪物角色
		CMonsterEntity*						createMonsterEntity(MonsterEntityData* data);
		// 删除怪物角色
		void                                destroyMonsterEntity(IdType id);
		// 获得一个怪物对象
		CMonsterEntity*						getMonsterEntity(IdType id);

		// 更新所有怪物角色
		void                                updateMonsterEntitys( Flt delta );
		// 销毁所有怪物角色
		void                                destroyMonsterEntitys();

		//--------------------------------------------------------------------------------------------------------------

        // 创建第三方角色
        CThirdPartyCharacterEntity*         createThirdPartyCharacterEntity(ThirdPartyCharacterEntityData* data);
        // 得到第三方角色
        CThirdPartyCharacterEntity*         getThirdPartyCharacterEntity( IdType id );
        // 销毁第三方角色
        void                                destroyThirdPartyCharacterEntity(IdType id);

        // 更新第三方角色
        void                                updateThirdPartyCharacterEntitys( Flt delta );
        // 销毁所有第三方角色
        void                                destroyThirdPartyCharacterEntitys();
        
        //--------------------------------------------------------------------------------------------------------------

        // 根据引擎层的Npc组 加载逻辑层的Npc
        void                                loadNpcEntity();

        // 得到Npc
        CNpcEntity*                         getNpcEntity( IdType id );

        // 更新NPC对象
        void                                updateNpcEntitys(Flt delta);

        // 销毁所有Npc对象
        void                                destroyNpcEntitys();

        //--------------------------------------------------------------------------------------------------------------

        // 根据引擎层的Building组 加载逻辑层普通Building
        void                                loadOrdinaryBuildingEntity();

        // 得到OrdinaryBuilding
        COrdinaryBuildingEntity*            getOrdinaryBuildingEntity( IdType id );

        // 更新所有普通建筑对象
        void                                updateOrdinaryBuildingEntitys( Flt delta );

        // 销毁所有普通建筑对象
        void                                destroyOrdinaryBuildingEntitys();

        //--------------------------------------------------------------------------------------------------------------

        // 创建战斗建筑实体
        CBuildingEntity*                    createBuildingEntity(BuildingEntityData* data);
        // 得到战斗建筑实体
        CBuildingEntity*                    getBuildingEntity( IdType id );
        // 销毁战斗建筑实体
        void                                destroyBuildingEntity(IdType buildingId);

        // 更新战斗建筑实体
        void                                updateBuildingEntitys( Flt delta );
        // 销毁所有战斗建筑实体
        void                                destroyBuildingEntitys();

        //--------------------------------------------------------------------------------------------------------------

        // 创建Troop
        CTroopEntity*                       createTroopEntity( TroopEntityData* data );
        // 得到Troop
        CTroopEntity*                       getTroopEntity( IdType id );

		CTroopSoldierEntity*				getTroopSoldierEntity( TroopIdType id, UInt index );
        // 销毁Troop
        void                                destroyTroopEntity(IdType id);

        // 更新Troop
        void                                updateTroopEntity( Flt delta );
        // 销毁所有Troop
        void                                destroyTroopEntitys();

		//--------------------------------------------------------------------------------------------------------------

		Color								getTroopSoldierColor( FORCE force, IdType playerID );

		void								setTroopSoldierColor( FORCE force, IdType playerID );

		//--------------------------------------------------------------------------------------------------------------

		// 创建道具
		CItemEntity*						createItemEntity( ItemEntityData* data );
		// 删除道具
		void                                destroyItemEntity( IdType id );
		// 获得一个道具对象
		CItemEntity*						getItemEntity( IdType id );

		// 更新所有道具
		void                                updateItemEntitys( Flt delta );
		// 销毁所有道具
		void                                destroyItemEntitys();

		//--------------------------------------------------------------------------------------------------------------

		Bool								getIsStartCampaign();	
		void								setIsStartCampaign(Bool isStart);	

		//--------------------------------------------------------------------------------------------------------------

       
    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [场景管理]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

		//std::map<IdType, CTroopEntity*>                                 mTroopEntityList;


	protected:

        Bool	mIsLoadScene;
        Bool	mIsLoadingScene;
        Bool    mLoadSceneEndDirty;

		Bool	mIsSupportDynamicPathFind;

		typedef std::map<IdType, CPlayerCharacterEntity*>::iterator		PlayerChaEntityListIt;
        typedef std::map<IdType, CThirdPartyCharacterEntity*>::iterator ThirdPartyChaEntityListIt;
		typedef std::map<IdType, CMonsterEntity*>::iterator				MonsterEntityListIt;
        typedef std::map<IdType, CNpcEntity*>::iterator					NpcEntityListIt;
        typedef std::map<IdType, CBuildingEntity*>::iterator			BattleBuildingEntityListIt;
		typedef std::map<IdType, COrdinaryBuildingEntity*>::iterator    OrdinaryBuildingEntityListIt;
		typedef std::map<IdType, CTroopEntity*>::iterator               TroopObjectListIt;
		typedef std::map<IdType, CItemEntity*>::iterator				ItemEntityListIt;

		std::map<IdType, CPlayerCharacterEntity*>						mPlayerChaEntityList;
        std::map<IdType, CThirdPartyCharacterEntity*>                   mThirdPartyEntityList;
		std::map<IdType, CMonsterEntity*>								mMonsterEntityList;
		std::map<IdType, CNpcEntity*>									mNpcEntityList;
		std::map<IdType, CBuildingEntity*>								mBattleBuildingEntityList;
        std::map<IdType, COrdinaryBuildingEntity*>                      mOrdinaryBuildingEntityList;
        std::map<IdType, CTroopEntity*>                                 mTroopEntityList;
		std::map<IdType, CItemEntity*>									mItemEntityList;

        CSkillEffectSystem*												mSkillEffectSystem;


		RegionIdType                                                    mRegionId;
        MapType                                                         mMapType;
        REGION_OBJ_TYPE                                                 mRegionObjType ;
        CRegionObject*                                                  mCurrRegion;
		UInt															mAttackForceNum;
		UInt															mDefenseForceNum;
		std::map<IdType, BYTE>											mAttackForceList;
		std::map<IdType, BYTE>											mDefenseForceList;
		Color															mAttackForceColorList[ATTACKFORCEMAXNUM];
		Color															mDefenseForceColorList[DEFENSEFORCEMAXNUM];

		Bool															mIsStartCampaign;


	};
}

#endif