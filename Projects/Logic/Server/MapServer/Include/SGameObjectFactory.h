

/******************************************************************************/
#ifndef _SGAMEOBJECTFACTORY_H_
#define _SGAMEOBJECTFACTORY_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "ObjectPool.h"
#include "SPlayerCharacter.h"
#include "SMonster.h"
#include "SThirdPartCharacter.h"
#include "SCamp.h"
#include "SCampaignInRegion.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // ��ɫ����
    /******************************************************************************/
    class SPlayerCharacterFactory
    {
        friend class SPlayerCharacterPtr;
    public:
        SPlayerCharacterFactory();
        ~SPlayerCharacterFactory();

    public:

        void    createSPlayerCharacterPtr( SPlayerCharacterPtr& ptr, PlayerCharacterIdType playerCharacterId, PlayerCharacterData& data );

    protected:  

        void    destroySPlayerCharacterPtr( SPlayerCharacterPtr& ptr );

    private:    

        ObjectPool<SPlayerCharacter,false> mSPlayerCharacterPool;
        Critical    mSPlayerCharacterPoolCs;
    };


	/******************************************************************************/
	// Building����
	/******************************************************************************/
	class SBuildingFactory
	{
		friend class SBuildingPtr;
	public:
		SBuildingFactory();
		~SBuildingFactory();

	public:

		void    createSBuildingPtr(SBuildingPtr& ptr, BuildingData& data, GameObjectIndexIdInSceneType indexId);

	protected:  

		void    destroySBuildingPtr( SBuildingPtr& ptr );

	private:    

		ObjectPool<SBuilding,false> mSBuildingPool;
		Critical    mSBuildingPoolCs;
	};


	/******************************************************************************/
	// Monster����
	/******************************************************************************/
	class SMonsterFactory
	{

		friend class SMonsterPtr;

	public:

		SMonsterFactory();
		~SMonsterFactory();

	public:

		void    createSMonsterPtr(SMonsterPtr& ptr, MonsterData& data, GameObjectIndexIdInSceneType indexId);

	protected:  

		void    destroySMonsterPtr( SMonsterPtr& ptr );

	private:
		ObjectPool<SMonster,false> mSMonsterPool;
		Critical    mSMonsterPoolCs;
	};
	
	/******************************************************************************/
	// ThirdPartCharacter����
	/******************************************************************************/
	 class SThirdPartCharacterFactory
	 {

		 friend class SThirdPartCharacterPtr;

	 public:

		 SThirdPartCharacterFactory();
		 ~SThirdPartCharacterFactory();

	 public:

		 void    createSThirdPartCharacterPtr(SThirdPartCharacterPtr& ptr, ThirdPartyCharacterData& data, GameObjectIndexIdInSceneType indexId);

	 protected:  

		 void    destroySThirdPartCharacterPtr( SThirdPartCharacterPtr& ptr );

	 private:
		 ObjectPool<SThirdPartCharacter,false> mSThirdPartCharacterPool;
		 Critical    mSThirdPartCharacterPoolCs;
	 };

	/******************************************************************************/
	// Troop����
	/******************************************************************************/

	/******************************************************************************/
	// Item����
	/******************************************************************************/

	 /******************************************************************************/
	 // Camp����
	 /******************************************************************************/
	 class SCampFactory
	 {

		 friend class SCampPtr;

	 public:

		 SCampFactory();
		 ~SCampFactory();

	 public:

		 void    createSCampPtr(SCampPtr& ptr, GameObjectIndexIdInSceneType indexId);

	 protected:  

		 void    destroySCampPtr( SCampPtr& ptr );

	 private:
		 ObjectPool<SCamp,false> mSCampPool;
		 Critical    mSCampPoolCs;
	
	 };

	 /******************************************************************************/
	 // Camp����
	 /******************************************************************************/
	 class SCampaignInRegionPtrFactory
	 {
		 friend class SCampaignInRegionPtr;

	 public:

		 SCampaignInRegionPtrFactory();
		 ~SCampaignInRegionPtrFactory();

	 public:

		 void    createCampaignInRegionPtr(SCampaignInRegionPtr& ptr, GameObjectIndexIdInSceneType indexId){}

	 protected:  

		 void    destroyCampaignInRegionPtr( SCampaignInRegionPtr& ptr ){}

	 private:
		 ObjectPool<SCampaignInRegion,false> mSCampaignInRegionPool;
		 Critical    mSCampaignInRegionPoolCs;

	 };
		
}

#endif