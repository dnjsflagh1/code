
/******************************************************************************/

#include "stdafx.h"
#include "SMonsterSceneManager.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // SMonster 模板对象
    /******************************************************************************/


    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

	Bool SMonsterXml::initialize( SMonsterSceneManager* owner )
	{
		return true;
	}

    Bool SMonsterXml::unInitialize()
	{
		return true;
	}

    void SMonsterXml::clear()
	{

	}

    void SMonsterXml::update(Flt delta)
	{

	}

    //-----------------------------------------------------------------------------------
    // Instance
    //-----------------------------------------------------------------------------------

    void SMonsterXml::getMonster( SMonsterPtr& ptr )
	{
	}

    Bool SMonsterXml::hasMonster()
	{
		return true;
	}

    //-----------------------------------------------------------------------------------
    // MonsterBorn
    //-----------------------------------------------------------------------------------


    void SMonsterXml::checkMonsterBorn()
	{

	}

    //-----------------------------------------------------------------------------
    void SMonsterXml::createMonster()
    {
        if ( mSMonsterPtr.isNull() == false )
        {
            DYNAMIC_EEXCEPT_LOG("already exist monster!");
            destroyMonster();
            mSMonsterPtr.setNull();
        }

        //mSMonsterSceneManager->mSMonsterFactory->createSMonsterPtr( ... );

        mSMonsterSceneManager->mMonsterListCs.writeLock();
        {
            //mSMonsterSceneManager->mMonsterList[ id ] = this;
        }
        mSMonsterSceneManager->mMonsterListCs.writeUnLock();
    }

    //-----------------------------------------------------------------------------
    void SMonsterXml::destroyMonster()
    {

    }


    /******************************************************************************/
    //  SMonsterSceneManager
    /******************************************************************************/

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

	Bool SMonsterSceneManager::initialize( SSceneObject* owner )
	{
		return true;
	}
    Bool SMonsterSceneManager::unInitialize()
	{
		return true;
	}
    void SMonsterSceneManager::clear()
	{
	}
    void SMonsterSceneManager::update(Flt delta)
	{

	}

    //-----------------------------------------------------------------------------------
    // Base Data
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    void SMonsterSceneManager::createMonsterByXml(CharAppearType appearType)
    {
		//loop
		{
			//SMonsterXml::createMonster();
		}

    }



    Bool SMonsterSceneManager::hasMonster( GameObjectIndexIdInSceneType objIndex )
	{
		return true;
	}
    Bool SMonsterSceneManager::getMonster( SMonsterPtr& ptr, GameObjectIndexIdInSceneType objIndex)
	{
		return true;
	}
    void SMonsterSceneManager::removeAllMonster()
    {


		//loop mMonsterList
		{

			//SMonsterXml::destroyMonster();

		}

		//mMonsterList.clear();

		// 可选择
		//mMonsterXmlList.clear();
    }

    //-----------------------------------------------------------------------------------
    // AI Ctrl
    //-----------------------------------------------------------------------------------

    //void				            calcControlMonsterAIByPlayerListAndSendToClient();
    //void				            setIsNeedCalcContorlMonsterAI(Bool need);


    //Bool				            hasPlayerInCtrlMonsterAIList(const AccountIdType accountId);	
    //void				            addPlayerInCtrlMonsterAIList(SPlayerPtr& playerPtr);
    //void				            removePlayerInCtrlMonsterAIList(const AccountIdType accountId);


}	//namespace MG