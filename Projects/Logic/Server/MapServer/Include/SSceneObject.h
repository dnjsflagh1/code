
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
    //  ĳ����ͼ����������
    //  ��Ҫ���ڹ���һ�������������
    /******************************************************************************/
    class SSceneObject	//��Ӧ SRegionObjectBase + SInstanceRegion ��������
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
        //�Ƿ��� slg, ���� rpg
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
        Int				                getPrintPlayerStrList(std::string& outStrPlayerIds);				//���������Player���б��ַ�������ʽ����
        Int				                getPrintPlayerCharacterStrList(std::string& strPlayerCharacterIds);		//���������PlayerCharacter���б��ַ�������ʽ����
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
        //ͳ�����о�Ӫ��ľ�������
        Int				                getAllTroopNumInCampByForce(const FORCE force);

        virtual	void                    onTroopEnter(SCharacter* troop, SPlayerPtr& controllerPlayer);

        //-----------------------------------------------------------------------------------
        // BattleBuilding
        //-----------------------------------------------------------------------------------

        void					        createBuildingByXml(CharAppearType appearType);
        void					        createBuildingAlwaysExistByXml();
        void					        changeBuildingBelongPlayer(SPlayer* belongPlayer);

        //����˳��ͻ��ˣ����¼�����˭������ ������
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

		InstanceUIdType			            mInstanceUId;			//����ID
		AccountIdType			            mCreatorAccountId;		//������id
		U64						            mCreateTime;			//����ʱ���
		U64						            mLastPlayerLeaveTime;	//���һ������뿪ʱ���
        
		Bool								mOpen;					//�������Ƿ���,  ��CenterServer����
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