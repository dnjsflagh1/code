/******************************************************************************/
#include "stdafx.h"
#include "Scene.h"
#include "PathFindingManager.h"
#include "MGEngineUtility.h"
#include "OgreSceneQuery.h"
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    PathFindingManager::PathFindingManager( Scene* scene )
        :mScene(scene)
		,mStaticPathFinder(NULL)
		,mDynamicPathFinder(NULL)
    {

    }

    //-----------------------------------------------------------------------
    PathFindingManager::~PathFindingManager()
    {
		unLoad();
    }

    //-----------------------------------------------------------------------
    void PathFindingManager::load()
    {
		TerrainManager* terrainManager = mScene->getTerrainManager();
		if(!terrainManager)
		{
			return;
		}

		mStaticPathFinder = MG_NEW PathFinder2;
		mDynamicPathFinder = MG_NEW PathFinder21;

        // ����Ѱ·����
        mStaticPathFinder->setType( PathFinder2::PT_SPREAD_SEARCH );
		//mStaticPathFinder->setType( PathFinder2::PT_ALWAYS_NEAREST );
        mDynamicPathFinder->setType( PathFinder21::PT_ALWAYS_NEAREST );

        /////////////////////////////////////////////////////////////////////////////////////////////

        // ���ؾ�̬Ѱ·����
		Int terrainWidth = terrainManager->getTerrainWidth();
		Int terrainHeight = terrainManager->getTerrainHeight();

		Vector3 centerPos = MGEngineUtility::toVec3(terrainManager->getCenterPosition());
		
        Int staticBlockMapWidth = terrainWidth / BlockManager::STATIC_BLOCK_GRID_SIZE;
		if(staticBlockMapWidth * BlockManager::STATIC_BLOCK_GRID_SIZE < terrainWidth)
		{
			staticBlockMapWidth++;
		}

		Int staticBlockMapHeight = terrainHeight / BlockManager::STATIC_BLOCK_GRID_SIZE;
		if(staticBlockMapHeight * BlockManager::STATIC_BLOCK_GRID_SIZE < terrainHeight)
		{
			staticBlockMapHeight++;
		}

		mStaticPathFinder->load(mScene->getBlockManager()->getStaticBlockList());

        /////////////////////////////////////////////////////////////////////////////////////////////

        // ���ض�̬Ѱ·����

        Int dynamicBlockMapWidth = terrainWidth / BlockManager::DYNAMIC_BLOCK_GRID_SIZE;
		if(dynamicBlockMapWidth * BlockManager::DYNAMIC_BLOCK_GRID_SIZE < terrainWidth)
		{
			dynamicBlockMapWidth++;
		}

		Int dynamicBlockMapHeight = terrainHeight / BlockManager::DYNAMIC_BLOCK_GRID_SIZE;
		if(dynamicBlockMapHeight * BlockManager::DYNAMIC_BLOCK_GRID_SIZE < terrainHeight)
		{
			dynamicBlockMapHeight++;
		}

		mDynamicPathFinder->load(mScene, 100, 100);
    }

    //-----------------------------------------------------------------------
    void PathFindingManager::unLoad()
    {
		MG_SAFE_DELETE(mStaticPathFinder);
		MG_SAFE_DELETE(mDynamicPathFinder);
    }

    //-----------------------------------------------------------------------
    void PathFindingManager::update(Flt delta)
    {

    }

	//-----------------------------------------------------------------------
	PathFinder2* PathFindingManager::getStaticPathFinder()
	{
		return mStaticPathFinder;
	}

	//-----------------------------------------------------------------------
	PathFinder21* PathFindingManager::getDynamicPathFinder()
	{
		return mDynamicPathFinder;
	}

}