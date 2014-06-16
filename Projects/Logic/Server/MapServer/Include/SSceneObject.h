
/******************************************************************************/

#ifndef _S_SCENE_OBJECT_H_
#define _S_SCENE_OBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "InstanceListCsv.h"
#include "DistrictList.h"
#include "SSceneGridManager.h"

/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    //  某个地图场景管理器
    //  主要用于管理一个场景相关事务
    /******************************************************************************/
    class SSceneObject	//对应 SRegionObjectBase + SInstanceRegion 部分数据
    {
    public:

        SSceneObject();
        virtual ~SSceneObject();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize();
        virtual Bool                    unInitialize();
		virtual void                    clear();
		virtual void                    update(Flt delta){};

        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------

        Bool			                isOpen() const;
        void			                setOpen(Bool open);
        //是否是 slg, 还是 rpg
        virtual GameType			    getGameType()				= NULL;

		InstanceUIdType				    getInstanceUId() const							{ return mInstanceUId; }
		void						    setInstanceUId(InstanceUIdType instanceUid)		{ mInstanceUId = instanceUid; }

        //-----------------------------------------------------------------------------------
        // File
        //-----------------------------------------------------------------------------------

        SceneFileObject*                getSceneFileObject();

        InstanceListCsvInfo*		    getInstanceListCsvInfo();
        InstanceType				    getInstanceType();

        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

        void			                print();
        Int				                getPrintPlayerStrList(std::string& outStrPlayerIds);				//把区域里的Player的列表字符串的形式返回
        Int				                getPrintPlayerCharacterStrList(std::string& strPlayerCharacterIds);		//把区域里的PlayerCharacter的列表字符串的形式返回
        void					        createCampByPlayerForTest(SPlayerPtr& playerCreator, Vec3& pos);

        //-----------------------------------------------------------------------------------
        // Region
        //-----------------------------------------------------------------------------------

        RegionObjectData*	            getData();

        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------

		SPlayerSceneManager*			getSPlayerSceneManager();

        virtual	void	                onPlayerEnter(SPlayerPtr& playerPtr);
        virtual	void	                onPlayerLeave(SPlayerPtr& playerPtr);

        //-----------------------------------------------------------------------------------
        // PlayerCharacter
        //-----------------------------------------------------------------------------------

		SPlayerCharacterSceneManager*			getSPlayerCharacterSceneManager();

        virtual	void	                onPlayerCharacterEnter(SPlayerCharacterPtr& playerCharPtr);
        virtual	void	                onPlayerCharacterLeave(SPlayerCharacterPtr& playerCharPtr);

        //-----------------------------------------------------------------------------------
        // ThirthPartCharacter
        //-----------------------------------------------------------------------------------

        void					        createThirthPartCharacterByXml();
        Bool						    hasThirthPartCharacter( GameObjectIndexIdInSceneType objIndex );
        Bool						    getThirthPartCharacter( SThirdPartCharacterPtr& ptr, GameObjectIndexIdInSceneType objIndex);
        void						    removeAllThirthPartCharacter();

        virtual	void	                onThirthPartCharacterEnter(SThirdPartCharacterPtr& thirdPartPlayerCharPtr);
        virtual	void	                onThirthPartCharacterLeave(SThirdPartCharacterPtr& thirdPartPlayerCharPtr);

        //-----------------------------------------------------------------------------------
        // Monster
        //-----------------------------------------------------------------------------------

        SMonsterSceneManager*           getMonsterSceneManager();
        
        virtual	void	                onMonsterEnter(SMonsterPtr& monsterPtr){return ;}
        virtual	void	                onMonsterLeave(SMonsterPtr& monsterPtr){return ;}

        //-----------------------------------------------------------------------------------
        // Camp
        //-----------------------------------------------------------------------------------

		SCampSceneManager*					getSCampSceneManager();

        void					        changeCampControl(const CampIdType campId, const AccountIdType targetAccountId);
        void					        changeCampOwner(const AccountIdType targetAccountId);

        //-----------------------------------------------------------------------------------
        // Troop
        //-----------------------------------------------------------------------------------

        void					        addTroopToContorlObjFromCamp(SPlayer* controllerPlayer, TroopGroupIdType troopGroupId, Int troopNum, NetVec2Data* troopPos);
        //统计所有军营里的军队数量
        Int				                getAllTroopNumInCampByForce(const FORCE force);

        virtual	void                    onTroopEnter(SCharacter* troop, SPlayerPtr& controllerPlayer);

        //-----------------------------------------------------------------------------------
        // BattleBuilding
        //-----------------------------------------------------------------------------------

        void					        createBuildingByXml(CharAppearType appearType);
        void					        createBuildingAlwaysExistByXml();
        void					        changeBuildingBelongPlayer(SPlayer* belongPlayer);

        //玩家退出客户端，重新计算由谁来控制 建筑物
        void					        calcChangeBuildingBelongPlayer();	
        void					        setBuildingListBelongPlayer(const AccountIdType accountId);


        virtual	void	                onBattleBuildingEnter(SCharacter* building);
        virtual	void	                onBattleBuildingLeave(SCharacter* building);

        //-----------------------------------------------------------------------------------
        // Building
        //-----------------------------------------------------------------------------------

        //AccountIdType	                getBuildingBelongPlayerAccountId() const { return mBuildingBelongPlayerAccountId; }
        //void			                setBuildingBelongPlayerAccountId(const AccountIdType BelongAccountId) { mBuildingBelongPlayerAccountId = BelongAccountId; }


        //-----------------------------------------------------------------------------------
        // Item
        //-----------------------------------------------------------------------------------

        DropItemManager&		        getDropItemManager();

        //-----------------------------------------------------------------------------------
        // SceneGrid
        //-----------------------------------------------------------------------------------

        SSceneGridManager&		        getSceneGridManager();
    
    private:

		InstanceUIdType			            mInstanceUId;			//副本ID
		AccountIdType			            mCreatorAccountId;		//创建者id
		U64						            mCreateTime;			//创建时间戳
		U64						            mLastPlayerLeaveTime;	//最后一个玩家离开时间戳
        
		Bool								mOpen;					//该区域是否开启,  由CenterServer控制
		RegionObjectData*					mRegionData;

	private:

		SPlayerSceneManager*				mSPlayerSceneManager;
		SPlayerCharacterSceneManager*		mSPlayerCharacterSceneManager;
		SMonsterSceneManager*				mSMonsterSceneManager;
		SCampSceneManager*					mSCampSceneManager;
		SBuildingSceneManager*				mSBuildingSceneManager;


		SSceneGridManager					mSceneGridManager;
		//SItemSceneManager		mSMonsterSceneManager;

    };
}

#endif	