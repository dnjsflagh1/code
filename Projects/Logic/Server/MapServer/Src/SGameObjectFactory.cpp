
/******************************************************************************/

#include "stdafx.h"
#include "SGameObjectFactory.h"
#include "GameObject.h"


/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	// 角色工厂
	/******************************************************************************/
    //-----------------------------------------------------------------------------
    SPlayerCharacterFactory::SPlayerCharacterFactory()
    {
    }

    //-----------------------------------------------------------------------------
    SPlayerCharacterFactory::~SPlayerCharacterFactory()
    {
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacterFactory::createSPlayerCharacterPtr( SPlayerCharacterPtr& ptr, PlayerCharacterIdType playerCharacterId, PlayerCharacterData& data )
    {
        SPlayerCharacter* playerChar = NULL;
        mSPlayerCharacterPoolCs.lock();
        {
            playerChar = MG_POOL_NEW_ONCE_CONSTRUCTION(mSPlayerCharacterPool, SPlayerCharacter, ());
        }
        mSPlayerCharacterPoolCs.unlock();

        playerChar->clear();
        playerChar->initialize( playerCharacterId, data );

        ptr.bind( playerChar );

        ptr.mFactory = this;
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacterFactory::destroySPlayerCharacterPtr( SPlayerCharacterPtr& ptr )
    {
        SPlayerCharacter* playerChar = ptr.getPointer();

        if ( playerChar )
        {
            playerChar->clear();
            playerChar->unInitialize();

            mSPlayerCharacterPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSPlayerCharacterPool, playerChar);
            }
            mSPlayerCharacterPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("playerChar pointer is null!");
        }
    }

	/******************************************************************************/
	// Building工厂
	/******************************************************************************/

	//-----------------------------------------------------------------------------
	SBuildingFactory::SBuildingFactory()
	{
	}

	//-----------------------------------------------------------------------------
	SBuildingFactory::~SBuildingFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void SBuildingFactory::createSBuildingPtr(SBuildingPtr& ptr, BuildingData& data, GameObjectIndexIdInSceneType indexId)
	{
		SBuilding* building = NULL;
		mSBuildingPoolCs.lock();
		{
			building = MG_POOL_NEW_ONCE_CONSTRUCTION(mSBuildingPool, SBuilding, (indexId));
		}
		mSBuildingPoolCs.unlock();

		building->clear();
		//building->initialize(data);
		building->setID(indexId);

		ptr.bind( building );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void SBuildingFactory::destroySBuildingPtr( SBuildingPtr& ptr )
	{
		SBuilding* building = ptr.getPointer();

		if ( building )
		{
			building->clear();
			building->unInitialize();

			mSBuildingPoolCs.lock();
			{
				MG_POOL_DELETE_ONCE_DESTRUCTOR(mSBuildingPool, building);
			}
			mSBuildingPoolCs.unlock();
		}else
		{
			DYNAMIC_EEXCEPT_LOG("building pointer is null!");
		}
	}

	/******************************************************************************/
	// Monster工厂
	/******************************************************************************/

	//-----------------------------------------------------------------------------
	SMonsterFactory::SMonsterFactory()
	{
	}

	//-----------------------------------------------------------------------------
	SMonsterFactory::~SMonsterFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void SMonsterFactory::createSMonsterPtr(SMonsterPtr& ptr, MonsterData& data, GameObjectIndexIdInSceneType indexId)
	{
		SMonster* monster = NULL;
		mSMonsterPoolCs.lock();
		{
			monster = MG_POOL_NEW_ONCE_CONSTRUCTION(mSMonsterPool, SMonster, ());
		}
		mSMonsterPoolCs.unlock();

		monster->clear();
		//monster->initialize(data,indexId);
		monster->setID(indexId);

		ptr.bind( monster );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void SMonsterFactory::destroySMonsterPtr( SMonsterPtr& ptr )
	{
		SMonster* monster = ptr.getPointer();

		if ( monster )
		{
			monster->clear();
			monster->unInitialize();

			mSMonsterPoolCs.lock();
			{
				MG_POOL_DELETE_ONCE_DESTRUCTOR(mSMonsterPool, monster);
			}
			mSMonsterPoolCs.unlock();
		}else
		{
			DYNAMIC_EEXCEPT_LOG("monster pointer is null!");
		}
	}

	/******************************************************************************/
	// ThirdPartCharacter工厂
	/******************************************************************************/

	//-----------------------------------------------------------------------------
	SThirdPartCharacterFactory::SThirdPartCharacterFactory()
	{
	}

	//-----------------------------------------------------------------------------
	SThirdPartCharacterFactory::~SThirdPartCharacterFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void SThirdPartCharacterFactory::createSThirdPartCharacterPtr(SThirdPartCharacterPtr& ptr, ThirdPartyCharacterData& data, GameObjectIndexIdInSceneType indexId)
	{
		SThirdPartCharacter* thirdPartCharacter = NULL;
		mSThirdPartCharacterPoolCs.lock();
		{
			thirdPartCharacter = MG_POOL_NEW_ONCE_CONSTRUCTION(mSThirdPartCharacterPool, SThirdPartCharacter, (indexId));
		}
		mSThirdPartCharacterPoolCs.unlock();

		thirdPartCharacter->clear();
		//monster->initialize(data);
		thirdPartCharacter->setID(indexId);

		ptr.bind( thirdPartCharacter );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void SThirdPartCharacterFactory::destroySThirdPartCharacterPtr( SThirdPartCharacterPtr& ptr )
	{
		SThirdPartCharacter* thirdPartCharacter = ptr.getPointer();

		if ( thirdPartCharacter )
		{
			thirdPartCharacter->clear();
			thirdPartCharacter->unInitialize();

			mSThirdPartCharacterPoolCs.lock();
			{
				MG_POOL_DELETE_ONCE_DESTRUCTOR(mSThirdPartCharacterPool, thirdPartCharacter);
			}
			mSThirdPartCharacterPoolCs.unlock();
		}else
		{
			DYNAMIC_EEXCEPT_LOG("thirdPartCharacter pointer is null!");
		}
	}
	/******************************************************************************/
	// Camp工厂
	/******************************************************************************/

	//-----------------------------------------------------------------------------
	SCampFactory::SCampFactory()
	{
	}

	//-----------------------------------------------------------------------------
	SCampFactory::~SCampFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void SCampFactory::createSCampPtr(SCampPtr& ptr, GameObjectIndexIdInSceneType indexId)
	{
		SCamp* camp = NULL;
		mSCampPoolCs.lock();
		{
			camp = MG_POOL_NEW_ONCE_CONSTRUCTION(mSCampPool, SCamp, ());
		}
		mSCampPoolCs.unlock();

		camp->clear();
		//camp->initialize(data);
		camp->setID(indexId);

		ptr.bind( camp );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void SCampFactory::destroySCampPtr( SCampPtr& ptr )
	{
		SCamp* camp = ptr.getPointer();

		if ( camp )
		{
			camp->clear();
			camp->unInitialize();

			mSCampPoolCs.lock();
			{
				MG_POOL_DELETE_ONCE_DESTRUCTOR(mSCampPool, camp);
			}
			mSCampPoolCs.unlock();
		}else
		{
			DYNAMIC_EEXCEPT_LOG("camp pointer is null!");
		}
	}

}	//namespace MG