
/******************************************************************************/

#include "stdafx.h"
#include "SCampaignInRegionManager.h"
#include "SCampaignInRegion.h"
#include "SPlaceSceneObject.h"
#include "SGameObjectFactory.h"

/******************************************************************************/
namespace MG
{


	/******************************************************************************/
	//SPlayerPtr
	/******************************************************************************/

	void SCampaignInRegionPtr::destroy(void)
	{
		mFactory->destroyCampaignInRegionPtr( *this );
	}


    /******************************************************************************/
    // SCampaign
    /******************************************************************************/

	SCampaignInRegion::SCampaignInRegion()
	{
	}

	SCampaignInRegion::~SCampaignInRegion()
	{

	}


    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

	Bool SCampaignInRegion::initialize( SSceneObject& sceneObj )
    {

        // 创建4种逻辑对象
        // 运行期间不释放逻辑对象，直到 SCampaign unInitialize

		return true;

    }

	//-----------------------------------------------------------------------------------
    Bool SCampaignInRegion::unInitialize()
	{
		return true;
	}

	//-----------------------------------------------------------------------------------
    void SCampaignInRegion::clear()
	{
	}

	//-----------------------------------------------------------------------------------
    void SCampaignInRegion::update(Flt delta)
	{
	}

    //-----------------------------------------------------------------------------------
    // Scene
    //-----------------------------------------------------------------------------------

    void SCampaignInRegion::checkSceneLifeTime()
	{
	}

    void SCampaignInRegion::createScene()
    {

        SPlaceSceneObjectPtr atkPtr;

        // SAtkSceneObjectPtr atkPtr = 创建战场副本
        // SWorldManager
        // 创建场景对象，生命周期由SCampaign控制
        // WorldManager

		SCampaignInRegionPtr Campaignptr;
		atkPtr->setCampaign( Campaignptr );
    }

    void SCampaignInRegion::destroyScene()
	{

	}

    //-----------------------------------------------------------------------------------
    // Logic
    //-----------------------------------------------------------------------------------


    void SCampaignInRegion::createLogicObject()
    {
        // Camp         
        // SAtkSceneObjectPtr -> SCampSceneManage 会 Xml读取加载
        // 所以可以通过得到SCampSceneManage中的实例或者通过MapObject中的XmlFileLoader得到CampList信息创建逻辑对象

        // Army         读取Csv 调用
        // 创建逻辑对象
        // 并创建实例

        // TroopGroup   读取Csv 
        // 创建逻辑对象
        // 并创建实例

        // Troop        读取Csv 
        // 创建逻辑对象
        // 并创建实例
    }


    void SCampaignInRegion::createLogicCampInCampaign()
	{
	}

    void SCampaignInRegion::createLogicArmyInCampaign()
	{
	}

    void SCampaignInRegion::createLogicTroopGroupInCampaign()
	{
	}
    void SCampaignInRegion::createLogicTroopInCampaign()
	{

	}

}