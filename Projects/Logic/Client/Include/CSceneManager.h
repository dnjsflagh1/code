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
	//��������3d��������Ϸ�����߼���ص���ʾ����
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

    //��������������������������������������������������������������������������������������������������
    //  [��Ҫ����]
    //��������������������������������������������������������������������������������������������������

		// ��Ϸ��������
		void                                update( Flt delta );
        // �õ����泡������
        IScene*                             getEngineScene();
        // �õ�������Чϵͳ
        CSkillEffectSystem*                 getSkillEffectSystem();
        
    //��������������������������������������������������������������������������������������������������
    //  [�������غ��ͷ�]
    //��������������������������������������������������������������������������������������������������

		// �����ļ���
		Bool                                loadRegionScene(RegionIdType regionId, REGION_OBJ_TYPE regionObjType);
		Bool                                loadRegionScene(const Str& baseFilePath, const Str& filepath);
		// ���پݵ㳡��
		void                                destroyRegionScene();
		// ���ٳ�����Ϣ
		void								destroyRegionInfo() { mCurrRegion = NULL; }
        // �Ƿ�ݵ㳡����Ч
        Bool                                isRegionSceneLoaded();
		// �����Ƿ񳡾���Ч
		void								setRegionSceneLoaded(Bool isLoadScene);
        // �õ��ݵ���
        IdType                              getRegionId();

		CRegionObject*						getCurrRegion();
		// �õ���ͼ����
		REGION_OBJ_TYPE                     getRegionObjType();
        // �õ���ͼ����
        MapType                             getMapType();

        // ���¼��س���
        void                                updateLoadScene();
        // ����ʼ���س���
        void                                onLoadSceneStart();
        // ���������س���
        void                                onLoadSceneEnd();
        // ���ý������س�����־λ
        void                                setLoadSceneEndDirty();
		// ���ý������س�����־λ
		Bool                                isLoadingScene();

		// ���ú͵õ��Ƿ�֧�ֶ�̬Ѱ·
		void								setDynamicPathFindEnable( Bool enable );
		Bool								getDynamicPathFindEnable();

		//��������������������������������������������������������������������������������������������������
		//  [����Ԫ�ؼ��غ��ͷ�]
		//��������������������������������������������������������������������������������������������������

        //--------------------------------------------------------------------------------------------------------------

        // �õ�����ʵ�����
        CSceneEntity*                       getSceneEntity(IdType id, GAMEOBJ_TYPE type);
        CCharacterSceneEntity*              getCharacterSceneEntity( GAMEOBJ_TYPE type, IdType id, UInt index = 0 );

        //--------------------------------------------------------------------------------------------------------------
        
        // ������ҽ�ɫ
        CPlayerCharacterEntity*             createPlayerCharacterEntity(PlayerCharacterEntityData* data);
		// ɾ����ҽ�ɫ
		void                                destroyPlayerCharacterEntity(IdType id);
		// ���һ����Ҷ���
		CPlayerCharacterEntity*             getPlayerCharacterEntity(IdType id);
        // ���һ����Ҷ���
		CPlayerCharacterEntity*             getPlayerCharacterEntityByName(Char16* name);

        // ����������ҽ�ɫ
        void                                updatePlayerCharacterEntitys( Flt delta );
        // ����������ҽ�ɫ
        void                                destroyPlayerCharacterEntitys();

        //--------------------------------------------------------------------------------------------------------------

		// ���������ɫ
		CMonsterEntity*						createMonsterEntity(MonsterEntityData* data);
		// ɾ�������ɫ
		void                                destroyMonsterEntity(IdType id);
		// ���һ���������
		CMonsterEntity*						getMonsterEntity(IdType id);

		// �������й����ɫ
		void                                updateMonsterEntitys( Flt delta );
		// �������й����ɫ
		void                                destroyMonsterEntitys();

		//--------------------------------------------------------------------------------------------------------------

        // ������������ɫ
        CThirdPartyCharacterEntity*         createThirdPartyCharacterEntity(ThirdPartyCharacterEntityData* data);
        // �õ���������ɫ
        CThirdPartyCharacterEntity*         getThirdPartyCharacterEntity( IdType id );
        // ���ٵ�������ɫ
        void                                destroyThirdPartyCharacterEntity(IdType id);

        // ���µ�������ɫ
        void                                updateThirdPartyCharacterEntitys( Flt delta );
        // �������е�������ɫ
        void                                destroyThirdPartyCharacterEntitys();
        
        //--------------------------------------------------------------------------------------------------------------

        // ����������Npc�� �����߼����Npc
        void                                loadNpcEntity();

        // �õ�Npc
        CNpcEntity*                         getNpcEntity( IdType id );

        // ����NPC����
        void                                updateNpcEntitys(Flt delta);

        // ��������Npc����
        void                                destroyNpcEntitys();

        //--------------------------------------------------------------------------------------------------------------

        // ����������Building�� �����߼�����ͨBuilding
        void                                loadOrdinaryBuildingEntity();

        // �õ�OrdinaryBuilding
        COrdinaryBuildingEntity*            getOrdinaryBuildingEntity( IdType id );

        // ����������ͨ��������
        void                                updateOrdinaryBuildingEntitys( Flt delta );

        // ����������ͨ��������
        void                                destroyOrdinaryBuildingEntitys();

        //--------------------------------------------------------------------------------------------------------------

        // ����ս������ʵ��
        CBuildingEntity*                    createBuildingEntity(BuildingEntityData* data);
        // �õ�ս������ʵ��
        CBuildingEntity*                    getBuildingEntity( IdType id );
        // ����ս������ʵ��
        void                                destroyBuildingEntity(IdType buildingId);

        // ����ս������ʵ��
        void                                updateBuildingEntitys( Flt delta );
        // ��������ս������ʵ��
        void                                destroyBuildingEntitys();

        //--------------------------------------------------------------------------------------------------------------

        // ����Troop
        CTroopEntity*                       createTroopEntity( TroopEntityData* data );
        // �õ�Troop
        CTroopEntity*                       getTroopEntity( IdType id );

		CTroopSoldierEntity*				getTroopSoldierEntity( TroopIdType id, UInt index );
        // ����Troop
        void                                destroyTroopEntity(IdType id);

        // ����Troop
        void                                updateTroopEntity( Flt delta );
        // ��������Troop
        void                                destroyTroopEntitys();

		//--------------------------------------------------------------------------------------------------------------

		Color								getTroopSoldierColor( FORCE force, IdType playerID );

		void								setTroopSoldierColor( FORCE force, IdType playerID );

		//--------------------------------------------------------------------------------------------------------------

		// ��������
		CItemEntity*						createItemEntity( ItemEntityData* data );
		// ɾ������
		void                                destroyItemEntity( IdType id );
		// ���һ�����߶���
		CItemEntity*						getItemEntity( IdType id );

		// �������е���
		void                                updateItemEntitys( Flt delta );
		// �������е���
		void                                destroyItemEntitys();

		//--------------------------------------------------------------------------------------------------------------

		Bool								getIsStartCampaign();	
		void								setIsStartCampaign(Bool isStart);	

		//--------------------------------------------------------------------------------------------------------------

       
    //��������������������������������������������������������������������������������������������������
    //  [��������]
    //��������������������������������������������������������������������������������������������������

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